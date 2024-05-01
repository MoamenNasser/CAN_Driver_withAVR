/*
 * 		HLCD_Program.c
 *		V2.0
 *  	Created on: Sep 24, 2021
 *      Author: Moamen Nasser Saad
 *
 */

#include"STD_TYPES.h"
#include<avr/delay.h>
#include "HLCD_CNF.h"
#include"MDIO_interface.h"
#include"MDIO_Private.h"
#include"HLCD_Interface.h"


/*********************************************************************
 *
 *					This Function send a character to the LCD
 *
 **********************************************************************/
void HLCD_VoidSendChar(u8 Copy_u8Data)
{
	/*								set RS pin							*/
	MDIO_VoidSetPinValue(HLCD_CONTROL_PORT,HLCD_RS_PIN,DIO_PIN_HIGH);
	/*								clear RW pin						*/
	/*				here we set the pin value to port B pin 1 to 0v		*/
	MDIO_VoidSetPinValue(HLCD_CONTROL_PORT,HLCD_RW_PIN,DIO_PIN_LOW);

	/*				here we set the port C to the given data			*/
	MDIO_VoidSetPortValue(HLCD_DATA_PORT, Copy_u8Data);
	/*				set E pin to HIGH									*/
	/*				here we set the pin value to port B pin 0 to 5v		*/
	MDIO_VoidSetPinValue(HLCD_CONTROL_PORT,HLCD_E_PIN,DIO_PIN_HIGH);
	/*				Delay Function for 10 microsecond					*/
	_delay_ms(1);
	/*							clear E pin								*/
	/*		here we set the pin value to port B pin 2 to 5v				*/
	MDIO_VoidSetPinValue(HLCD_CONTROL_PORT,HLCD_E_PIN,DIO_PIN_LOW);
	/*Delay Function for 1ms to make sure that the LCD complete the task*/
	_delay_ms(4);

}


/**********************************************************************
 *
 *		This Function send a command to the LCD
 *
 ************************************************************************/
void HLCD_VoidSendCommand(u8 Copy_u8Command)
{
	/*					clear Rs pin									*/
	MDIO_VoidSetPinValue(HLCD_CONTROL_PORT,HLCD_RS_PIN,DIO_PIN_LOW);
	/*					clear RW pin									*/
	/*			here we set the pin value to port B pin 1 to 0v			*/
	MDIO_VoidSetPinValue(HLCD_CONTROL_PORT,HLCD_RW_PIN,DIO_PIN_LOW);

	/*			Delay Function for 10 microsecond						*/
	/*			here we set the port C to the given data				*/
	MDIO_VoidSetPortValue(HLCD_DATA_PORT, Copy_u8Command);
	/*				set E pin to HIGH									*/
	/*			here we set the pin value to port B pin 0 to 5v			*/
	MDIO_VoidSetPinValue(HLCD_CONTROL_PORT,HLCD_E_PIN,DIO_PIN_HIGH);
	_delay_ms(1);
	/*					clear E pin										*/
	/*			here we set the pin value to port B pin 2 to 5v			*/
	MDIO_VoidSetPinValue(HLCD_CONTROL_PORT,HLCD_E_PIN,DIO_PIN_LOW);
	/*Delay Function for 1ms to make sure that the LCD complete the task*/
	_delay_ms(4);
}

/*********************************************************************
 *
 * 		Here we initialize each port direction and every pin we need
 *
 **********************************************************************/
