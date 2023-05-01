/*
 * INT_Internal.h
 *
 *  Created on: Mar 16, 2023
 *      Author: ahmed
 */

#ifndef INT_INTERNAL_H_
#define INT_INTERNAL_H_



/* -------------------- Includes -------------------- */
#include "Interrupt_config.h"

/* -------------------- MACRO Definitions -------------------- */

/* -------------------- MACRO Functions Definitions -------------------- */
#if TIMER0_INTERRUPT_FEATURE == INTERRUPT_FEATURE_ENABLE
#define TIMER0_OVERFLOW_INTERRUPT_ENABLE()						(SET_BIT(TIMSK,TOIE0))
#define TIMER0_OVERFLOW_INTERRUPT_DISABLE()						(CLEAR_BIT(TIMSK, TOIE0))
#define TIMER0_CLEAR_OVERFLOW_INTERRUPT_FLAG()					(SET_BIT(TIFR, TOV0))

#define TIMER0_OUTPUT_COMPARE_INTERRUPT_ENABLE()				(SET_BIT(TIMSK,OCIE0))
#define TIMER0_OUTPUT_COMPARE_INTERRUPT_DISABLE()				(CLEAR_BIT(TIMSK, OCIE0))
#define TIMER0_CLEAR_OUTPUT_COMPARE_INTERRUPT_FLAG()			(SET_BIT(TIFR, OCF0))
#endif

#if ADC_INTERRUPT_FEATURE == INTERRUPT_FEATURE_ENABLE
#define ADC_INTERRUPT_ENABLE()									(SET_BIT(ADCSRA, ADIE))
#define ADC_INTERRUPT_DISABLE()									(CLEAR_BIT(ADCSRA, ADIE))
#define ADC_CLEAR_INTERRUPT_FLAG()								(SET_BIT(ADCSRA, ADIF))
#endif
/* -------------------- Data Type Declarations -------------------- */


/* -------------------- Software Interfaces -------------------- */


#endif /* INT_INTERNAL_H_ */
