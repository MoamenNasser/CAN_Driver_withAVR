/*
 * 		MDIO_Program.c
 *		Version: 1.0
 *  	Created on: Sep 18, 2021
 *      Author: Moamen Naser
 */

#include"STD_TYPES.h"
#include"BIT_MATH.h"
#include"MDIO_Private.h"
#include"MDIO_Interface.h"
/***************************************************************************
 *
 * 			Here we Set the Pin direction of the given port to 1 or 0
 *
 *************************************************************************/
void MDIO_VoidSetPinDirection(u8 Copy_u8Port ,u8 Copy_u8Pin, u8 Copy_u8Direc)
{
	/*					check for pins and ports					*/
	if(Copy_u8Port <= DIO_PORTD  && Copy_u8Pin <= DIO_PIN7)
	{
	/*					check the direction							*/
		if(DIO_PIN_HIGH == Copy_u8Direc)
		{
			switch(Copy_u8Port)
			{
				case DIO_PORTA:SET_BIT(DDRA_REG, Copy_u8Pin); break;
				case DIO_PORTB:SET_BIT(DDRB_REG, Copy_u8Pin); break;
				case DIO_PORTC:SET_BIT(DDRC_REG, Copy_u8Pin); break;
				case DIO_PORTD:SET_BIT(DDRD_REG, Copy_u8Pin); break;
				default: /*		Wrong POrt ID		*/	      break;
			}
		}
	/**/
		else if(DIO_PIN_LOW == Copy_u8Direc)
		{
			switch(Copy_u8Port)
			{
				case DIO_PORTA:CLR_BIT(DDRA_REG, Copy_u8Pin); break;
				case DIO_PORTB:CLR_BIT(DDRB_REG, Copy_u8Pin); break;
				case DIO_PORTC:CLR_BIT(DDRC_REG, Copy_u8Pin); break;
				case DIO_PORTD:CLR_BIT(DDRD_REG, Copy_u8Pin); break;
				default: /*		Wrong POrt ID		*/	      break;
			}
		}
		else
		{
			/* NOTHING */
			/*Wrong Port direction*/
		}
	}
	else
	{
		/*					Wrong PIN ID or POrt ID						*/
	}
}
/***************************************************************************
 *
 * 			Here we Set the Pin value of the given port to 1 or 0
 *
 *************************************************************************/
void MDIO_VoidSetPinValue(u8 Copy_u8Port ,u8 Copy_u8Pin, u8 Copy_u8Value)
{
	/*					check for pins and ports					*/
	if(Copy_u8Port <= DIO_PORTD  && Copy_u8Pin <= DIO_PIN7)
	{
	/*check the direction*/
		if(DIO_PIN_HIGH == Copy_u8Value)
		{
			switch(Copy_u8Port)
			{
				case DIO_PORTA:SET_BIT(PORTA_REG, Copy_u8Pin); break;
				case DIO_PORTB:SET_BIT(PORTB_REG, Copy_u8Pin); break;
				case DIO_PORTC:SET_BIT(PORTC_REG, Copy_u8Pin); break;
				case DIO_PORTD:SET_BIT(PORTD_REG, Copy_u8Pin); break;
				default: /*		Wrong POrt ID		*/	   	   break;
			}
		}
	/**/
		else if(DIO_PIN_LOW == Copy_u8Value)
		{
			switch(Copy_u8Port)
			{
				case DIO_PORTA:CLR_BIT(PORTA_REG, Copy_u8Pin); break;
				case DIO_PORTB:CLR_BIT(PORTB_REG, Copy_u8Pin); break;
				case DIO_PORTC:CLR_BIT(PORTC_REG, Copy_u8Pin); break;
				case DIO_PORTD:CLR_BIT(PORTD_REG, Copy_u8Pin); break;
				default: /*		Wrong POrt ID		*/	   	   break;
			}
		}
		else
		{
			/* NOTHING */
			/*Wrong Port direction*/
		}
	}
	else
	{
		/*Wrong PIN ID or POrt ID*/
	}

}
/***************************************************************************
 *
 * 			Here we get the Pin value of the given port and pin
 *
 *************************************************************************/
