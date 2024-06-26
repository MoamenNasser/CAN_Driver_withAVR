/*
 * SPI_Interface.h
 *
 *  Created on: Nov 15, 2021
 *      Author: naser
 */

#ifndef SPI_INTERFACE_H_
#define SPI_INTERFACE_H_


/********************************************************************************************
 *
 * 							Function to initialize the MASTER OF THE SPI
 *
 *******************************************************************************************/
void SPI_VoidMasterInit(void);

/********************************************************************************************
 *
 * 							Function to transmit Data from the SPI
 *
 *******************************************************************************************/
u8 SPI_u8MasterTransmitter(u8 Copy_u8DataByte);

/********************************************************************************************
 *
 * 							Function to initialize the SLAVE OF THE SPI
 *
 *******************************************************************************************/
void SPI_VoidSlaveInit(void);


/********************************************************************************************
 *
 * 							Function to Receive Data from the SPI
 *
 *******************************************************************************************/
u8 SPI_VoidSlaveReceiver(void);

/********************************************************************************************
 *
 * 							Function to select the state
 *
 *******************************************************************************************/
void SPI_voidChipSelect(u8 state);


#endif /* SPI_INTERFACE_H_ */