void HLCD_enuInit(void)
{
	MDIO_VoidSetPortDirection(DIO_PORTC,DIO_PORT_HIGH);
	/**/
	MDIO_VoidSetPinDirection(DIO_PORTB,DIO_PIN0,DIO_PIN_HIGH);
	/**/
	MDIO_VoidSetPinDirection(DIO_PORTB,DIO_PIN1,DIO_PIN_HIGH);
	/**/
	MDIO_VoidSetPinDirection(DIO_PORTB,DIO_PIN2,DIO_PIN_HIGH);


#if HLCD_INIT_MODE == HLCD_8_BIT_MODE

		/*					Delay for 30ms									*/
		_delay_ms(50);
		/*					set Port c to output							*/
		HLCD_VoidSendCommand(0b00111000);
		_delay_ms(1);
		/*					set port b pin number 0 to high					*/
		HLCD_VoidSendCommand(0b00001111);
		/*					Delay for 1ms									*/
		_delay_ms(1);
		HLCD_VoidSendCommand(0b00000000);
		/*					Delay for 2ms									*/
		_delay_ms(2);



#elif HLCD_INIT_MODE == HLCD_4_BIT_MODE

		_delay_ms(40);
		/*							Clear RW												*/
		MDIO_VoidSetPinValue(HLCD_CONTROL_PORT,HLCD_RW_PIN,DIO_PIN_LOW);
		/*							Clear RS												*/
		MDIO_VoidSetPinValue(HLCD_CONTROL_PORT,HLCD_RW_PIN,DIO_PIN_LOW);
		/*
		 * 							Send 4 bits high of the function set command
		 * 																					*/
		MDIO_VoidSetPortValue(HLCD_DATA_PORT,0b00100000);
/*
		MDIO_VoidSetPinValue(HLCD_CONTROL_PORT,HLCD_RW_PIN,DIO_PIN_LOW);
		MDIO_VoidSetPinValue(HLCD_CONTROL_PORT,HLCD_RW_PIN,DIO_PIN_LOW);
		MDIO_VoidSetPinValue(HLCD_CONTROL_PORT,HLCD_RW_PIN,DIO_PIN_LOW);
		MDIO_VoidSetPinValue(HLCD_CONTROL_PORT,HLCD_RW_PIN,DIO_PIN_LOW);
*/
		/*							Enable Latch											*/
		MDIO_VoidSetPinValue(HLCD_CONTROL_PORT,HLCD_E_PIN,DIO_PIN_HIGH);
		/*							Delay for 1 milliseconds								*/
		_delay_ms(1);
		/**/
		MDIO_VoidSetPinValue(HLCD_CONTROL_PORT,HLCD_E_PIN,DIO_PIN_LOW);
		/*							Function Set Command									*/
		HLCD_VoidSendCommand(0b00101000);
		/*							Delay for 40 microseconds								*/
		_delay_us(40);
		/*							make the LCD Blink										*/
		HLCD_VoidSendCommand(0x0C);
		/*							Delay for 40 microseconds								*/
		_delay_us(40);
		/*							*/
		HLCD_VoidSendCommand(0x01);
		/*							Delay for 2 milliseconds								*/
		_delay_ms(2);
		/*							*/
		HLCD_VoidSendCommand(0b00000110);

#endif

}


/*********************************************************************
 *
 *		This function write the whole string in the LCD
 *
 **********************************************************************/
void HLCD_VoidWriteStr(u8 * pu8str)
{
	/*Null terminator is very important that helps me a lot*/
	u8 i = 0;
	/*			Here we loop till the null terminator				*/
	while(pu8str[i] != 0)
	{
		/*Send the character to the LCD in each iteration till the end*/
		HLCD_VoidSendChar(pu8str[i]);
		i++;
	}

}


/*********************************************************************
 *
 * Function to go to special position of the col
 *
 *********************************************************************/
void HLCD_GoToXY(u8 x,s8 y)
{
	/*			here we check the x if it's 1 or 2					*/
	switch(x)
	{
		/* 		0x80 === 127 decimal		*/
		case 1: HLCD_VoidSendCommand(y + 127); break;
		/* 		0xBF === 191 decimal		*/
		case 2: HLCD_VoidSendCommand(y + 191); break;
	}
}


/*******************************************************************
 *
 * This function send an int number to the LCD
 *
 ********************************************************************/
void HLCD_VoidSendNumber(u32 Number)
{
	if(Number == 0)
	{
		/*					Here Print the zero						*/
	}
	else
	{
		/*			Looping if the number is positive only 			*/
		u32 reverse = 1;
		while(Number > 0)
		{
			/*	Here we reverse the number to display it on screen	*/
			reverse = (reverse * 10) + (Number  % 10);
			Number = Number / 10;
		}
		/*		Check if the reverse number is bigger than 1 or not */
		while(reverse > 1)
		{
			u32 remainder;
			remainder = reverse % 10;
			/*		Send the number to the LCD as a character		*/
			HLCD_VoidSendChar(remainder + 48);
			reverse = reverse / 10;
		}
	}
}

