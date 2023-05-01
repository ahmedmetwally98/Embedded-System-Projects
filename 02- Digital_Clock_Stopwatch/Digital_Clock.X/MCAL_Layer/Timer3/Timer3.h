/* 
 * File:   Timer3.h
 * Author: ahmed
 *
 * Created on March 20, 2023, 4:13 PM
 */

#ifndef TIMER3_H
#define	TIMER3_H

/* --------------- Includes --------------- */
#include "../interrupt/mcal_internal_interrupt.h"

/* --------------- MACRO Declarations --------------- */
// Pre-scaler values
#define TIMER3_PRESCALER_DIV_BY_1                   0x00
#define TIMER3_PRESCALER_DIV_BY_2                   0x01
#define TIMER3_PRESCALER_DIV_BY_4                   0x02
#define TIMER3_PRESCALER_DIV_BY_8                   0x03

#define TIMER3_8BIT_REG_SIZE                0
#define TIMER3_16BIT_REG_SIZE               1

#define TIMER3_COUNTER_MODE                 1
#define TIMER3_TIMER_MODE                   0

#define TIMER3_SYNC_COUNTER_MODE            0
#define TIMER3_ASYNC_COUNTER_MODE           1

/* --------------- MACRO Function Declarations ---------------*/
#define TIMER3_MODULE_ENABLE()                  (T3CONbits.TMR3ON = 1)
#define TIMER3_MODULE_DISABLE()                 (T3CONbits.TMR3ON = 0)
/* Enable Read/Write from Timer3 Register as one 16-bit or two 8-bit Register(s) */
#define TIMER3_RW_8BIT_SET()                    (T3CONbits.RD16 = 0)
#define TIMER3_RW_16BIT_SET()                   (T3CONbits.RD16 = 1)
/* Enable Timer3 to operate in Timer/Counter mode */
#define TIMER3_COUNTER_MODE_SET_ENABLE()        (T3CONbits.TMR3CS = 1)
#define TIMER3_TIMER_MODE_SET_ENABLE()          (T3CONbits.TMR3CS = 0)
/* This Enable counts to be A/synchronize with the TIMER3 external clock*/
#define TIMER3_COUNTER_SYNC_ENABLE()            (T3CONbits.T3SYNC = 1)
#define TIMER3_COUNTER_ASYNC_ENABLE()           (T3CONbits.T3SYNC = 0)
/* configure the Pre-scaler value of the Timer3 module */
#define TIMER3_PRESCALER_SET_VALUE(_PRESCALE)   (T3CONbits.T3CKPS = (_PRESCALE))

/* --------------- Data Type Declarations --------------- */
typedef struct{
    uint16 preload_value;
#if TIMER3_INTERRUPT_FEATURE == INTERRUPT_FEATURE_ENABLE
    void (*TMR3_InterruptHandler)(void);
#if INTERRUPT_PRIORITY_FEATURE == INTERRUPT_FEATURE_ENABLE
    uint8 timer3_INT_priority;
#endif
#endif
    uint8 timer3_mode                           :1;
    uint8 timer3_prescaler_value                :2;
    uint8 timer3_RW_mode                        :1;
    uint8 timer3_counter_sync                   :1;
    uint8 timer3_reserved                       :3;
}timer3_config_t;

/* ---------------- Functions Declarations ---------------- */
Std_ReturnType Timer3_Init(const timer3_config_t* _timer3);
Std_ReturnType Timer3_DeInit(const timer3_config_t* _timer3);
Std_ReturnType Timer3_write_value(const timer3_config_t* _timer3, uint16 _preload_value);
Std_ReturnType Timer3_read_value(const timer3_config_t* _timer3, uint16 *_value);

void TMR3_ISR(void);

#endif	/* TIMER3_H */

