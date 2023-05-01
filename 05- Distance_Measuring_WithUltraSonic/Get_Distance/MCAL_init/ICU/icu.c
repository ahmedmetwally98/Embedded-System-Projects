/*
 * icu.c
 *
 *  Created on: Apr 13, 2023
 *      Author: ahmed
 */


#include "icu.h"

/* ------------------------------ Global Variables Declarations ------------------------------ */

#if ICU_MODULE == MODULE_ENABLE

static void(*icu_interruptCallBack_ptr)(void);
static inline void set_timer1_clock(uint8 timer1Clock);
/* ----------------------------- SW Functions Definitions ------------------------------ */
Std_ReturnType ICU_init(const icu_ConfigType* a_icuObj_ptr)
{
	Std_ReturnType ret = E_OK;
	if(NULL == a_icuObj_ptr)
	{
		ret = E_NOT_OK;
	}
	else
	{
		/* Disable timer1 module */
		TCCR1B = NO_CLOCK;
		/* set edge detection */
		ICU_setEdgeDetectionType(a_icuObj_ptr->icu_edgeSelect);
		/* configure noise cancellation */
		switch(a_icuObj_ptr->icu_edgeSelect)
		{
		case ICU_NOISE_CANCEL_DISABLE:	CLEAR_BIT(TCCR1B, ICNC1);
			break;
		case ICU_NOISE_CANCEL_ENABLE:	SET_BIT(TCCR1B, ICNC1);
			break;
		default: CLEAR_BIT(TCCR1B, ICES1);
		break;
		}
		/* configure interrupt */
#if TIMER1_IC1_INTERRRUPT_FEATURE == INTERRUPT_FEATURE_ENABLE
		INTERRUPT_GLOBAL_ENABLE();
		TIMER1_CLEAR_IC1_INTERRUPT_FLAG();
		TIMER1_IC1_INTERRUPT_ENABLE();
		ret = ICU_setCallBack(a_icuObj_ptr->icu_interruptHandlerNotify);
#endif
		/* set TCNT1 initial value */
		TCNT1H = 0;
		TCNT1L = 0;
		/* set timer1 clock */
		set_timer1_clock(a_icuObj_ptr->timer1Clock);
	}
	return ret;
}

/*
 * Description: Function to set the Call Back function address.
 */
Std_ReturnType ICU_setCallBack(void(*a_ptr)(void))
{
	Std_ReturnType ret = E_OK;
	if(NULL == a_ptr)
	{
		ret = E_NOT_OK;
	}
	else
	{
		icu_interruptCallBack_ptr = a_ptr;
	}
	return ret;
}

/*
 * Description: Function to set the required edge detection.
 */
void ICU_setEdgeDetectionType(const e_icu_EdgeType_t a_icuEdgeType)
{
	/*
	 * Be aware that changing trigger source can trigger a capture.
	 * The Input Capture Flag must therefore be cleared after the change
	 */
	switch(a_icuEdgeType)
	{
	case ICU_FALLING_EDGE_DETECT:	CLEAR_BIT(TCCR1B, ICES1);
		break;
	case ICU_RISING_EDGE_DETECT:	SET_BIT(TCCR1B, ICES1);
		break;
	}
	TIMER1_CLEAR_IC1_INTERRUPT_FLAG();
}
/*
 * Description: Function to get the Timer1 Value when the input is captured
 *              The value stored at Input Capture Register ICR1
 */
Std_ReturnType ICU_getInputCaptureValue(uint16* a_icuData)
{
	Std_ReturnType ret = E_OK;
	if(NULL == a_icuData)
	{
		ret = E_NOT_OK;
	}
	else
	{	/* Reading the 16-bit value in the Input Capture Register (ICR1) is done by
	 	 * first reading the Low byte (ICR1L) and then the High byte (ICR1H)
	 	 */
		*a_icuData = ICR1L;
		*a_icuData = (uint16)ICR1H << 8;
	}
	return ret;
}

/*
 * Description: Function to clear the Timer1 Value to start count from ZERO
 */
void ICU_clearTimerValue(void)
{
	TCNT1 = 0;
}

/*
 * Description: Function to disable the Timer1 to stop the ICU Driver
 */
void ICU_DeInit(void)
{
	/* Clear All Timer1 Registers */
	TCCR1A = 0;
	TCCR1B = 0;
	TCNT1 = 0;

#if TIMER1_IC1_INTERRRUPT_FEATURE == INTERRUPT_FEATURE_ENABLE
	TIMER1_IC1_INTERRUPT_DISABLE();
#endif
}

/* ISR code on ADC Completion */
#if TIMER1_IC1_INTERRRUPT_FEATURE == INTERRUPT_FEATURE_ENABLE
ISR(TIMER1_CAPT_vect)
{
	if(NULL != icu_interruptCallBack_ptr)
	{
		icu_interruptCallBack_ptr();
	}
	/* clear ICU interrupt flag. */
	TIMER1_CLEAR_IC1_INTERRUPT_FLAG();
}
#endif

/*------------------------------ Helper Function Definitions ------------------------------*/
static inline void set_timer1_clock(uint8 timer1Clock)
{
	switch(timer1Clock)
	{
	case F_CPU_CLOCK:	SET_BIT(TCCR1B, CS10), CLEAR_BIT(TCCR1B, CS11), CLEAR_BIT(TCCR1B, CS12);
		break;
	case F_CPU_8:	CLEAR_BIT(TCCR1B, CS10), SET_BIT(TCCR1B, CS11), CLEAR_BIT(TCCR1B, CS12);
		break;
	case F_CPU_64:	SET_BIT(TCCR1B, CS10), SET_BIT(TCCR1B, CS11), CLEAR_BIT(TCCR1B, CS12);
		break;
	case F_CPU_256:	CLEAR_BIT(TCCR1B, CS10), CLEAR_BIT(TCCR1B, CS11), SET_BIT(TCCR1B, CS12);
		break;
	case F_CPU_1024:SET_BIT(TCCR1B, CS10), CLEAR_BIT(TCCR1B, CS11), SET_BIT(TCCR1B, CS12);
		break;
	default:		SET_BIT(TCCR1B, CS10), CLEAR_BIT(TCCR1B, CS11), CLEAR_BIT(TCCR1B, CS12);
	}
}
#endif
