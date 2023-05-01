/* 
 * File:   MCAL_Layer_init.c
 * Author: ahmed
 *
 * Created on March 1, 2023, 5:30 PM
 */


#include "MCAL_Layer_init.h"

// Timer1 works for Digital Clock
timer1_config_t g_tmr1Obj = {
.preload_value=3036,
.TMR1_InterruptHandler=tmr1_callBackNotify,
.timer1_RW_mode=TIMER1_8BIT_REG_SIZE,
.timer1_mode=TIMER1_TIMER_MODE,
.timer1_prescaler_value=TIMER1_PRESCALER_DIV_BY_8,
};

// Timer3 works for Stopwatch
timer3_config_t g_tmr3Obj = {
.preload_value=3036,
.TMR3_InterruptHandler=tmr3_callBackNotify,
.timer3_RW_mode=TIMER3_8BIT_REG_SIZE,
.timer3_mode=TIMER3_TIMER_MODE,
.timer3_prescaler_value=TIMER3_PRESCALER_DIV_BY_8,
};

//define interrupt 0 for program changing
interrupt_INTx_t g_int0Obj_changeProgram = {
.INTx_src=EXT_INT0,
.INTx_edge=INTERRUPT_INTx_RISING_EDGE,
.INTx_mcu_pin={PORTB_INDEX, GPIO_PIN0, GPIO_DIRECTION_INPUT},
.EXT_InterruptHandler=interrupt1_callBackNotify_changeProgram
};
//define interrupt 1 for changing the clock in digital clock mode
interrupt_INTx_t g_int1Obj_changeClock = {
.INTx_src=EXT_INT1,
.INTx_edge=INTERRUPT_INTx_RISING_EDGE,
.INTx_mcu_pin={PORTB_INDEX, GPIO_PIN1, GPIO_DIRECTION_INPUT},
.EXT_InterruptHandler=interrupt2_callBackNotify_changeClock
};
//define 3 interrupt for 3 features stopwatch mode
interrupt_RBx_t g_intRB1_reset = {
.mcu_pin={PORTB_INDEX, GPIO_PIN5, GPIO_DIRECTION_INPUT},
.RBx_EXT_InterruptHandler= reset_stopWatch
};
interrupt_RBx_t g_intRB2_stop = {
.mcu_pin={PORTB_INDEX, GPIO_PIN6, GPIO_DIRECTION_INPUT},
.RBx_EXT_InterruptHandler= stop_stopWatch
};
interrupt_RBx_t g_intRB3_resume = {
.mcu_pin={PORTB_INDEX, GPIO_PIN7, GPIO_DIRECTION_INPUT},
.RBx_EXT_InterruptHandler= resume_stopWatch
};

Std_ReturnType ret = E_OK;
Std_ReturnType MCAL_Layer_init(void)
{
    // initialize the digital clock timer1
    ret = Timer1_Init(&g_tmr1Obj);
    // initialize the interrupt INT0 that used for changing the application program
    ret = Interrupt_INTx_Init(&g_int0Obj_changeProgram);
    ret = Interrupt_INTx_Init(&g_int1Obj_changeClock);
    ret = Interrupt_RBx_Init(&g_intRB1_reset);
    ret = Interrupt_RBx_Init(&g_intRB2_stop);
    ret = Interrupt_RBx_Init(&g_intRB3_resume);
    // initialize PORTD that used to control Seven segment multiplexing
    ret = GPIO_port_direction_initialize(PORTD_INDEX, 0b11000000);
    return ret;
}
