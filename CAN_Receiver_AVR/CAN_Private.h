/*
 * CAN_Private.h
 *
 *  Created on: Apr 29, 2024
 *      Author: Moamen
 */

#ifndef CAN_PRIVATE_H_
#define CAN_PRIVATE_H_


/**************************************************************************************************
 *
 *			 CAN CONTROLLER REGISTER MAP
 *
 **************************************************************************************************/
#define		TXB0CTRL		0x30
#define		TXB1CTRL		0x40
#define		TXB2CTRL		0x50





/**************************************************************************************************
 *
 * 			MACRO for EFLG: ERROR FLAG REGISTER (ADDRESS: 2Dh)
 *
 * 			Legend:
		R = Readable bit W = Writable bit U = Unimplemented bit, read as ‘0’
		-n = Value at POR ‘1’ = Bit is set ‘0’ = Bit is cleared x = Bit is unknown
 *
 **************************************************************************************************/
#define EFLG		0x2D

/*		bit 7 RX1OVR: Receive Buffer 1 Overflow Flag bit
		- Sets when a valid message is received for RXB1 and RX1IF (CANINTF[1]) = 1
		- Must be reset by MCU
		bit 6 RX0OVR: Receive Buffer 0 Overflow Flag bit
		- Sets when a valid message is received for RXB0 and RX0IF (CANINTF[0]) = 1
		- Must be reset by MCU
		bit 5 TXBO: Bus-Off Error Flag bit
		- Sets when TEC reaches 255
		- Resets after a successful bus recovery sequence
		bit 4 TXEP: Transmit Error-Passive Flag bit
		- Sets when TEC is equal to or greater than 128
		- Resets when TEC is less than 128
		bit 3 RXEP: Receive Error-Passive Flag bit
		- Sets when REC is equal to or greater than 128
		- Resets when REC is less than 128
		bit 2 TXWAR: Transmit Error Warning Flag bit
		- Sets when TEC is equal to or greater than 96
		- Resets when TEC is less than 96
		bit 1 RXWAR: Receive Error Warning Flag bit
		- Sets when REC is equal to or greater than 96
		- Resets when REC is less than 96
		bit 0 EWARN: Error Warning Flag bit
		- Sets when TEC or REC is equal to or greater than 96 (TXWAR or RXWAR = 1)
		- Resets when both REC and TEC are less than 96
 * */
#define RX1OVR			7
#define RX0OVR			6
#define TXBO			5
#define TXEP			4
#define RXEP			3
#define TXWAR			2
#define RXWAR			1
#define EWARN			0


/**************************************************************************************************
 *
 *			REC: RECEIVE ERROR COUNTER REGISTER (ADDRESS: 1Dh)
 *			bit 7-0 REC[7:0]: Receive Error Count bits
 **************************************************************************************************/
#define REC		0x1D

/**************************************************************************************************
 *			TEC: TRANSMIT ERROR COUNTER REGISTER (ADDRESS: 1Ch)
 *			bit 7-0 TEC[7:0]: Transmit Error Count bits
 *
 *
 **************************************************************************************************/
#define TEC		0x1C


/**************************************************************************************************
 *			CNF3: CONFIGURATION REGISTER 3 (ADDRESS: 28h)
 *
 *
 **************************************************************************************************/
#define CNF3		0x28

/*		bit 7 SOF: Start-of-Frame signal bit
		If CLKEN (CANCTRL[2]) = 1:
		1 = CLKOUT pin is enabled for SOF signal
		0 = CLKOUT pin is enabled for clock out function
		If CLKEN (CANCTRL[2]) = 0:
		Bit is don’t care.
		bit 6 WAKFIL: Wake-up Filter bit
		1 = Wake-up filter is enabled
		0 = Wake-up filter is disabled
		bit 5-3 Unimplemented: Reads as ‘0’
		bit 2-0 PHSEG2[2:0]: PS2 Length bits
		(PHSEG2[2:0] + 1) x TQ. Minimum valid setting for PS2 is 2 TQs.
 * */
#define SOF			7
#define WAKFIL		6
#define PHSEG22		2
#define PHSEG21		1
#define PHSEG20		0



