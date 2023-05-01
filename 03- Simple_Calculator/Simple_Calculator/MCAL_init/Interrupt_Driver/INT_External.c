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
static Std_ReturnType Interrupt_INTx_Sense_init(const interrupt_INTx_t* int_obj);

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
		ret = Interrupt_INTx_Deinit(int_obj->int_source);
		/* Set External Interrupt Sensing */
		ret = Interrupt_INTx_Sense_init(int_obj);
		/* Enable the External Interrupt (Set INTx Enable bit)*/
		INTERRUPT_GLOBAL_ENABLE();
		switch(int_obj->int_source)
		{
		case INT0_EXT:	INT0_ENABLE();
						CLEAR_BIT(DDRD, PD2);	// set INT0 pin as digital input
		INT0_InterruptHandler_notify = int_obj->EXT_InterruptHandler;
			break;
		case INT1_EXT:	INT1_ENABLE();
						CLEAR_BIT(DDRD, PD3);	// set INT1 pin as digital input
		INT1_InterruptHandler_notify = int_obj->EXT_InterruptHandler;
			break;
		case INT2_EXT:	INT2_ENABLE();
						CLEAR_BIT(DDRB, PB2);	// set INT2 pin as digital input
		INT2_InterruptHandler_notify = int_obj->EXT_InterruptHandler;
			break;
		default:		ret = E_NOT_OK;
			break;
		}
		/* Enabling the Global Interrupt Bit (I-bit in the SREG "status register") */
	}
	return ret;
}
Std_ReturnType Interrupt_INTx_Deinit(const uint8 a_int_source)
{
	Std_ReturnType ret = E_OK;
		/* Disable the External Interrupt */
		switch(a_int_source)
		{
		case INT0_EXT:	 INT0_CLEAR_FLAG(); INT0_DISABLE();
			break;
		case INT1_EXT:	 INT1_CLEAR_FLAG(); INT1_DISABLE();
			break;
		case INT2_EXT:	 INT2_CLEAR_FLAG(); INT2_DISABLE();
			break;
		default:		ret = E_NOT_OK;
			break;
	}
	return ret;
}

/* ------------------------------ Helper Functions Definitions ------------------------------ */
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


/* ---------------------- Implementing ISR code for INT0, INT1 and INT2*/
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
