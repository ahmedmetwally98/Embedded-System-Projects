/*
 * Interrupt_config.h
 *
 *  Created on: Mar 16, 2023
 *      Author: ahmed
 */

#ifndef INTERRUPT_CONFIG_H_
#define INTERRUPT_CONFIG_H_

/* --------------- Includes ---------------*/
#include "../../micro_config.h"
#include "../../std_types.h"
#include "../../common_macros.h"
#include "Interrupt_gen_config.h"

/* --------------- MACRO Declarations --------------- */
#define INTERRUPT_ENABLE            1U
#define INTERRUPT_DISABLE           0U
#define INTERRUPT_OCCUR             1U
#define INTERRUPT_NOT_OCCUR         0U

/*--------------- MACRO FUNCTIONS --------------- */
#define INTERRUPT_GLOBAL_ENABLE()			(SET_BIT(SREG, 7))
#define INTERRUPT_GLOBAL_DISABLE()			(CLEAR_BIT(SREG, 7))

#if INTERRUPT_NESTING_FEATURE == INTERRUPT_FEATURE_ENABLE
// called at the start of each ISR() for Enable Interrupt nesting feature if required
#define INTERRUPT_NESTING_SET_ENABLE()	(SET_BIT(SREG, 7))
#endif

#endif /* INTERRUPT_CONFIG_H_ */
