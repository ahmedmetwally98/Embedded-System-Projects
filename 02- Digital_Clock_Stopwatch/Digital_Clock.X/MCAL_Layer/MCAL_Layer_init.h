/* 
 * File:   MCAL_Layer_init.h
 * Author: ahmed
 *
 * Created on March 1, 2023, 5:30 PM
 */

#ifndef MCAL_LAYER_INIT_H
#define	MCAL_LAYER_INIT_H

/*--------------- Includes ---------------------*/
#include "mcal_std_types.h"
#include "std_libraries.h"
#include "compiler.h"
#include "device_config.h"

#include "Timer3/Timer3.h"
#include "Timer1/Timer1.h"
#include "interrupt/mcal_external_interrupt.h"

/*--------------- Functions Declarations ---------------------*/
Std_ReturnType MCAL_Layer_init(void);
extern void tmr1_callBackNotify(void);
extern void tmr3_callBackNotify(void);
extern void interrupt1_callBackNotify_changeProgram(void);
extern void interrupt2_callBackNotify_changeClock(void);
extern void reset_stopWatch(uint8);
extern void stop_stopWatch(uint8);
extern void resume_stopWatch(uint8);

#endif	/* MCAL_LAYER_INIT_H */

