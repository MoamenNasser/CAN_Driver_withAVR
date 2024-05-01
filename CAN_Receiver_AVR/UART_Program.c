/*
 * UART_Program.c
 *
 *  Created on: Nov 3, 2021
 *      Author: naser
 */
#include"STD_TYPES.h"
#include"BIT_MATH.h"
#include"UART_Interface.h"
#include"UART_Private.h"
#include"CNF.h"


u8 UCSRC_HELP = 0;
/*****************************************************************************************************************************
 *
 * 							Function to initialize the UART
 *
*****************************************************************************************************************************/
void UART_VoidInit(void)
{
	/*						NORMAL SPEED													*/
	CLR_BIT(UCSRA,U2X);
	/**/
	UBRRL = 51;
	/**/
	SET_BIT(UCSRB,RXEN);
	SET_BIT(UCSRB,TXEN);

	/*						No parity BITS*/
	SET_BIT(UCSRC_HELP,7);
	CLR_BIT(UCSRC_HELP,6);
	CLR_BIT(UCSRC_HELP,5);
	CLR_BIT(UCSRC_HELP,4);
	CLR_BIT(UCSRC_HELP,3);
	SET_BIT(UCSRC_HELP,1);
	SET_BIT(UCSRC_HELP,2);
	/*						Assign the HELP variable to the register						*/
	UCSRC = UCSRC_HELP;

}

/*****************************************************************************************************************************
 *
 * 							Function to transmit Data from the UART
 *
*****************************************************************************************************************************/
void UART_VoidTransmitter(u8 Copy_u8DataByte)
{
	/*						8 BIT MODE														*/
#if UART_MODE == EIGHT_BIT_MODE
	/*
	 * 						WE NEED TO WAIT FOR THE DATA TO BE
	 * 						TRANSMITTED AND BUFFER IS EMPTY
	 * 																						*/
	UDR = Copy_u8DataByte;
	while(!GET_BIT(UCSRA,UDRE));
	/*						PUT THE SEND DATA INTO THE UDR DATA REGISTER					*/

#endif

	/*						9 BIT MODE														*/
#if UART_MODE == NINE_BIT_MODE
	/*
	 * 						WE NEED TO WAIT FOR THE DATA TO BE
	 * 						TRANSMITTED AND BUFFER IS EMPTY
	 * 																						*/
	while(!GET_BIT(UCSRA,UDRE));
	/*						PUT THE SEND DATA INTO THE UDR DATA REGISTER					*/
	/* 						Copy 9th bit to TXB8 											*/
	CLR_BIT(UCSRB,TXB8);
	if ( Copy_u8DataByte & 0x0100 )
		SET_BIT(UCSRB,TXB8);
	/* 						Put data into buffer, sends the data							 */
	UDR = Copy_u8DataByte;
#endif
}
/*****************************************************************************************************************************
 *
 * 							Function to Receive Data from the UART
 *
*****************************************************************************************************************************/
u8 UART_VoidReceiver(void)
{
	/*
	 * 						WE NEED TO WAIT FOR THE DATA TO BE
	 * 						TRANSMITTED AND BUFFER IS EMPTY
	 * 																						*/
	while(!GET_BIT(UCSRA,RXC));
	/*						return THE SEND DATA THE UDR DATA REGISTER					*/
	return UDR ;
}

/*****************************************************************************************************************************
 *
 * 							Function to Receive PeriodicChecking the UART
 *
*****************************************************************************************************************************/
u8 UART_u8Receive_PeriodicChecking(u8 * Copy_u8ptrData)
{
	/*						Checking if the data received or not 							*/
	if(GET_BIT(UCSRA,RXC))
	{
		/*					Put the Data inside the pointer									*/
		*Copy_u8ptrData = UDR;
		return 1;
	}
	else
	{
		/*					Return 0 if the data didn't receive								*/
		return 0;
	}
}

/*****************************************************************************************************************************
 *
 * 							Function to enable interrupt for the receiver of the UART
 *
 *****************************************************************************************************************************/
void UART_RX_InterruptEnable(void)
{
	/*						Set the bit to 1 RXCIE: RX Complete Interrupt Enable			*/
	SET_BIT(UCSRB,RXCIE);
}

/*****************************************************************************************************************************
 *
 * 							Function to disable interrupt for the receiver of the UART
 *
*****************************************************************************************************************************/
void UART_RX_InterruptDisable(void)
{
	/*						Clear the bit to 1 RXCIE: RX Complete Interrupt Disable			*/
	CLR_BIT(UCSRB,RXCIE);
}

/*****************************************************************************************************************************
 *
 * 							Function to enable interrupt for the transmitter of the UART
 *
*****************************************************************************************************************************/
void UART_TX_InterruptEnable(void)
{
	/*						Set the bit number 6 to 1 TXCIE: TX Complete Interrupt Enable		*/
	SET_BIT(UCSRB,TXCIE);
}

/*****************************************************************************************************************************
 *
 * 							Function to disable interrupt for the transmitter of the UART
 *
 *****************************************************************************************************************************/
void UART_TX_InterruptDisable(void)
{
	/*						Clear the bit number 6 to 1 TXCIE: TX Complete Interrupt Disable	*/
	CLR_BIT(UCSRB,TXCIE);
}



/*****************************************************************************************************************************
 *
 * 							Function for setting the callback receiver
 *
*****************************************************************************************************************************/
void UART_RX_SetCallBack(void (*LocalEptr)(void))
{
	/**/
}


/*****************************************************************************************************************************
 *
 * 							Function for setting the callback transmitter
 *
 ******************************************************************************************************************************/
void UART_TX_SetCallBack(void (*LocalEptr)(void))
{

}


/*****************************************************************************************************************************
 *
 * 							Function for sending the number of block in UART
 *
 ******************************************************************************************************************************/
void UART_SendNumberOfBlock(u8 Copy_u8Data)
{
	UDR = Copy_u8Data;
}

/*****************************************************************************************************************************
 *
 * 							Function for receive the number of block in UART
 *
 *****************************************************************************************************************************/
u8 UART_u8ReceiveNumberOfBlock(void)
{
	return UDR;
}


/*****************************************************************************************************************************
 *
 * 							Function for sending a string in UART
 *
 *****************************************************************************************************************************/
void UART_VoidSendString(u8 * Copy_u8String)
{
	/**/
	u8 Local_u8Counter;
	for(Local_u8Counter = 0; Copy_u8String[Local_u8Counter] ; Local_u8Counter++)
	{
		/*					Sending each byte using the transmit function								*/
		UART_VoidTransmitter(Copy_u8String[Local_u8Counter]);
	}
	UART_VoidTransmitter("#");
}



/*****************************************************************************************************************************
 *
 * 							Function for receiving a string in UART
 *
 *****************************************************************************************************************************/
void UART_VoidReceiveString(u8 * Copy_u8String)
{
	/*						initialize a counter and polling on the string 								*/
	u8 Local_u8Counter = 0;
	Copy_u8String[Local_u8Counter] = UART_VoidReceiver();
	for(; Copy_u8String[Local_u8Counter] != 'A'; )
	{
		Local_u8Counter++;
		/*					Receiving each byte using the receive function								*/
		Copy_u8String[Local_u8Counter] = UART_VoidReceiver();
	}
	Copy_u8String[Local_u8Counter] = 0;
}