/**************************************************************
 *
 * 		This function send an float number to the LCD
 *
 *************************************************************/
void HLCD_SendFloatNumber(f32 Copy_f32Number)
{
	f32 Local_f32FloatR;
	s32 Local_s32CopyNumber = (u32) Copy_f32Number;
	HLCD_VoidSendNumber(Local_s32CopyNumber);
	HLCD_VoidSendChar('.');

	Local_f32FloatR = (f32) Copy_f32Number - Local_s32CopyNumber;
	/*				Check if the number is negative we need to get off the sign						*/
	if(Copy_f32Number < 0)
	{
		Local_f32FloatR = (f32) (-1) * (Local_f32FloatR);
	}
	HLCD_VoidSendNumber((u32) Local_f32FloatR);
}


/*************************************************************
 *
 * This function Draw shape E without the left
 *
 *************************************************************/
void HLCD_DrawCharacterE(void)
{
	HLCD_GoToXY(0,0);
	HLCD_VoidSendCommand(0b01000000);
	HLCD_VoidSendCommand(0b01110);
	HLCD_VoidSendCommand(0b01010);
	HLCD_VoidSendCommand(0b01110);
	HLCD_VoidSendCommand(0b00010);
	HLCD_VoidSendCommand(0b00010);
	HLCD_VoidSendCommand(0b01110);
	HLCD_VoidSendCommand(0b00000);
	HLCD_VoidSendCommand(0b00000);
	HLCD_VoidSendChar(0);

}


/**************************************************************
 *
 * 		This function clear all the characters on the screen
 *
 * ***********************************************************/
void HLCD_ClearDisplay(void)
{
	HLCD_VoidSendCommand(1);
}


/***********************************************************
 *
 * This function print F character on the screen
 *
 ************************************************************/
void HLCD_DrawCharacterF(void)
{
	HLCD_GoToXY(0,3);
	HLCD_VoidSendCommand(0b01000011);
	HLCD_VoidSendCommand(0b00110);
	HLCD_VoidSendCommand(0b00100);
	HLCD_VoidSendCommand(0b01110);
	HLCD_VoidSendCommand(0b00100);
	HLCD_VoidSendCommand(0b00100);
	HLCD_VoidSendCommand(0b00100);
	HLCD_VoidSendCommand(0b00100);
	HLCD_VoidSendCommand(0b00100);
	HLCD_VoidSendChar(0);
}


/**********************************************************
 *
 * This function draw a human
 *
 ***********************************************************/
void HLCD_DrawHuman(void)
{
	HLCD_VoidSendCommand(0b01000010);
	HLCD_GoToXY(1,5);
	HLCD_VoidSendCommand(0b00100);
	HLCD_VoidSendCommand(0b01010);
	HLCD_VoidSendCommand(0b01110);
	HLCD_VoidSendCommand(0b00100);
	HLCD_VoidSendCommand(0b01110);
	HLCD_VoidSendCommand(0b10101);
	HLCD_VoidSendCommand(0b00100);
	HLCD_VoidSendCommand(0b00100);
	HLCD_VoidSendChar(0);
}


/****************************************************************************
 *
 * 		This is a private function that get the power of a number
 *
 ****************************************************************************/
s32 HLCD_S32Private_GetPower(u8 Copy_u8BaseNumber, u8 Copy_PowerNumber)
{
	u8 Copy_u8Counter = Copy_PowerNumber;
	u8 Copy_u8NumberAfterPower = 0;
	while(Copy_u8Counter != 0)
	{
		Copy_u8NumberAfterPower = Copy_u8BaseNumber * Copy_u8BaseNumber;
		Copy_u8Counter--;
	}
}


/***************************************************************************
 *
 * 		This function stores a custom pattern passed by an array
 *
 ***************************************************************************/
void HLCD_StoreCustomCharacter(u8 Copy_char_Index, u8 * Copy_Pattern)
{
	u8 Local_CGRAMAdd = Copy_char_Index * 8;
	/*			Set CGRAM address										*/
	HLCD_VoidSendCommand(0b01000000 + Local_CGRAMAdd);
	/*			put the pattern in CGRAM								*/
	for(u8 Local_Counter = 0; Local_Counter < 8; Local_Counter++)
	{
		HLCD_VoidSendChar(Copy_Pattern[Local_Counter]);
	}
}


