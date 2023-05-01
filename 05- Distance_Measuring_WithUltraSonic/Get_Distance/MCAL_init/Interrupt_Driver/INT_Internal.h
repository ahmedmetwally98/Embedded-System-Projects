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


#if TIMER1_IC1_INTERRRUPT_FEATURE == INTERRUPT_FEATURE_ENABLE
#define TIMER1_IC1_INTERRUPT_ENABLE()							(SET_BIT(TIMSK,TICIE1))
#define TIMER1_IC1_INTERRUPT_DISABLE()							(CLEAR_BIT(TIMSK, TICIE1))
#define TIMER1_CLEAR_IC1_INTERRUPT_FLAG()						(SET_BIT(TIFR, ICF1))
#endif

/* -------------------- Data Type Declarations -------------------- */


/* -------------------- Software Interfaces -------------------- */


#endif /* INT_INTERNAL_H_ */
