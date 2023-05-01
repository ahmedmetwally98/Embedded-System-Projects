
/* 
 * File:   Timer1.h
 * Author: ahmed
 *
 * Created on March 17, 2023, 11:41 PM
 */

#include "Timer1.h"

/* ----------------- static global variables definitions ----------------- */
#if TIMER1_INTERRUPT_FEATURE == INTERRUPT_FEATURE_ENABLE
static void (*TMR1_InterruptHandler)(void) = NULL;
#endif
static uint16 timer1_preload = 0;

/* ----------------- Helper Functions Declarations ----------------- */
static inline void timer1_mode_select(const timer1_config_t* _timer1);
static inline void timer1_RW_reg_size_select(const timer1_config_t* _timer1);

/* ----------------- Software Interfaces Definitions ----------------- */
Std_ReturnType Timer1_Init(const timer1_config_t* _timer1)
{
    Std_ReturnType ret = E_OK;
    if(_timer1 == NULL)
    {
        ret = E_NOT_OK;
    }
    else
    {   /* disable timer1 module for starting configurations */
        TIMER1_MODULE_DISABLE();
        /* starting timer1 interrupt configurations */
#if TIMER1_INTERRUPT_FEATURE == INTERRUPT_FEATURE_ENABLE
        TIMER1_CLEAR_INTERRUPT_FLAG();  // clear TIMER1 INT flag
        TIMER1_INTERRUPT_ENABLE();      // enable TIMER1 INT 
        /* configure callBack function */
        TMR1_InterruptHandler = _timer1->TMR1_InterruptHandler;
        /* checking timer1 interrupt priority */
#if INTERRUPT_PRIORITY_FEATURE == INTERRUPT_FEATURE_ENABLE
        INTERRUPT_PriorityLevelsEnable();   // enable priority bit
        INTERRUPT_GlobalInterruptHighEnable();  // enable global interrupts
        if(_timer1->timer1_INT_priority == HIGH_PRIORITY)
        {
            TIMER1_INTERRUPT_SET_PriorityHigh();
        }
        else if (_timer1->timer1_INT_priority == LOW_PRIORITY)
        {
            TIMER1_INTERRUPT_SET_PriorityLow();
            INTERRUPT_GlobalInterruptLowEnable();   // enable low priority
        } 
#else 
        INTERRUPT_GlobalInterruptEnable();      // enable global interrupts
        INTERRUPT_PeripheralInterruptEnable();  // enable peripheral interrupts
#endif
#endif
        /* check timer1 modes if Timer/Counter mode */
        timer1_mode_select(_timer1);
        /* check timer1 R/W register mode 8-bit / 16-bit
         * And set timer1 registers with pre-load value */
        timer1_RW_reg_size_select(_timer1);
        /* Saving the pre-load value for refilling when interrupt happens */
        timer1_preload = _timer1->preload_value;
        /* check pre-scaler assignment */
        TIMER1_PRESCALER_SET_VALUE(_timer1->timer1_prescaler_value);
        /* Set timer1 registers with initial value */
        TMR1H = ((_timer1->preload_value) >> 8);
        TMR1L = (uint8)(_timer1->preload_value);
        if(_timer1->timer1_oscillator==TIMER1_OSCILLATOR_EABLE)
        {
            TIMER1_SEC_OSCILLATOR_ENABLE();
        }
        else
        {
            TIMER1_SEC_OSCILLATOR_DISABLE();
        }
        // enable timer1 module after finishing the configurations
        TIMER1_MODULE_ENABLE();
    }
    return ret;
}
Std_ReturnType Timer1_DeInit(const timer1_config_t* _timer1)
{
    Std_ReturnType ret = E_OK;
    if(_timer1 == NULL)
    {
        ret = E_NOT_OK;
    }
    else
    {
        /* disable timer1 interrupt feature */
#if TIMER1_INTERRUPT_FEATURE == INTERRUPT_FEATURE_ENABLE
        TIMER1_CLEAR_INTERRUPT_FLAG();  // clear TIMER1 INT flag
        TIMER1_INTERRUPT_DISABLE();      // disable TIMER1 INT
#endif
        /* disable timer1 module */
        TIMER1_MODULE_DISABLE();
    }
    return ret;
}
Std_ReturnType Timer1_write_value(const timer1_config_t* _timer1, uint16 _preload_value)
{
    Std_ReturnType ret = E_OK;
    if(_timer1 == NULL)
    {
        ret = E_NOT_OK;
    }
    else
    {
        TMR1H = (_preload_value) >> 8;
        TMR1L = (uint8)(_preload_value);
    }
    return ret;
}
Std_ReturnType Timer1_read_value(const timer1_config_t* _timer1, uint16 *_value)
{
    uint8 l_tmr1l = ZERO_INIT, l_tmr1h = ZERO_INIT;
    Std_ReturnType ret = E_OK;
    if(_timer1 == NULL || _value == NULL)
    {
        ret = E_NOT_OK;
    }
    else
    {
        l_tmr1l = TMR1L;
        l_tmr1h = TMR1H;
        *_value = (uint16)((uint16)l_tmr1l + ((uint16)l_tmr1h << 8));    
    }
    return ret;
}

#if TIMER1_INTERRUPT_FEATURE == INTERRUPT_FEATURE_ENABLE
void TMR1_ISR(void)
{
    // clearing timer1 interrupt flag
    TIMER1_CLEAR_INTERRUPT_FLAG();
    
    /* ISR code */
    // fill timer1 registers with the pre-load value.
    TMR1H = ((timer1_preload) >> 8);
    TMR1L = (uint8)(timer1_preload);
    /* Notify the Application that Timer1 interrupt is finished! */
    if(TMR1_InterruptHandler)
    {
        TMR1_InterruptHandler();
    }
}
#endif
/* ----------------- Helper Functions Definitions ----------------- */

static inline void timer1_mode_select(const timer1_config_t* _timer1)
{
    /* check timer1 modes */
    if(_timer1->timer1_mode == TIMER1_COUNTER_MODE)
    {
        TIMER1_COUNTER_MODE_SET_ENABLE();
        /* T1OSI, T1OSO pins in PORTC are configured as Digital input pin automatically */
        /* check for Sync Option */
        if(_timer1->timer1_counter_sync == TIMER1_SYNC_COUNTER_MODE)
        {
            TIMER1_SYNC_ENABLE();
        }
        else if(_timer1->timer1_counter_sync == TIMER1_ASYNC_COUNTER_MODE)
        {
            TIMER1_ASYNC_ENABLE();
        }
    }
    else if(_timer1->timer1_mode == TIMER1_TIMER_MODE)
    {
        TIMER1_TIMER_MODE_SET_ENABLE();
    }
}

static inline void timer1_RW_reg_size_select(const timer1_config_t* _timer1)
{
    /* check timer1 RW register mode 8-bit/16-bit */
    if(_timer1->timer1_RW_mode == TIMER1_16BIT_REG_SIZE)
    {
        TIMER1_RW_16BIT_SET();
    }
    else
    {
        // Default case
        TIMER1_RW_8BIT_SET();
    }
}