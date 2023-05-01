/*
 * Timer0.h
 *
 *  Created on: Mar 16, 2023
 *      Author: ahmed
 */

#ifndef TIMER0_TIMER0_H_
#define TIMER0_TIMER0_H_

/* -------------------- Includes -------------------- */
#include "../Interrupt_Driver/INT_Internal.h"

#if TIMER0_MODULE == MODULE_ENABLE
/* -------------------- MACRO Definitions -------------------- */
// Timer0 General Modes
#define TIMER0_NORMAL_MODE					(0)
#define TIMER0_CLEAR_TIMER_COMPARE_MODE		(2u)
#define TIMER0_FAST_PWM_MODE				(3u)
#define TIMER0_PHASE_CORRECT_PWM_MODE		(1u)
// choose OC0 pin action
#define TIMER0_CTC_PIN_DISCONNECTED			(0u)
#define TIMER0_CTC_SET_PIN					(1u)
#define TIMER0_CTC_CLEAR_PIN				(2u)
#define TIMER0_CTC_TOGGLE_PIN				(3u)
#define TIMER0_INVERTED_PWM					(4u)
#define TIMER0_NON_INVERTED_PWM				(5u)
//TIMER0 Pre-scaler Values
#define TIMER0_PRESCALER_VALUE_DIV_BY_1			(0u)
#define TIMER0_PRESCALER_VALUE_DIV_BY_8			(1u)
#define TIMER0_PRESCALER_VALUE_DIV_BY_64		(2u)
#define TIMER0_PRESCALER_VALUE_DIV_BY_256		(3u)
#define TIMER0_PRESCALER_VALUE_DIV_BY_1024		(4u)
// Timer0 CLK source selection (Timer mode Or Counter mode)
#define TIMER0_INTERNAL_CLK_SOURCE				(0u)
#define TIMER0_EXTERNAL_CLK_SOURCE				(1u)
#define TIMER0_EXTERNAL_CLK_RISING_EDGE			(6u)
#define TIMER0_EXTERNAL_CLK_FALLING_EDGE		(5u)
/* -------------------- MACRO Functions Definitions -------------------- */

/* GENERAL NOTE: Fast PWM frequency determined by the value of pre-scaler as following *
 * Fpwm = (Fclk)/(pre-scaler_value * 256)
 * Phase Correct PWM frequency determined by the value of pre-scaler as following
 * Fpwm = (Fclk)/(scaler_value * 510)*/
/* -------------------- Data Type Declarations -------------------- */
typedef struct{
	uint8 timer0_prescaler_value			:3;		// default value is no pre-scaler
	uint8 timer0_co0_pin_state		        :3;
	uint8 timer0_general_mode				:2;

	uint8 timer0_clk_src					:1;
	uint8 timer0_edge_detect				:3;
	uint8 reserved							:4;

	uint8 tmr0_OCR_preload_value;
}timer0_t;

/* -------------------- Software Interfaces -------------------- */
/* General Interfaces */
Std_ReturnType timer0_init(const timer0_t* tmr_obj);
Std_ReturnType timer0_Deinit(const timer0_t* tmr_obj);
Std_ReturnType timer0_write_value(const timer0_t* tmr_obj, uint8 value);	// be careful in use
Std_ReturnType timer0_read_value(const timer0_t* tmr_obj, uint8* ret_value);
/* Interfaces related to compare mode */
// should read timer/counter register (TCNT0) for avoiding compare miss
Std_ReturnType timer0_generate_waveform(const timer0_t* tmr_obj, uint32 wave_freq);
/* Interfaces related to PWM mode */
Std_ReturnType timer0_pwm_duty_cycle(const timer0_t* tmr_obj, uint8 duty_cycle);
Std_ReturnType timer0_pwm_start(const timer0_t* tmr_obj);
Std_ReturnType timer0_pwm_stop();
#endif

#endif /* TIMER0_TIMER0_H_ */
