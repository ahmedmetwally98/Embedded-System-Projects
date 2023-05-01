/* 
 * File:   mcal_interrupt_config.h
 * Author: ahmed
 *
 * Created on February 16, 2023, 11:15 PM
 */

#ifndef MCAL_INTERRUPT_CONFIG_H
#define	MCAL_INTERRUPT_CONFIG_H

/* --------------- Includes ---------------*/
#include "../mcal_std_types.h"
#include "../std_libraries.h"
#include "../device_config.h"
#include "../Limits.h"
#include "../GPIO/hal_gpio.h"
#include "macl_interrupt_gen_cfg.h"

/* --------------- MACRO Declarations ---------------*/
#define INTERRUPT_ENABLE            1U
#define INTERRUPT_DISABLE           0U
#define INTERRUPT_OCCUR             1U
#define INTERRUPT_NOT_OCCUR         0U

#define LOW_PRIORITY                0u
#define HIGH_PRIORITY               1u

/* --------------- MACRO Function Declarations --------------- */
#if (INTERRUPT_PRIORITY_FEATURE == INTERRUPT_FEATURE_ENABLE)
/* Enable priority feature */
#define INTERRUPT_PriorityLevelsEnable()            (RCONbits.IPEN = 1)
/* Disable priority feature */
#define INTERRUPT_PriorityLevelsDisable()           (RCONbits.IPEN = 0)
/* Enable all High priority interrupt */
#define INTERRUPT_GlobalInterruptHighEnable()       (INTCONbits.GIEH = 1)
/* Disable all High priority interrupt */
#define INTERRUPT_GlobalInterruptHighDisable()      (INTCONbits.GIEH = 0)
/* Enable all Low priority interrupt */
#define INTERRUPT_GlobalInterruptLowEnable()        (INTCONbits.GIEL = 1)
/* Disable all Low priority interrupt */
#define INTERRUPT_GlobalInterruptLowDisable()       (INTCONbits.GIEL = 0)
#endif 
/* Enable general interrupt */
#define INTERRUPT_GlobalInterruptEnable()           (INTCONbits.GIE = 1)
/* Disable general interrupt */
#define INTERRUPT_GlobalInterruptDisable()           (INTCONbits.GIE = 0)
/* Enable all Peripheral interrupt */
#define INTERRUPT_PeripheralInterruptEnable()       (INTCONbits.PEIE = 1)
/* Disable all Peripheral interrupt */
#define INTERRUPT_PeripheralInterruptDisable()      (INTCONbits.PEIE = 0)

/* --------------- Data Type Declarations --------------- */

/* --------------- Functions Declarations --------------- */


#endif	/* MCAL_INTERRUPT_CONFIG_H */

