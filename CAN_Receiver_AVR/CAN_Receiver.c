/*
 * CAN_Transmitter.c
 *
 *  Created on: Apr 29, 2024
 *      Author: Moamen
 */

#include "STD_TYPES.h"
#include"BIT_MATH.h"
#include "MDIO_interface.h"
#include "HLCD_Interface.h"
#include "SPI_Interface.h"
#include "CAN_Interface.h"
#include "CAN_Private.h"



/**/
u8 CAN_u8ReadRegister(u8 address)
{
	u8 Local_u8ReadValue = 0;
	SPI_voidChipSelect(1);

	SPI_u8MasterTransmitter(MCP_2515_READ);
	SPI_u8MasterTransmitter(address);
	Local_u8ReadValue = SPI_u8MasterTransmitter(0);
	SPI_voidChipSelect(0);

	return Local_u8ReadValue;


}


/**/
void CAN_voidWriteRegister(u8 address, u8 Data)
{
	/*		Chip select 		*/
	SPI_voidChipSelect(1);
	/*			First we send the instrucion as given from data sheet
	 * 			0b00000010
	 * 			then we send the address and Data as given in datasheet
	 * */
	SPI_u8MasterTransmitter(MCP2515_INST_WRITE);
	SPI_u8MasterTransmitter(address);
	SPI_u8MasterTransmitter(Data);

	SPI_voidChipSelect(0);


}

/*		Function to reset 		*/
void CAN_voidReset()
{
	/*		Chip select		*/
	SPI_voidChipSelect(1);

	SPI_u8MasterTransmitter(MCP_2515_RESET);


	SPI_voidChipSelect(0);


}


/*			Function to modify bits*/
void CAN_voidModify(u8 address, u8 mask, u8 Data)
{
	SPI_voidChipSelect(1);

	SPI_u8MasterTransmitter(MCP_2515_BIT_MODIFY);

	SPI_u8MasterTransmitter(address);
	SPI_u8MasterTransmitter(mask);
	SPI_u8MasterTransmitter(Data);

	SPI_voidChipSelect(0);

}


/*			Function to set BIT timing 		Very important		*/
void CAN_voidSetBitTiming(u8 CNF1VAL, u8 CNF2VAL, u8 CNF3VAL)
{
	CAN_voidWriteRegister(CNF1, CNF1VAL);

	CAN_voidWriteRegister(CNF2, CNF2VAL);

	CAN_voidWriteRegister(CNF3, CNF3VAL);

}

/*		Function to set MODE of operation		*/
void CAN_voidSetMode(u8 mode)
{
	CAN_voidModify(CANCTRL, 0xE0, mode << 5);

	/*		here we loop in the value of the state to check if the mode
	 *
	 * 		*/
	while(CAN_u8ReadRegister(CANSTAT >> 5) != mode);


}

/**/
void CAN_voidSetRollOver(u8 value)
{

	CAN_voidModify(RXB0CTRL, 1<<3, 1<<3);
}


/*			Function to initialize the CAN as Receiver			*/
void CAN_voidInit_Recevier(void)
{
	/*		Initialize the Master of the SPI			*/
	SPI_VoidMasterInit();
	/*			After each step we have to reset CAN		*/
	CAN_voidReset();
	/*			We now choose the mode of the CAN
	 * 			Configuration Mode
	 * */
	/*			from data sheet to pick the mode
	 * 			0x84  ==  0b10000100*/
	CAN_voidWriteRegister(CANCTRL, 0x84);
	/*			Wait for the mode to be in configuration mode		*/
	while(CAN_u8ReadRegister(CANSTAT>>5)!= MCP_2515_CONFIGURATION_MODE);
	/*			We set the Bit timing here		*/
	CAN_voidSetBitTiming(0x80, 0xB1, 0x05);

	/*			We set mask0 and choose between standard and extended*/
	/*					0x00000000 >> accept all messages because 0 will assign as don't care and accepted*/
	CAN_voidSetMask(RXM0SIDH, 0x00000000, 1);

	/*			We set mask1 and choose between standard and extended*/
	/*					0x00000000 >> accept all messages because 0 will assign as don't care and accepted*/
	CAN_voidSetMask(RXM1SIDH, 0x00000000, 1);
	/*		Enabling Interrupt			*/
	CAN_voidWriteRegister(CANINTE,1<<0);
	/*			CAN NORMAL MODE TO SEND AND RECEIVE		*/
	/*
	 * 			we set the CAN into normal mode
	 * 			to be able to send and receive
	 * 			*/
	CAN_voidSetMode(MCP_2515_NORMAL_MODE);

}

