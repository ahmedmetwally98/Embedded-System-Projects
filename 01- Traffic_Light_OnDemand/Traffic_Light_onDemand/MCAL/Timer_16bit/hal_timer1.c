/*
 * hal_timer1.c
 *
 *  Created on: Mar 25, 2023
 *      Author: ahmed
 */



#include "../Timer_16bit/hal_timer1.h"
#if TIMER1_MODULE == MODULE_ENABLE
/* ------------------------------ Global Variables Declarations ------------------------------ */
//static const uint16 prescaler_value_map[5] = {1, 8, 64, 256, 1024};
static void (*TMR1_interruptHandlerNotify)(void) = NULL;

/* ------------------------------ Helper Functions Declarations ------------------------------ */
static void timer1_set_clock_source(const timer1_t* tmr_obj);
static Std_ReturnType timer1_set_general_mode(const timer1_t* tmr_obj);

/* ------------------------------ SW Functions Definitions ------------------------------ */
Std_ReturnType timer1_init(const timer1_t* tmr_obj)
{
	Std_ReturnType ret = E_OK;
	if(tmr_obj == NULL)
	{
		ret  = E_NOT_OK;
	}
	else
	{
		// Disable timer1 module
		TIMER1_MODULE_DISABLE();
		/* Set Interrupts Configurations */
#if TIMER1_INTERRUPT_FEATURE == INTERRUPT_FEATURE_ENABLE
		INTERRUPT_GLOBAL_ENABLE();
		TMR1_interruptHandlerNotify = tmr_obj->tmr1_interruptHanlderNotify;
#if TIMER1_OV1_INTERRUPT_FEATURE == INTERRUPT_FEATURE_ENABLE
		TIMER1_OVERFLOW_INTERRUPT_ENABLE();
#endif
#if	TIMER1_OC1A_INTERRRUPT_FEATURE == INTERRUPT_FEATURE_ENABLE
		TIMER1_OC1A_INTERRUPT_ENABLE();
#endif
#if	TIMER1_OC1B_INTERRRUPT_FEATURE == INTERRUPT_FEATURE_ENABLE
		TIMER1_OC1B_INTERRUPT_ENABLE();
#endif
#if	TIMER1_IC1_INTERRRUPT_FEATURE == INTERRUPT_FEATURE_ENABLE
		TIMER1_IC1_INTERRUPT_ENABLE();
#endif
#endif
		/*Set Timer1 General Mode */
		timer1_set_general_mode(tmr_obj);

		/* Enable Timer1 Module */
		timer1_set_clock_source(tmr_obj);
	}
	return ret;
}
Std_ReturnType timer1_Deinit(const timer1_t* tmr_obj)
{
	Std_ReturnType ret = E_OK;
	if(tmr_obj == NULL)
	{
		ret  = E_NOT_OK;
	}
	else
	{
		// Disable all Timer1 interrupt sources if defined
#if TIMER1_INTERRUPT_FEATURE == INTERRUPT_FEATURE_ENABLE
#if TIMER1_OV1_INTERRUPT_FEATURE == INTERRUPT_FEATURE_ENABLE
		TIMER1_OVERFLOW_INTERRUPT_DISABLE();
#endif
#if	TIMER1_OC1A_INTERRRUPT_FEATURE == INTERRUPT_FEATURE_ENABLE
		TIMER1_OC1A_INTERRUPT_DISABLE();
#endif
#if	TIMER1_OC1B_INTERRRUPT_FEATURE == INTERRUPT_FEATURE_ENABLE
		TIMER1_OC1B_INTERRUPT_DISABLE();
#endif
#if	TIMER1_IC1_INTERRRUPT_FEATURE == INTERRUPT_FEATURE_ENABLE
		TIMER1_IC1_INTERRUPT_DISABLE();
#endif
#endif
		// disconnected both OC1A and OC1B
		TCCR1A &= 0x0F;
		// Disable Timer1 Module
		TIMER1_MODULE_DISABLE();
	}
	return ret;
}
Std_ReturnType timer1_write_counter_value(const uint16 value)
{
	Std_ReturnType ret = E_OK;
	/** write sequence in 16-bit register for 8-bit architecture is as following:
	 * 1- write first the new value in High byte of the intended register
	 * 2- write second the new value in Low byte of the intended register
	 * */
	TCNT1H = (value >> 8);
	TCNT1L = (uint8)(value);
	return ret;
}
Std_ReturnType timer1_read_counter_value(uint16* ret_value)
{
	Std_ReturnType ret = E_OK;
	/** read sequence in 16-bit register for 8-bit architecture is as following:
	 * 1- read first the new value in Low byte of the intended register
	 * 2- read second the new value in High byte of the intended register
	 * */
	*ret_value = TCNT1L;
	*ret_value |= (((uint16)TCNT1H) << 8);
	return ret;
}

