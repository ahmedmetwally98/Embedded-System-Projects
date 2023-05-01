/* 
 * File:   mcal_interrupt_manager.h
 * Author: ahmed
 *
 * Created on February 16, 2023, 11:18 PM
 */

#ifndef MCAL_INTERRUPT_MANAGER_H
#define	MCAL_INTERRUPT_MANAGER_H

/* Section : Includes */
#include "mcal_interrupt_config.h"

/* Section : MACRO Declarations */

/* Section : MACRO Function Declarations */

/* Section : Data Type Declarations */

/* Section : Functions Declarations */
extern void INT_RB4_ISR(uint8);
extern void INT_RB5_ISR(uint8);
extern void INT_RB6_ISR(uint8);
extern void INT_RB7_ISR(uint8);
extern void INT0_ISR(void);
extern void INT1_ISR(void);
extern void INT2_ISR(void);

extern void TMR1_ISR(void);
extern void TMR3_ISR(void);

#endif	/* MCAL_INTERRUPT_MANAGER_H */

