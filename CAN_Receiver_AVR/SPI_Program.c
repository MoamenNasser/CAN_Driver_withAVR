/*
 * SPI_Program.c

 *
 *  Created on: Nov 15, 2021
 *      Author: naser
 */
#include"STD_TYPES.h"
#include"BIT_MATH.h"
#include"SPI_Interface.h"
#include"SPI_Private.h"
#include"MDIO_interface.h"
#include"MDIO_Private.h"
#include"SPI_CNF.h"




/********************************************************************************************
 *
 * 							Function to initialize the MASTER OF THE SPI
 *
 *******************************************************************************************/
void SPI_VoidMasterInit(void)
{
	/*						SET MOSI AND SCK PINS AS OUTPUTS ALL OTHER AS INPUT				*/
	SET_BIT(PORTB_REG,PORTB_PIN5_MOSI);
	SET_BIT(PORTB_REG,PORTB_PIN7_SCK);
	/*						ENABLE SPI MASTER , SET CLOCK RATE TO FCLK/16					*/
	/*						SPE must be set for any SPI operation							*/
	SET_BIT(SPCR,SPE);
	/*						DATA ORDER LSB TRANSMITTED FIRST								*/
	#if SPI_DATA_ORDER == LSB_FIRST
		SET_BIT(SPCR,DORD);

	/*						DATA ORDER MSB TRANSMITTED FIRST								*/
	#else if SPI_DATA_ORDER == MSB_FIRST
			CLR_BIT(SPCR,DORD);
	#endif
	/*				Configure SPI SS pin as output 				*/
	MDIO_VoidSetPinDirection(DIO_PORTB, DIO_PIN4, DIO_OUTPUT);
	MDIO_VoidSetPinValue(DIO_PORTB, DIO_PIN4, DIO_PIN_HIGH);

	/*						SET MSTR BIT TO CHOOSE THE MASTER MODE							*/
	#if SPI_MODE == MASTER_MODE
		SET_BIT(SPCR,MSTR);

	/*						SET MSTR BIT TO CHOOSE THE SLAVE MODE							*/
	#else if SPI_MODE == SLAVE_MODE
		CLR_BIT(SPCR,MSTR);
	#endif

	/*		Clock Polarity >> Leading rising Edge			*/
	CLR_BIT(SPCR, CPOL);
	/*		Clock phase >> sampling at rising edge			*/
	CLR_BIT(SPCR, CPHA);

	/*		Clock oscillator	>> FCPU / 4		*/
	CLR_BIT(SPCR, SPR1);
	CLR_BIT(SPCR, SPR0);
	CLR_BIT(SPSR, SPI2X);



}

/********************************************************************************************
 *
 * 							Function to transmit Data from the SPI
 *
 *******************************************************************************************/
u8 SPI_u8MasterTransmitter(u8 Copy_u8DataByte)
{
	u8 Localu8Help;
	/**/
	SPDR = Copy_u8DataByte;
	/*						Flag won't clear until we read the SPDR*/
	while(!CLR_BIT(SPSR,SPIF));
	/**/
	Localu8Help = SPDR;
	/**/
	return Localu8Help;

}

/********************************************************************************************
 *
 * 							Function to initialize the SLAVE OF THE SPI
 *
 *******************************************************************************************/
void SPI_VoidSlaveInit(void)
{
	/*		Enable SPI		*/
	SET_BIT(SPCR, SPE);
	/*		Data Order Least Segnificant bit first		*/
	SET_BIT(SPCR, DORD);
	/*				Configure SPI SS pin as output 				*/
	MDIO_VoidSetPinDirection(DIO_PORTB, DIO_PIN4, DIO_INPUT);
	MDIO_VoidSetPinValue(DIO_PORTB, DIO_PIN4, DIO_PIN_HIGH);

	/*						SET MSTR BIT TO CHOOSE THE MASTER MODE							*/
	#if SPI_MODE_INCASE_SLAVE == MASTER_MODE
		SET_BIT(SPCR,MSTR);

	/*						SET MSTR BIT TO CHOOSE THE SLAVE MODE							*/
	#else if SPI_MODE_INCASE_SLAVE == SLAVE_MODE
		CLR_BIT(SPCR,MSTR);
	#endif

	/*		Clock Polarity >> Leading rising Edge			*/
	CLR_BIT(SPCR, CPOL);
	/*		Clock phase >> sampling at rising edge			*/
	CLR_BIT(SPCR, CPHA);

	/*		Clock oscillator	>> FCPU / 4		*/
	CLR_BIT(SPCR, SPR1);
	CLR_BIT(SPCR, SPR0);
	CLR_BIT(SPSR, SPI2X);
}


/********************************************************************************************
 *
 * 							Function to Receive Data from the SPI
 *
 *******************************************************************************************/
u8 SPI_VoidSlaveReceiver(void)
{
	/**/
	while(!CLR_BIT(SPSR,SPIF));
	/**/
	return SPDR;


}

/*		*/
void SPI_voidChipSelect(u8 state)
{
	if(state == 1)
	{
		MDIO_VoidSetPinValue(DIO_PORTB, DIO_PIN4, DIO_PIN_LOW);
	}
	else
	{
		MDIO_VoidSetPinValue(DIO_PORTB, DIO_PIN4, DIO_PIN_HIGH);
	}
}

/********************************************************************************************
 *
 * 							Function to ENABLE THE INTERRUPT OF the SPI
 *
 *******************************************************************************************/
void SPI_VoidInterruptEnable(void)
{
	/*						SET the SPIE PIN 												*/
	SET_BIT(SPCR,SPIE);

}


/********************************************************************************************
 *
 * 							Function to ENABLE THE INTERRUPT OF the SPI
 *
 *******************************************************************************************/
u8 SPI_u8ReadData(void)
{
	/*						Dummy value to push the old data out 							*/
	SPDR = 0xFF;
	/*						Check the value of the flag*/
	while(!CLR_BIT(SPSR,SPIF));
	/**/
	return SPDR;

}
