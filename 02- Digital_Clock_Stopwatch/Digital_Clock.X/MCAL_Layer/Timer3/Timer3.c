/* 
 * File:   Timer3.c
 * Author: ahmed
 *
 * Created on March 20, 2023, 4:13 PM
 */

#include "Timer3.h"

/* ----------------- static global variables definitions ----------------- */
#if TIMER1_INTERRUPT_FEATURE == INTERRUPT_FEATURE_ENABLE
static void (*TMR3_InterruptHandler)(void) = NULL;
#endif
static uint16 timer3_preload = 0;

/* ----------------- Helper Functions Declarations ----------------- */
static inline void timer3_mode_select(const timer3_config_t* _timer3);
static inline void timer3_RW_reg_size_select(const timer3_config_t* _timer3);


/* ----------------- Software Interfaces Definitions ----------------- */
Std_ReturnType Timer3_Init(const timer3_config_t* _timer3)
{
    Std_ReturnType ret = E_OK;
    if(_timer3 == NULL)
    {
        ret = E_NOT_OK;
    }
    else
    {   /* disable timer3 module for starting configurations */
        TIMER3_MODULE_DISABLE();
        /* starting timer3 interrupt configurations */
#if TIMER3_INTERRUPT_FEATURE == INTERRUPT_FEATURE_ENABLE
        TIMER3_CLEAR_INTERRUPT_FLAG();  // clear TIMER3 INT flag
        TIMER3_INTERRUPT_ENABLE();      // enable TIMER3 INT 
        /* configure callBack function */
        TMR3_InterruptHandler = _timer3->TMR3_InterruptHandler;
        /* checking timer3 interrupt priority */
#if INTERRUPT_PRIORITY_FEATURE == INTERRUPT_FEATURE_ENABLE
        INTERRUPT_PriorityLevelsEnable();   // enable priority bit
        INTERRUPT_GlobalInterruptHighEnable();  // enable global interrupts
        if(_timer3->timer3_INT_priority == HIGH_PRIORITY)
        {
            TIMER3_INTERRUPT_SET_PriorityHigh();
        }
        else if (_timer3->timer3_INT_priority == LOW_PRIORITY)
        {
            TIMER3_INTERRUPT_SET_PriorityLow();
            INTERRUPT_GlobalInterruptLowEnable();   // enable low priority
        } 
#else 
        INTERRUPT_GlobalInterruptEnable();      // enable global interrupts
        INTERRUPT_PeripheralInterruptEnable();  // enable peripheral interrupts
#endif
#endif
        /* check timer3 modes if Timer/Counter mode */
        timer3_mode_select(_timer3);
        /* check timer3 R/W register mode 8-bit / 16-bit */
        timer3_RW_reg_size_select(_timer3);
        /* Set timer3 registers with initial value */
        TMR3H = ((_timer3->preload_value) >> 8);
        TMR3L = (uint8)(_timer3->preload_value);
        /* Saving the pre-load value for refilling when interrupt happens */
        timer3_preload = _timer3->preload_value;
        /* check pre-scaler assignment */
        TIMER3_PRESCALER_SET_VALUE(_timer3->timer3_prescaler_value);
        // enable timer1 module after finishing the configurations
        TIMER3_MODULE_ENABLE();
    }
    return ret;
}
Std_ReturnType Timer3_DeInit(const timer3_config_t* _timer3)
{
    Std_ReturnType ret = E_OK;
    if(_timer3 == NULL)
    {
        ret = E_NOT_OK;
    }
    else
    {
        /* disable timer3 interrupt feature */
#if TIMER3_INTERRUPT_FEATURE == INTERRUPT_FEATURE_ENABLE
        TIMER3_CLEAR_INTERRUPT_FLAG();  // clear TIMER3 INT flag
        TIMER3_INTERRUPT_DISABLE();      // disable TIMER3 INT
#endif
        /* disable timer3 module */
        T3CON = 0;
    }
    return ret;
}

Std_ReturnType Timer3_write_value(const timer3_config_t* _timer3, uint16 _preload_value)
{
    Std_ReturnType ret = E_OK;
    if(_timer3 == NULL)
    {
        ret = E_NOT_OK;
    }
    else
    {
        TMR3H = (_preload_value) >> 8;
        TMR3L = (uint8)(_preload_value);
    }
    return ret;
}

Std_ReturnType Timer3_read_value(const timer3_config_t* _timer3, uint16 *_value)
{
    uint8 l_tmr3l = ZERO_INIT, l_tmr3h = ZERO_INIT;
    Std_ReturnType ret = E_OK;
    if(_timer3 == NULL || _value == NULL)
    {
        ret = E_NOT_OK;
    }
    else
    {
        l_tmr3l = TMR3L;
        l_tmr3h = TMR3H;
        *_value = (uint16)((uint16)l_tmr3l + ((uint16)l_tmr3h << 8));    
    }
    return ret;
}
#if TIMER1_INTERRUPT_FEATURE == INTERRUPT_FEATURE_ENABLE
void TMR3_ISR(void)
{
    // clearing timer1 interrupt flag
    TIMER3_CLEAR_INTERRUPT_FLAG();
    
    /* ISR code */
    // fill timer1 registers with the pre-load value.
    TMR3H = ((timer3_preload) >> 8);
    TMR3L = (uint8)(timer3_preload);
    /* Notify the Application that Timer1 interrupt is finished! */
    if(TMR3_InterruptHandler)
    {
        TMR3_InterruptHandler();
    }
}
#endif
/* ----------------- Helper Functions Definitions ----------------- */

static inline void timer3_mode_select(const timer3_config_t* _timer3)
{
    /* check timer3 modes */
    if(_timer3->timer3_mode == TIMER3_COUNTER_MODE)
    {
        TIMER3_COUNTER_MODE_SET_ENABLE();
        /* check for Sync Option */
        if(_timer3->timer3_counter_sync == TIMER3_SYNC_COUNTER_MODE)
        {
            TIMER3_COUNTER_SYNC_ENABLE();
        }
        else if(_timer3->timer3_counter_sync == TIMER3_ASYNC_COUNTER_MODE)
        {
            TIMER3_COUNTER_ASYNC_ENABLE();
        }
    }
    else if(_timer3->timer3_mode == TIMER3_TIMER_MODE)
    {
        TIMER3_TIMER_MODE_SET_ENABLE();
    }
}

static inline void timer3_RW_reg_size_select(const timer3_config_t* _timer3)
{
    /* check timer3 RW register mode 8-bit/16-bit */
    if(_timer3->timer3_RW_mode == TIMER3_16BIT_REG_SIZE)
    {
        TIMER3_RW_16BIT_SET();
    }
    else
    {   // default value
        TIMER3_RW_8BIT_SET();
    }
}