/**************************************************************************
 *
 * 		This Function Shift the display to the left
 *
 ***************************************************************************/
void HLCD_ShiftDisplayLeft()
{
	HLCD_VoidSendCommand(0b000110);
	_delay_ms(2);
}



/**************************************************************************
 *
 * 		This Function Shift the display to the right
 *
 **************************************************************************/
void HLCD_ShiftDisplayRight()
{
	HLCD_VoidSendCommand(0b000111);
	_delay_ms(2);
}


/***************************************************
 *
 * 		This function shift the cursor to the left
 *
 * **************************************************/
void HLCD_ShiftCursorLeft(void)
{
	HLCD_VoidSendCommand(0b000100);
	_delay_ms(2);
}


/***************************************************
 *
 * 		This function shift the cursor to the right
 *
 * **************************************************/
void HLCD_ShiftCursorRight(void)
{
	HLCD_VoidSendCommand(0b000101);
	_delay_ms(2);
}


/*****************************************************
 *
 * 		This function write a number on the LCD as hex
 *
 ***************************************************** */
void HLCD_WriteHexNumber(u8 Number)
{
    /*				char array to store hexadecimal number				*/
    u8 Copy_u8HexaDeciNum[100];
    /*				counter for hexadecimal number array				*/
    u8 Copy_u8Counter = 0;
    while (Number != 0)
    {
        /*			temporary variable to store remainder				*/
        u8 Copy_u8tempVariable = 0;

        /*			storing remainder in Copy_u8tempVariable 			*/
        Copy_u8tempVariable = Number % 16;

        /*			check if Copy_u8tempVariable < 10					*/
        if (Copy_u8tempVariable < 10)
        {
            Copy_u8HexaDeciNum[Copy_u8Counter] = Copy_u8tempVariable + 48;
            Copy_u8Counter++;
        }
        else
        {
        	Copy_u8HexaDeciNum[Copy_u8Counter] = Copy_u8tempVariable + 55;
        	Copy_u8Counter++;
        }
        Number = Number / 16;
    }
    for (u8 Copy_u8Counterloop = Copy_u8Counter - 1; Copy_u8Counterloop >= 0; Copy_u8Counterloop--)
    {
    	HLCD_VoidSendNumber(Copy_u8HexaDeciNum[Copy_u8Counterloop]);
    }
}


/*******************************************************************
 *
 * 		This function Write a number in the LCD as a binary form
 *
 * ******************************************************************/
void HLCD_WriteBinaryNumber(u8 Number)
{
    /*				char array to store Binary number					*/
    u8 Copy_u8BinaryDeciNum[100];

    for(u8 Copy_u8Counter = 0; Number > 0; Copy_u8Counter++)
    {
    	/*			Getting the Mod of base 2 to convert into binary	*/
    	Copy_u8BinaryDeciNum[Copy_u8Counter] = Number % 2;
    	Number = Number / 2;
    	/*			Sending the number to the LCD						*/
    	HLCD_VoidSendNumber(Copy_u8BinaryDeciNum[Copy_u8Counter]);
    }
}


/************************************************************************
 *
 * 			This function animate the string from left to right and the
 * 			last character in the string start from the beginning
 * 			of the LCD
 *
 ***********************************************************************/
void HLCD_AnimateString(u8 * str)
{

	static s8 Copy_iCounter = -1;
	/*			Looping on the string to make the animation on it		*/
	for(; Copy_iCounter <= 15; Copy_iCounter++)
	{
		/*		Set the cursor to the beginning							*/
		HLCD_GoToXY(1,Copy_iCounter);
		HLCD_VoidWriteStr(str);
		/*
		 * check if the counter bigger then the length of the
		 * 								character
		 *																*/
		if(Copy_iCounter > 10)
		{
			/*		Set the string from the first row and last column	*/
			HLCD_GoToXY(1, Copy_iCounter - 15);
			/*		Send the String to the LCD							*/
			HLCD_VoidWriteStr(str);
		}
		/*						Wait for 200ms 							*/
		_delay_ms(200);
		/*				Clear all the display							*/
		HLCD_ClearDisplay();
	}
	/*				Start the counter from the beginning				*/
	Copy_iCounter = 1;
}


/**/


