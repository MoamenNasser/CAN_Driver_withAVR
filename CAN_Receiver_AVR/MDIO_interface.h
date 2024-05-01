/*
 * MDIO_interface.h
 *
 *  Created on: Sep 24, 2021
 *      Author: naser
 */

#ifndef MDIO_INTERFACE_H_
#define MDIO_INTERFACE_H_

#include"STD_TYPES.h"
#include"BIT_MATH.h"


void MDIO_VoidSetPinDirection(u8 Copy_u8Port ,u8 Copy_u8Pin, u8 Copy_u8Direc);
void MDIO_VoidSetPinValue(u8 Copy_u8Port ,u8 Copy_u8Pin, u8 Copy_u8Value);
u8 MDIO_u8GetPinValue(u8 Copy_u8Port ,u8 Copy_u8Pin);
void MDIO_VoidSetPortDirection(u8 Copy_u8Port, u8 Copy_u8Direc);
void MDIO_VoidSetPortValue(u8 Copy_u8Port ,u8 Copy_u8Value);
void MDIO_VoidTogglePin(u8 Copy_u8Port ,u8 Copy_u8Pin);
void MDIO_VoidEnablePullUpResistor(u8 Copy_u8Port,u8 Copy_u8Pin);




#endif /* MDIO_INTERFACE_H_ */
