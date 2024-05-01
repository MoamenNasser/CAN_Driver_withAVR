/*
 * HLCD_Interface.h
 *
 *  Created on: Sep 24, 2021
 *      Author: naser
*/

#ifndef HLCD_INTERFACE_H_
#define HLCD_INTERFACE_H_

/* 		LCD control Commands								*/
#define HLCD_CLR              0x01
#define HLCD_HOME             0x02
#define HLCD_ENTRYMODE        0x06
#define HLCD_DISSOFF          0x08
#define HLCD_DISPON_CURSON    0x0E
#define HLCD_FUNCRESET        0x30
#define HLCD_FUNCSET_8BIT     0x38
#define HLCD_SETCURSOR        0x80
#define HLCD_DISPON_CURSBLINK 0x0F
#define HLCD_DISPON_CURSOFF   0x0C


/***********************************************
 *
 * 		This function send the character
 *
 ********************************************************/
void HLCD_VoidSendChar(u8 Copy_u8Data);

/*******************************************************
 *
 * 		This function send command
 *
 ********************************************************/
void HLCD_VoidSendCommand(u8 Copy_u8Command);

/********************************************************
 *
 * 		This function write string
 *
 *********************************************************/
void HLCD_VoidWriteStr(u8 * pu8str);

/*********************************************************
 *
 * 		This function go to exact x and y
 *
 *********************************************************/
void HLCD_GoToXY(u8 x,s8 y);

/**********************************************************
 *
 * 		Initialization function
 *
 ***********************************************************/
void HLCD_enuInit(void);

/*********************************************************
 *
 * 		To Send an integer  number
 *
 **********************************************************/
void HLCD_VoidSendNumber(u32 Number);

/********************************************************
 *
 * 		To Send a float number
 *
 *********************************************************/
void HLCD_SendFloatNumber(f32 Copy_f32Number);

/********************************************************
 * 		This function clear all the content on the LCD
 *
 ********************************************************/
void HLCD_ClearDisplay(void);

/********************************************************
 * 		This function draw character E
 *
 ********************************************************/
void HLCD_DrawCharacterE(void);

/******************************************************
 *
 * 		This draw character F
 *
 *******************************************************/
void HLCD_DrawCharacterF(void);

/*******************************************************
 *
 * 		This function store custom character
 *
 ********************************************************/
void HLCD_StoreCustomCharacter(u8 Copy_char_Index, u8 * Copy_Pattern);

/*******************************************************
 *
 * 		This function draw a human on the screen
 *
 *******************************************************/
void HLCD_DrawHuman(void);

/******************************************************
 *
 * 		This function set the cursor to exact position
 *
 ******************************************************/
void HLCD_SetCursor(u8 Line, u8 Cell);

/****************************************************
 *
 * 		this function shift the display to the left
 *
 *****************************************************/
void HLCD_ShiftDisplayLeft();

/*****************************************************
 *
 * 		this function shift the display to the right
 *
 * ***************************************************/
void HLCD_ShiftDisplayRight();

/****************************************************
 **
 * 		this function write the number on the LCD as 4D
 *
 * **************************************************/
void HLCD_WriteNumber_4D(s32 Number);

/***************************************************
 *
 * 		This function shift the cursor to the left
 *
 * **************************************************/
void HLCD_ShiftCursorLeft(void);

/***************************************************
 *
 * 		This function shift the cursor to the right
 *
 * **************************************************/
void HLCD_ShiftCursorRight(void);

/*****************************************************
 *
 * 		This function write a number on the LCD as hex
 *
 ***************************************************** */
void HLCD_WriteHexNumber(u8 Number);

/*****************************************************
 *
 * 		This function Write a number in the LCD as a binary form
 *
 * *****************************************************/
void HLCD_WriteBinaryNumber(u8 Number);

/**/
void HLCD_AnimateString(u8 * str);

#endif /* HLCD_INTERFACE_H_ */
