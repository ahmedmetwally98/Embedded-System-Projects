/*
 * INT_External.c
 *
 *  Created on: Mar 16, 2023
 *      Author: ahmed
 */

#include "INT_External.h"


#if INTERRUPT_EXTERNAL_INTx_FEATURE == INTERRUPT_FEATURE_ENABLE
/* ------------------------------ Global Variables Declarations ------------------------------ */
static void (*INT0_InterruptHandler_notify)(void) = NULL;
static void (*INT1_InterruptHandler_notify)(void) = NULL;
static void (*INT2_InterruptHandler_notify)(void) = NULL;

/* ------------------------------ Helper Functions Declarations ------------------------------ */

static Std_ReturnType Interrupt_INTx_Enable(const interrupt_INTx_t* int_obj);
static Std_ReturnType Interrupt_INTx_Disable(const interrupt_INTx_t* int_obj);
static Std_ReturnType Interrupt_INTx_Sense_init(const interrupt_INTx_t* int_obj);
static Std_ReturnType Interrupt_INTx_Pin_init(const interrupt_INTx_t* int_obj);


/* ------------------------------ SW Functions Definitions ------------------------------ */
Std_ReturnType Interrupt_INTx_Init(const interrupt_INTx_t* int_obj)
{
	Std_ReturnType ret = E_OK;
	if(int_obj == NULL)
	{
		ret = E_NOT_OK;
	}
	else
	{
		/* Disable the External Interrupt */
		ret = Interrupt_INTx_Disable(int_obj);
		/* Set External Interrupt Sensing */
		ret = Interrupt_INTx_Sense_init(int_obj);
		/* Configure interrupt Pin as input pin */
		ret = Interrupt_INTx_Pin_init(int_obj);
		/* Enable the External Interrupt (Set INTx Enable bit)*/
		ret = Interrupt_INTx_Enable(int_obj);
		/* Enabling the Global Interrupt Bit (I-bit in the SREG "status register") */
	}
	return ret;
}
Std_ReturnType Interrupt_INTx_Deinit(const interrupt_INTx_t* int_obj)
{
	Std_ReturnType ret = E_OK;
	if(int_obj == NULL)
	{
		ret = E_NOT_OK;
	}
	else
	{
		/* Disable the External Interrupt */
		ret = Interrupt_INTx_Disable(int_obj);
	}
	return ret;
}


/* ------------------------------ Helper Functions Definitions ------------------------------ */
static Std_ReturnType Interrupt_INTx_Enable(const interrupt_INTx_t* int_obj)
{
	Std_ReturnType ret = E_OK;
	INTERRUPT_GLOBAL_ENABLE();
	switch(int_obj->int_source)
	{
	case INT0_EXT:	INT0_ENABLE();
		break;
	case INT1_EXT:	INT1_ENABLE();
		break;
	case INT2_EXT:	INT2_ENABLE();
		break;
	default:		ret = E_NOT_OK;
		break;
	}
	return ret;
}
static Std_ReturnType Interrupt_INTx_Disable(const interrupt_INTx_t* int_obj)
{
	Std_ReturnType ret = E_OK;
	switch(int_obj->int_source)
	{
	case INT0_EXT:	INT0_DISABLE();
		break;
	case INT1_EXT:	INT1_DISABLE();
		break;
	case INT2_EXT:	INT2_DISABLE();
		break;
	default:		ret = E_NOT_OK;
		break;
	}
	return ret;
}
static Std_ReturnType Interrupt_INTx_Sense_init(const interrupt_INTx_t* int_obj)
{
	Std_ReturnType ret = E_OK;
	switch(int_obj->int_source)
		{
		case INT0_EXT:
			switch(int_obj->int_sense)
			{
			case INTx_SENSE_LOW_LEVEL:			CLEAR_BIT(MCUCR, ISC00);
												CLEAR_BIT(MCUCR, ISC01);
				break;
			case INTx_SENSE_ANY_LOGICAL_CHANGE: SET_BIT(MCUCR, ISC00);
												CLEAR_BIT(MCUCR, ISC01);
				break;
			case INTx_SENSE_FALLING_EDGE: 		CLEAR_BIT(MCUCR, ISC00);
												SET_BIT(MCUCR, ISC01);
				break;
			case INTx_SENSE_RISING_EDGE:		SET_BIT(MCUCR, ISC00);
												SET_BIT(MCUCR, ISC01);
				break;
			default: ret = E_NOT_OK;
				break;
			}
			break;
		case INT1_EXT:
			switch(int_obj->int_sense)
			{
			case INTx_SENSE_LOW_LEVEL:			CLEAR_BIT(MCUCR, ISC10);
												CLEAR_BIT(MCUCR, ISC11);
				break;
			case INTx_SENSE_ANY_LOGICAL_CHANGE: SET_BIT(MCUCR, ISC10);
												CLEAR_BIT(MCUCR, ISC11);
				break;
			case INTx_SENSE_FALLING_EDGE: 		CLEAR_BIT(MCUCR, ISC10);
												SET_BIT(MCUCR, ISC11);
				break;
			case INTx_SENSE_RISING_EDGE:		SET_BIT(MCUCR, ISC10);
												SET_BIT(MCUCR, ISC11);
				break;
			default: ret = E_NOT_OK;
				break;
			}
			break;
		case INT2_EXT:
			switch(int_obj->int_sense)
			{
			case INTx_SENSE_FALLING_EDGE: 		CLEAR_BIT(MCUCSR, ISC2);
				break;
			case INTx_SENSE_RISING_EDGE:		SET_BIT(MCUCSR, ISC2);
				break;
			default: ret = E_NOT_OK;
				break;
			}
			break;
		default:		ret = E_NOT_OK;
			break;
		}
	return ret;
}
static Std_ReturnType Interrupt_INTx_Pin_init(const interrupt_INTx_t* int_obj)
{
	Std_ReturnType ret = E_OK;
	ret = GPIO_pin_direction_initialize(&(int_obj->int_pin));
	// Assigning the interrupt handler for notifying the application layer that interrupt is happen
	switch(int_obj->int_source)
	{
		case INT0_EXT:	INT0_InterruptHandler_notify = int_obj->EXT_InterruptHandler;
			break;
		case INT1_EXT:	INT1_InterruptHandler_notify = int_obj->EXT_InterruptHandler;
			break;
		case INT2_EXT:	INT2_InterruptHandler_notify = int_obj->EXT_InterruptHandler;
			break;
		default:		ret = E_NOT_OK;
			break;
	}
	return ret;
}


/* --------------- ISR for INT0, INT1 and INT2 --------------- */
ISR(INT0_vect)
{
	// clear the int0 flag
	INT0_CLEAR_FLAG();

	// use the callback function
	if(INT0_InterruptHandler_notify)
	{
		INT0_InterruptHandler_notify();
	}
}

ISR(INT1_vect)
{
	// clear the int0 flag
	INT1_CLEAR_FLAG();

	// use the callback function
	if(INT1_InterruptHandler_notify)
	{
		INT1_InterruptHandler_notify();
	}
}

ISR(INT2_vect)
{
	// clear the int0 flag
	INT2_CLEAR_FLAG();

	// use the callback function
	if(INT2_InterruptHandler_notify)
	{
		INT2_InterruptHandler_notify();
	}
}

#endif
