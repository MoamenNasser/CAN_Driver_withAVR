/*
 * CAN_Interface.h
 *
 *  Created on: Apr 29, 2024
 *      Author: Moamen
 */

#ifndef CAN_INTERFACE_H_
#define CAN_INTERFACE_H_


/**/
u8 CAN_u8ReadRegister(u8 address);


/**/
void CAN_voidWriteRegister(u8 address, u8 Data);

/*		Function to reset 		*/
void CAN_voidReset();


/*			Function to modify bits*/
void CAN_voidModify(u8 address, u8 mask, u8 Data);


/*			Function to set BIT timing 		Very important		*/
void CAN_voidSetBitTiming(u8 CNF1VAL, u8 CNF2VAL, u8 CNF3VAL);

/*		Function to set MODE of operation		*/
void CAN_voidSetMode(u8 mode);

/*			Function to initialize the CAN			*/
void CAN_voidInit_Recevier(void);

/**/
void CAN_voidSendMessage(u8 bufferIndex, u32 MessageID, u8 DLC, u8 * data);




#endif /* CAN_INTERFACE_H_ */