u8 MDIO_u8GetPinValue(u8 Copy_u8Port ,u8 Copy_u8Pin)
{
	/*					check for pins and ports					*/
	u8 LOC_u8RetValue_var1;
	if(Copy_u8Port <= DIO_PORTD  && Copy_u8Pin <= DIO_PIN7)
	{

		switch(Copy_u8Port)
		{
			case DIO_PORTA: LOC_u8RetValue_var1 = GET_BIT(PINA_REG, Copy_u8Pin);break;
			case DIO_PORTB: LOC_u8RetValue_var1 = GET_BIT(PINB_REG, Copy_u8Pin);break;
			case DIO_PORTC: LOC_u8RetValue_var1 = GET_BIT(PINC_REG, Copy_u8Pin);break;
			case DIO_PORTD: LOC_u8RetValue_var1 = GET_BIT(PIND_REG, Copy_u8Pin);break;
			default: /*		Wrong POrt ID		*/	   							break;
		}
	}
	else
	{
		/*Wrong PIN ID or POrt ID*/
		LOC_u8RetValue_var1 = DIO_UNDEFINED_VAL;
	}
	return LOC_u8RetValue_var1;

}
/***************************************************************************
 *
 * 			Here we Set the port direction of the given port to 1 or 0
 *
 *************************************************************************/
void MDIO_VoidSetPortDirection(u8 Copy_u8Port, u8 Copy_u8Direc)
{
	/*							check for Port							*/
	switch(Copy_u8Port)
	{
		case DIO_PORTA:  DDRA_REG =  Copy_u8Direc; break;
		case DIO_PORTB:  DDRB_REG =  Copy_u8Direc; break;
		case DIO_PORTC:  DDRC_REG =  Copy_u8Direc; break;
		case DIO_PORTD:  DDRD_REG =  Copy_u8Direc; break;
		default: /*		Wrong POrt ID		*/	   break;
	}
}

/***************************************************************************
 *
 * 			Here we Set the port value of the given port to 1 or 0
 *
 *************************************************************************/
void MDIO_VoidSetPortValue(u8 Copy_u8Port ,u8 Copy_u8Value)
{
	/*						check for Port								*/
	switch(Copy_u8Port)
	{
		case DIO_PORTA:  PORTA_REG =  Copy_u8Value; break;
		case DIO_PORTB:  PORTB_REG =  Copy_u8Value; break;
		case DIO_PORTC:  PORTC_REG =  Copy_u8Value; break;
		case DIO_PORTD:  PORTD_REG =  Copy_u8Value; break;
		default: /*		Wrong POrt ID		*/		break;
	}
}

/***************************************************************************
 *
 * 			Here we toggle the Pin
 *
 *************************************************************************/
void MDIO_VoidTogglePin(u8 Copy_u8Port ,u8 Copy_u8Pin)
{
	/*					check for pins and ports					*/
	if(Copy_u8Port <= DIO_PORTD  && Copy_u8Pin <= DIO_PIN7)
	{
		switch(Copy_u8Port)
		{
			case DIO_PORTA:TOGGLE_BIT(PORTA_REG, Copy_u8Pin); break;
			case DIO_PORTB:TOGGLE_BIT(PORTB_REG, Copy_u8Pin); break;
			case DIO_PORTC:TOGGLE_BIT(PORTC_REG, Copy_u8Pin); break;
			case DIO_PORTD:TOGGLE_BIT(PORTD_REG, Copy_u8Pin); break;
			default: /*		Wrong POrt ID		*/			  break;
		}
	}
	else
	{
		/*Wrong PIN ID or POrt ID*/
	}
}
/***************************************************************************
 *
 * 			Here we Enable the pull up resistor
 *
 *************************************************************************/
void MDIO_VoidEnablePullUpResistor(u8 Copy_u8Port,u8 Copy_u8Pin)
{
	/*					check for pins and ports					*/
	if(Copy_u8Port <= DIO_PORTD  && Copy_u8Pin <= DIO_PIN7)
	{
		switch(Copy_u8Port)
		{
			case DIO_PORTA:SET_BIT(PORTA_REG, Copy_u8Pin); break;
			case DIO_PORTB:SET_BIT(PORTB_REG, Copy_u8Pin); break;
			case DIO_PORTC:SET_BIT(PORTC_REG, Copy_u8Pin); break;
			case DIO_PORTD:SET_BIT(PORTD_REG, Copy_u8Pin); break;
			default: /*		Wrong POrt ID		*/		   break;
		}
	}
	else
	{
		/*Wrong PIN ID or POrt ID*/
	}
}