void timer1_delayInSeconds(uint8 a_delaySecond)
{
	/* delay should not exceed 8.38 seconds for a proper functionality */
	uint16 l_counter_preload = 0;
	Std_ReturnType ret = E_OK;
	l_counter_preload = 0;
	l_counter_preload = (uint16)(65536 - ((float)(F_CLOCK*a_delaySecond)/1024.0));
	ret = timer1_write_counter_value(l_counter_preload);
}
/* ------------------------------ Helper Functions Definitions ------------------------------ */
static Std_ReturnType timer1_set_general_mode(const timer1_t* tmr_obj)
{
	Std_ReturnType ret = E_OK;
	TCCR1A = 0; TCCR1B = 0;	// NORMAL Mode
	// Pins OC1A and OC1B Disconnected in normal mode.
	TCCR1A &= 0x0F;
	return ret;
}

static void timer1_set_clock_source(const timer1_t* tmr_obj)
{
	if (tmr_obj->timer1_clk_src == TIMER1_INTERNAL_CLK_SOURCE)
	{
		switch(tmr_obj->timer1_prescaler_value)
		{
		case TIMER1_PRESCALER_VALUE_DIV_BY_8:		TCCR1B &= 0xFA;
													SET_BIT(TCCR1B, CS11);
			break;
		case TIMER1_PRESCALER_VALUE_DIV_BY_64:		TCCR1B |= 0x03;
													CLEAR_BIT(TCCR1B, CS12);
			break;
		case TIMER1_PRESCALER_VALUE_DIV_BY_256:		TCCR1B &= 0xFC;
													SET_BIT(TCCR1B, CS12);
			break;
		case TIMER1_PRESCALER_VALUE_DIV_BY_1024:	TCCR1B |= 0x05;
													CLEAR_BIT(TCCR1B, CS11);
			break;
		default: 	SET_BIT(TCCR1B, CS10);		// Pre-scaler = 1 by default.
					TCCR1B &= 0xF9;
			break;
		}
	}
	else if(tmr_obj->timer1_clk_src == TIMER1_EXTERNAL_CLK_SOURCE)
	{
		switch(tmr_obj->timer1_edge_detect)
		{
		case TIMER1_EXTERNAL_CLK_RISING_EDGE:		TCCR1B |= 0x07;
			break;
		case TIMER1_EXTERNAL_CLK_FALLING_EDGE:		CLEAR_BIT(TCCR1B, CS10);
													TCCR1B |= 0x06;
			break;
		default:	TCCR1B |= 0x07;
			break;
		}
		CLEAR_BIT(DDRB, DDB1);	// set T1 pin as Digital i/p for Counter mode
	}
	else
	{	// Pre-scaler = 1 by default.
		SET_BIT(TCCR1B, CS10);
		TCCR1B &= 0xF9;
	}
}


/* Implement ISRs for the four Sources Interrupts related to TIMER1 */
#if TIMER1_INTERRUPT_FEATURE == INTERRUPT_FEATURE_ENABLE
#if TIMER1_OV1_INTERRUPT_FEATURE == INTERRUPT_FEATURE_ENABLE
ISR(TIMER1_OVF_vect)
{
	/* ISR code */
	if(NULL != TMR1_interruptHandlerNotify)
	{
		TMR1_interruptHandlerNotify();
	}
	// clear TIMER0_COMP flag happen automatically
}
#endif
#if	TIMER1_OC1A_INTERRRUPT_FEATURE == INTERRUPT_FEATURE_ENABLE
ISR(TIMER1_COMPA_vect)
{
	/* ISR code */

	// clear TIMER1_COMPA flag happen automatically
}
#endif
#if	TIMER1_OC1B_INTERRRUPT_FEATURE == INTERRUPT_FEATURE_ENABLE
ISR(TIMER1_COMPB_vect)
{
	/* ISR code */
	// use the callback function

	// clear TIMER1_COMPB flag happen automatically
}
#endif
#if	TIMER1_IC1_INTERRRUPT_FEATURE == INTERRUPT_FEATURE_ENABLE
ISR(TIMER1_CAPT_vect)
{
	/* ISR code */

	// clear TIMER1_CAPT flag happen automatically
}
#endif
#endif


#endif
