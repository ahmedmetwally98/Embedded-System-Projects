/*
 * mcal.h
 *
 *  Created on: Apr 11, 2023
 *      Author: ahmed
 */

#ifndef MCAL_MCAL_H_
#define MCAL_MCAL_H_

/* -------------------- Includes -------------------- */
#include "Timer_16bit/hal_timer1.h"
#include "Interrupt_Driver/INT_External.h"

/* -------------------- MACRO Definitions -------------------- */

/* -------------------- MACRO Functions Definitions -------------------- */

/* -------------------- Data Type Declarations -------------------- */

/* -------------------- Software Interfaces -------------------- */
extern void timer1_countEndNotify(void);
extern void int1_eventOccurNotify(void);

Std_ReturnType MCAL_initLayer(void);


#endif /* MCAL_MCAL_H_ */