/**************************************************************************************************
 *
 *		CNF2: CONFIGURATION REGISTER 2 (ADDRESS: 29h)
 *
 **************************************************************************************************/
#define CNF2		0x29

/*		bit 7 BTLMODE: PS2 Bit Time Length bit
		1 = Length of PS2 is determined by the PHSEG2[2:0] bits of CNF3
		0 = Length of PS2 is the greater of PS1 and IPT (2 TQs)
		bit 6 SAM: Sample Point Configuration bit
		1 = Bus line is sampled three times at the sample point
		0 = Bus line is sampled once at the sample point
		bit 5-3 PHSEG1[2:0]: PS1 Length bits
		(PHSEG1[2:0] + 1) x TQ.
		bit 2-0 PRSEG[2:0]: Propagation Segment Length bits
		(PRSEG[2:0] + 1) x TQ.
 *
 * */
#define BTLMODE			7
#define SAM				6
#define PHSEG12			5
#define PHSEG11			4
#define PHSEG10			3
#define PRSEG2			2
#define PRSEG1			1
#define PRSEG0			0



/**************************************************************************************************
 *		CNF1: CONFIGURATION REGISTER 1 (ADDRESS: 2Ah)
 *
 *
 *
 **************************************************************************************************/
#define CNF1		0x2A
/*		bit 7-6 SJW[1:0]: Synchronization Jump Width Length bits
		11 = Length = 4 x TQ
		10 = Length = 3 x TQ
		01 = Length = 2 x TQ
		00 = Length = 1 x TQ
		bit 5-0 BRP[5:0]: Baud Rate Prescaler bits
		TQ = 2 x (BRP[5:0] + 1)/FOSC.
 * */
#define SJW1		7
#define SJW0		6
#define BRP5		5
#define BRP4		4
#define BRP3		3
#define BRP2		2
#define BRP1		1
#define BRP0		0


/**/
#define EFLG			0x2C
#define CANINTE			0x2B

/**************************************************************************************************
 *
 *
 *
 **************************************************************************************************/



/**************************************************************************************************
 *
 *
 *
 **************************************************************************************************/


/**************************************************************************************************
 *
 *			REGISTER 10-1: CANCTRL: CAN CONTROL REGISTER (ADDRESS: XFh)
 *
 **************************************************************************************************/
#define CANCTRL			0x0F
/**************************************************************************************************
 *
 *			REGISTER 10-2: CANSTAT: CAN STATUS REGISTER (ADDRESS: XEh)
 *
 **************************************************************************************************/
#define CANSTAT			0x0E

/**/
#define RXB0CTRL		(0b01100000)
/*		*/
#define RXM0SIDH		0x20
#define RXM1SIDH		0x24


/*
 *
 * 		Here we will define the instruction of the CAN controller
 * 		MCP2515
 *
 * 		*/
#define MCP2515_INST_WRITE				0x02
//#define MCP2515_INS_READ				0x07
#define MCP_2515_RESET					0xC0
#define MCP_2515_READ					0x03
#define MCP_2515_READ_RX_BUFFER			0b10010nm0
#define MCP_2515_READ_STATUS			0xA0
#define MCP_2515_RX_STATUS				0xB0
#define MCP_2515_BIT_MODIFY				0x05
#define MCP_2515_LOAD_TX_BUFFER			0b01000abc
/*		Request to send			*/
#define MCP_2515_RTS					0b10000nnn
#define MCP_2515_RTS_B0					0x81 // buffer 0
#define MCP_2515_RTS_B1					0x82 // buffer 1
#define MCP_2515_RTS_B2					0x83 // buffer 2

/*
 *
 * 		Here we will define the modes of the CAN controller
 * 		MCP2515
 * 		*/
#define MCP_2515_NORMAL_MODE			0b000
#define MCP_2515_CONFIGURATION_MODE		0b100
#define MCP_2515_SLEEP_MODE				0b001
#define MCP_2515_LOOPBACK_MODE			0b010
#define MCP_2515_LISTENONLY_MODE		0b011



#endif /* CAN_PRIVATE_H_ */
