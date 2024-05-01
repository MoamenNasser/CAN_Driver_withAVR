/*
 * MDIO_Private.h
 *
 *  Created on: Sep 24, 2021
 *      Author: naser
*/

#ifndef MDIO_PRIVATE_H_
#define MDIO_PRIVATE_H_
			/*		Define all ports			*/
#define DIO_PORTA       		 0
#define DIO_PORTB         		 1
#define DIO_PORTC       		 2
#define DIO_PORTD       		 3
			/*		Define Each Pin in port		*/
#define DIO_PIN0      	  	 	 0
#define DIO_PIN1      		     1
#define DIO_PIN2      		     2
#define DIO_PIN3     		     3
#define DIO_PIN4     		     4
#define DIO_PIN5      		     5
#define DIO_PIN6      		     6
#define DIO_PIN7      		     7

#define DIO_INPUT       		 0
#define DIO_OUTPUT       		 1

#define DIO_PORT_HIGH         	 0xFF
#define DIO_PORT_LOW          	 0x00

#define DIO_PORT_OUTPUT          0xFF
#define DIO_PORT_INPUT           0x00

#define DIO_UNDEFINED_VAL		 0xFF

#define DIO_PIN_HIGH	 		 0x01
#define DIO_PIN_LOW		 		 0x00

/*				PORTA REGISTERS				*/
#define DDRA_REG 						*((volatile u8*)0x3A)
#define PORTA_REG 						*((volatile u8*)0x3B)
#define PINA_REG  						*((volatile u8*)0x39)

#define PORTA_PIN0_ADC0					0
#define PORTA_PIN1_ADC1					1
#define PORTA_PIN2_ADC2					2
#define PORTA_PIN3_ADC3					3
#define PORTA_PIN4_ADC4					4
#define PORTA_PIN5_ADC5					5
#define PORTA_PIN6_ADC6					6
#define PORTA_PIN7_ADC7					7



/*				PORTB REGISTERS				*/
#define DDRB_REG  						*((volatile u8*)0x37)
#define PORTB_REG 						*((volatile u8*)0x38)
#define PINB_REG  						*((volatile u8*)0x36)

#define PORTB_PIN0_XCK_T0				0
#define PORTB_PIN1_T1					1
#define PORTB_PIN2_INT2_AIN0			2
#define PORTB_PIN3_OC0_AIN1				3
#define PORTB_PIN4_SS					4
#define PORTB_PIN5_MOSI					5
#define PORTB_PIN6_MISO					6
#define PORTB_PIN7_SCK					7



/*				PORTC REGISTERS				*/
#define DDRC_REG  						*((volatile u8*)0x34)
#define PORTC_REG 						*((volatile u8*)0x35)
#define PINC_REG  						*((volatile u8*)0x33)

#define PORTC_PIN0_SCL					0
#define PORTC_PIN1_SDA					1
#define PORTC_PIN2_TCK					2
#define PORTC_PIN3_TMS					3
#define PORTC_PIN4_TDO					4
#define PORTC_PIN5_TDI					5
#define PORTC_PIN6_TOSC1				6
#define PORTC_PIN7_TOSC2				7


/*				PORTD REGISTERS				*/
#define DDRD_REG  						*((volatile u8*)0x31)
#define PORTD_REG 						*((volatile u8*)0x32)
#define PIND_REG  						*((volatile u8*)0x30)

#define PORTD_PIN0_RXD					0
#define PORTD_PIN1_TXD					1
#define PORTD_PIN2_INT0					2
#define PORTD_PIN3_INT1					3
#define PORTD_PIN4_OC1B					4
#define PORTD_PIN5_OC1A					5
#define PORTD_PIN6_ICP					6
#define PORTD_PIN7_OC2					7

#endif /* MDIO_PRIVATE_H_ */
