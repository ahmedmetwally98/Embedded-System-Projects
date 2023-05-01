/* 
 * File:   Timer1.h
 * Author: ahmed
 *
 * Created on March 17, 2023, 11:41 PM
 */

#ifndef TIMER1_H
#define	TIMER1_H


/* --------------- Includes --------------- */
#include "../interrupt/mcal_internal_interrupt.h"

/* --------------- MACRO Declarations --------------- */
#define TIMER1_8BIT_REG_SIZE                0
#define TIMER1_16BIT_REG_SIZE               1

#define TIMER1_COUNTER_MODE                 1
#define TIMER1_TIMER_MODE                   0

#define TIMER1_OSCILLATOR_EABLE             1
#define TIMER1_OSCILLATOR_DISABLE           0

#define TIMER1_SYNC_COUNTER_MODE            0
#define TIMER1_ASYNC_COUNTER_MODE           1

// Pre-scaler values

#define TIMER1_PRESCALER_DIV_BY_1                   0x00
#define TIMER1_PRESCALER_DIV_BY_2                   0x01
#define TIMER1_PRESCALER_DIV_BY_4                   0x02
#define TIMER1_PRESCALER_DIV_BY_8                   0x03

//check interrupt priority availability
#if INTERRUPT_PRIORITY_FEATURE == INTERRUPT_FEATURE_ENABLE
#define TIMER1_INTERRUPT_PRIORITY_HIGH      1
#define TIMER1_INTERRUPT_PRIORITY_LOW       0
#endif

/* --------------- MACRO Function Declarations ---------------*/
#define TIMER1_MODULE_ENABLE()                  (T1CONbits.TMR1ON = 1)
#define TIMER1_MODULE_DISABLE()                 (T1CONbits.TMR1ON = 0)
/* Enable Read/Write from Timer1 Register as one 16-bit or two 8-bit Register(s) */
#define TIMER1_RW_8BIT_SET()                    (T1CONbits.RD16 = 0)
#define TIMER1_RW_16BIT_SET()                   (T1CONbits.RD16 = 1)
/* Enable Timer1 to operate in Timer/Counter mode */
#define TIMER1_COUNTER_MODE_SET_ENABLE()        (T1CONbits.TMR1CS = 1)
#define TIMER1_TIMER_MODE_SET_ENABLE()          (T1CONbits.TMR1CS = 0)
/* Enable/Disable Timer1 Secondary Oscillator */
#define TIMER1_SEC_OSCILLATOR_ENABLE()          (T1CONbits.T1OSCEN = 1)
#define TIMER1_SEC_OSCILLATOR_DISABLE()         (T1CONbits.T1OSCEN = 0)
/* This Enable counts to be A/synchronize with the TIMER1 external clock*/
#define TIMER1_SYNC_ENABLE()                    (T1CONbits.T1SYNC = 1)
#define TIMER1_ASYNC_ENABLE()                   (T1CONbits.T1SYNC = 0)
/* configure the Pre-scaler value of the Timer1 module */
#define TIMER1_PRESCALER_SET_VALUE(_PRESCALE)   (T1CONbits.T1CKPS = (_PRESCALE))
/* Read System Clock Status ,where:
 * 1->clk drived from TMR1 Oscillator
 * 0->clc drived from another source */
#define TIMER1_READ_SYSTEM_CLOCK_STATUS()       (T1CONbits.T1RUN)

/* --------------- Data Type Declarations --------------- */
typedef struct{
    uint16 preload_value;
#if TIMER1_INTERRUPT_FEATURE == INTERRUPT_FEATURE_ENABLE
    void (*TMR1_InterruptHandler)(void);
#if INTERRUPT_PRIORITY_FEATURE == INTERRUPT_FEATURE_ENABLE
    uint8 timer1_INT_priority;
#endif
#endif
    uint8 timer1_mode                           :1;
    uint8 timer1_prescaler_value                :2;
    uint8 timer1_RW_mode                        :1;
    uint8 timer1_oscillator                     :1;
    uint8 timer1_counter_sync                   :1;
    uint8 timer1_reserved                       :2;
}timer1_config_t;

/* --------------- Functions Declarations ---------------*/
Std_ReturnType Timer1_Init(const timer1_config_t* _timer1);
Std_ReturnType Timer1_DeInit(const timer1_config_t* _timer1);
Std_ReturnType Timer1_write_value(const timer1_config_t* _timer1, uint16 _preload_value);
Std_ReturnType Timer1_read_value(const timer1_config_t* _timer1, uint16 *_value);

void TMR1_ISR(void);

#endif	/* TIMER1_H */