/**/
void CAN_voidSendMessage(u8 bufferIndex, u32 MessageID, u8 DLC, u8 * data)
{
	/*			We need to first to take the bus by selecting it		*/
	SPI_voidChipSelect(1);
	SPI_u8MasterTransmitter(MCP2515_INST_WRITE);
	SPI_u8MasterTransmitter(TXB0CTRL);

	/*			Now we setup priority "Mandatory"
	 * 			we shifted by 6 to make it the first priority i can choose any number
	 * 			but the upcoming priorities must be lower than 6
	 * 		*/
	SPI_u8MasterTransmitter(DLC >> 6);

	SPI_u8MasterTransmitter((u8)(MessageID >> 3));
	SPI_u8MasterTransmitter((u8)(MessageID << 5));
	SPI_u8MasterTransmitter(0);
	SPI_u8MasterTransmitter(0);
	/*			We need only the first 4 bits from right
	 * 			so we make logic add to neglect any bits except 4 LSBs
	 * 			*/
	SPI_u8MasterTransmitter(DLC & 0x0F);

	/*			Sending Data array of data using pointer			*/
	for(u8 counter = 0; counter < (DLC & 0x0F) ; counter++)
	{
		SPI_u8MasterTransmitter(data[counter]);
	}
	/*		Release the bus			*/
	SPI_voidChipSelect(0);
	/*			Initialize the bus		*/
	SPI_voidChipSelect(1);
	/*			Message request to send	buffer 0		*/
	SPI_u8MasterTransmitter(MCP_2515_RTS_B0);
	/*		Release the bus			*/
	SPI_voidChipSelect(0);



}
u8 ArrayToReceiveMessage[14];
/**/
void CAN_voidReceiveMessage()
{
	/*			Select Bus		*/
	SPI_voidChipSelect(1);
	/*				Set mode to read			*/
	SPI_u8MasterTransmitter(MCP_2515_READ);
	/*			send buffer 0 to receive data		*/
	SPI_u8MasterTransmitter(RXB0CTRL);
	/*				data is array so we loop in the range of array		*/
	for(u8 counter = 0; counter < 14 ; counter++)
	{
		/*			storing data into array 		*/
		ArrayToReceiveMessage[counter] = SPI_u8MasterTransmitter(0);
	}
	/*			Leaving bus			*/
	SPI_voidChipSelect(0);

	/*		Clear Flag for interrupt		*/
	CAN_voidWriteRegister(EFLG, 0x2C);

}
/**/
void CAN_voidSetMask(u8 maskAddress, u32 data, u8 IsExtended)
{
	/*		select the bus		*/
	SPI_voidChipSelect(1);
	/**/
	SPI_u8MasterTransmitter(MCP2515_INST_WRITE);
	/**/
	SPI_u8MasterTransmitter(maskAddress);
	if(IsExtended)
	{
		/*			*/
		SPI_u8MasterTransmitter((u8)(data >> 3));
		SPI_u8MasterTransmitter((u8)(data << 5) | (1<<3) | (u8)(data >> 27));
		/*			Here we write in the extender HIGH bits		*/
		SPI_u8MasterTransmitter((u8)(data >> 19));
		SPI_u8MasterTransmitter((u8)(data << 11));
	}
	else
	{
		SPI_u8MasterTransmitter((u8)(data >> 3));
		SPI_u8MasterTransmitter((u8)(data << 5));

	}
	SPI_voidChipSelect(0);

}




