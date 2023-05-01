/* 
 * File:   mcal_internal_interrupt.h
 * Author: ahmed
 *
 * Created on February 16, 2023, 11:16 PM
 */

#ifndef MCAL_INTERNAL_INTERRUPT_H
#define	MCAL_INTERNAL_INTERRUPT_H

/* Section : Includes */
#include "mcal_interrupt_config.h"
#include "mcal_interrupt_manager.h"


/* ----------------- Global Variable Section ----------------- */



/* ----------------- MACRO Declarations ----------------- */

/* ----------------- MACRO Function Declarations ----------------- */

#if TIMER0_INTERRUPT_FEATURE == INTERRUPT_FEATURE_ENABLE
/* This routine Disable the Interrupt for the TIMER0 module */
#define TIMER0_INTERRUPT_DISABLE()             (INTCONbits.TMR0IE = 0)
/* This routine Enable the Interrupt for the TIMER0 module */
#define TIMER0_INTERRUPT_ENABLE()              (INTCONbits.TMR0IE = 1)
/* This routine Clear the Interrupt flag for the TIMER0 module */
#define TIMER0_CLEAR_INTERRUPT_FLAG()          (INTCONbits.TMR0IF = 0)
#if INTERRUPT_PRIORITY_FEATURE == INTERRUPT_FEATURE_ENABLE
/* Set TIMER0 High priority Interrupt feature */
#define TIMER0_INTERRUPT_SET_PriorityHigh()    (INTCON2bits.TMR0IP = 1)
/* Set TIMER0 Low priority Interrupt feature */
#define TIMER0_INTERRUPT_SET_PriorityLow()     (INTCON2bits.TMR0IP = 0)
#endif
#endif

#if TIMER1_INTERRUPT_FEATURE == INTERRUPT_FEATURE_ENABLE
/* This routine Disable the Interrupt for the TIMER1 module */
#define TIMER1_INTERRUPT_DISABLE()             (PIE1bits.TMR1IE = 0)
/* This routine Enable the Interrupt for the TMR1 module */
#define TIMER1_INTERRUPT_ENABLE()              (PIE1bits.TMR1IE = 1)
/* This routine Clear the Interrupt flag for the TMR1 module */
#define TIMER1_CLEAR_INTERRUPT_FLAG()          (PIR1bits.TMR1IF = 0)
#if INTERRUPT_PRIORITY_FEATURE == INTERRUPT_FEATURE_ENABLE
/* Set TIMER1 High priority Interrupt feature */
#define TIMER1_INTERRUPT_SET_PriorityHigh()    (IPR1bits.TMR1IP = 1)
/* Set TIMER1 Low priority Interrupt feature */
#define TIMER1_INTERRUPT_SET_PriorityLow()     (IPR1bits.TMR1IP = 0)
#endif
#endif

#if TIMER2_INTERRUPT_FEATURE == INTERRUPT_FEATURE_ENABLE
/* This routine Disable the Interrupt for the TIMER2 module */
#define TIMER2_INTERRUPT_DISABLE()             (PIE1bits.TMR2IE = 0)
/* This routine Enable the Interrupt for the TMR2 module */
#define TIMER2_INTERRUPT_ENABLE()              (PIE1bits.TMR2IE = 1)
/* This routine Clear the Interrupt flag for the TMR2 module */
#define TIMER2_CLEAR_INTERRUPT_FLAG()          (PIR1bits.TMR2IF = 0)
#if INTERRUPT_PRIORITY_FEATURE == INTERRUPT_FEATURE_ENABLE
/* Set TIMER2 High priority Interrupt feature */
#define TIMER2_INTERRUPT_SET_PriorityHigh()    (IPR1bits.TMR2IP = 1)
/* Set TIMER2 Low priority Interrupt feature */
#define TIMER2_INTERRUPT_SET_PriorityLow()     (IPR1bits.TMR2IP = 0)
#endif
#endif

#if TIMER3_INTERRUPT_FEATURE == INTERRUPT_FEATURE_ENABLE
/* This routine Disable the Interrupt for the TIMER3 module */
#define TIMER3_INTERRUPT_DISABLE()             (PIE2bits.TMR3IE = 0)
/* This routine Enable the Interrupt for the TMR3 module */
#define TIMER3_INTERRUPT_ENABLE()              (PIE2bits.TMR3IE = 1)
/* This routine Clear the Interrupt flag for the TMR3 module */
#define TIMER3_CLEAR_INTERRUPT_FLAG()          (PIR2bits.TMR3IF = 0)
#if INTERRUPT_PRIORITY_FEATURE == INTERRUPT_FEATURE_ENABLE
/* Set TIMER3 High priority Interrupt feature */
#define TIMER3_INTERRUPT_SET_PriorityHigh()    (IPR2bits.TMR3IP = 1)
/* Set TIMER3 Low priority Interrupt feature */
#define TIMER3_INTERRUPT_SET_PriorityLow()     (IPR2bits.TMR3IP = 0)
#endif
#endif

/* Section : Data Type Declarations */

/* Section : Functions Declarations */  


#endif	/* MCAL_INTERNAL_INTERRUPT_H */

