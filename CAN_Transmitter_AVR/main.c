/*
 * main.c
 *
 *  Created on: Nov 15, 2021
 *      Author: naser
 */
#include"STD_TYPES.h"
#include"BIT_MATH.h"
#include"MDIO_interface.h"
#include"HLCD_Interface.h"
#include"SPI_Interface.h"
#include"CAN_Interface.h"
#include"avr/delay.h"
#include"util/delay.h"

int main(void)
{
	/*		Initializing CAN master to transmit			*/
	CAN_voidInit();
	u8 msgData[14] = {'a','b','c','c','v','d','d','e'};

	while(1)
	{
		CAN_voidSendMessage(0, 0x7E1, msgData, 8);
		for(u8 i = 0 ; i < 8 ; i++)
		{
			msgData[i]++;

		}

	}

	_delay_ms(1000);



	return 0;

}

