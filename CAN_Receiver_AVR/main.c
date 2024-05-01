/*
 * main.c
 *
 *  Created on: Nov 15, 2021
 *      Author: naser
 */
#include"STD_TYPES.h"
#include"BIT_MATH.h"
#include"MDIO_interface.h"
#include "MDIO_Private.h"
#include"HLCD_Interface.h"
#include"SPI_Interface.h"
#include "UART_Interface.h"
#include "CAN_Interface.h"
#include"avr/delay.h"
#include "util/delay.h"


extern u8 ArrayToReceiveMessage[];

int main(void)
{

	CAN_voidInit_Recevier();
	UART_VoidInit();
	MDIO_VoidSetPinDirection(DIO_PORTD, DIO_PIN2, DIO_INPUT);
	u8 dataR = 0;

	while(1)
	{
		if(MDIO_u8GetPinValue(DIO_PORTD, DIO_PIN2) == 0)
		{
			CAN_voidReceiveMessage();

			for(u8 i =0;i<8;i++)
			{
				/*			first 6 register we don't need them so we start from the index 6 == data element 7*/
				dataR = ArrayToReceiveMessage[6+i];
				/*		sending data		*/
				UART_VoidTransmitter(dataR);

			}
			UART_VoidTransmitter('\r');
			UART_VoidTransmitter('\n');

		}
		/**/

	}
	_delay_ms(1000);

	return 0;

}

