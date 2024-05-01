/*
 * CNF.h
 *
 *  Created on: Sep 19, 2021
 *      Author: naser
 */

#ifndef HLCD_CNF_H_
#define HLCD_CNF_H_

/**/
#define HLCD_4_BIT_MODE     0
/**/
#define HLCD_8_BIT_MODE     1
/*		Change the Mode From here please							*/
#define HLCD_INIT_MODE				HLCD_8_BIT_MODE
/*		Set PORTD as the Data Port to send the data on it 			*/
#define HLCD_DATA_PORT     		 	DIO_PORTC
/*		Set PORTB as the Control Port to control the signal bits 	*/
#define HLCD_CONTROL_PORT  		 	DIO_PORTB
/*		Set the RS pin to the first pin of the port					*/
#define HLCD_RS_PIN        		 	DIO_PIN0
/*		Set the RW pin to the second pin of the port				*/
#define HLCD_RW_PIN        			DIO_PIN1
/*		Set the E pin to the third pin of the port					*/
#define HLCD_E_PIN          		DIO_PIN2


/*		Configuration of PINS for 8 bit mode						*/
/*		#define HLCD_DATA_PORT		PORTC							*/
#define HLCD_DATA_PIN0_PORTX		DIO_PORTC
#define HLCD_DATA_PIN0_PINX			DIO_PIN0
#define HLCD_DATA_PIN1_PORTX		DIO_PORTC
#define HLCD_DATA_PIN1_PINX			DIO_PIN1
#define HLCD_DATA_PIN2_PORTX		DIO_PORTC
#define HLCD_DATA_PIN2_PINX			DIO_PIN2
#define HLCD_DATA_PIN3_PORTX		DIO_PORTC
#define HLCD_DATA_PIN3_PINX			DIO_PIN3




/*		Configuration of PINS for 4 bit mode						*/
/*		#define HLCD_DATA_PORT		PORTC							*/
#define HLCD_DATA_PIN4_PORTX		DIO_PORTC
#define HLCD_DATA_PIN4_PINX			DIO_PIN4
#define HLCD_DATA_PIN5_PORTX		DIO_PORTC
#define HLCD_DATA_PIN5_PINX			DIO_PIN5
#define HLCD_DATA_PIN6_PORTX		DIO_PORTC
#define HLCD_DATA_PIN6_PINX			DIO_PIN6
#define HLCD_DATA_PIN7_PORTX		DIO_PORTC
#define HLCD_DATA_PIN7_PINX			DIO_PIN7





#endif /* HLCD_CNF_H_ */
