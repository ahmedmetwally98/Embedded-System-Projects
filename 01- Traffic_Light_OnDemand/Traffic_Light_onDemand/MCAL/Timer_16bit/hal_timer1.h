/*
 * hal_timer1.h
 *
 *  Created on: Mar 25, 2023
 *      Author: ahmed
 */

#ifndef TIMER_16BIT_HAL_TIMER1_H_
#define TIMER_16BIT_HAL_TIMER1_H_


/* -------------------- Includes -------------------- */
#include "../Interrupt_Driver/INT_Internal.h"

#if TIMER1_MODULE == MODULE_ENABLE
/* -------------------- MACRO Definitions -------------------- */
#define TIMER1_FIXED_TOP_VALUE_1					(0xFF)
#define TIMER1_FIXED_TOP_VALUE_2					(0x1FF)
#define TIMER1_FIXED_TOP_VALUE_3					(0x3FF)

#define OC1A_PIN									(0)
#define OC1B_PIN									(1)
#define OC1A_OC1B_PINs								(2)
/* Timer1 General modes START */
#define TIMER1_NORMAL_MODE							(0)
#define TIMER1_CLEAR_TIMER_COMPARE_ICR1_MODE		(4u)
#define TIMER1_CLEAR_TIMER_COMPARE_OCR1A_MODE		(12u)
/* Timer1 Fast PWM modes */
#define TIMER1_FAST_PWM_TOP_FIXED_FF_MODE			(5u)
#define TIMER1_FAST_PWM_TOP_FIXED_1FF_MODE			(6u)
#define TIMER1_FAST_PWM_TOP_FIXED_3FF_MODE			(7u)
#define TIMER1_FAST_PWM_TOP_ICR_MODE				(14u)
#define TIMER1_FAST_PWM_TOP_OCR1A_MODE				(15u)
/* Timer1 Phase Correct PWM modes */
#define TIMER1_PC_PWM_TOP_FIXED_FF_MODE				(1u)
#define TIMER1_PC_PWM_TOP_FIXED_1FF_MODE			(2u)
#define TIMER1_PC_PWM_TOP_FIXED_3FF_MODE			(3u)
#define TIMER1_PC_PWM_TOP_ICR_MODE					(10u)
#define TIMER1_PC_PWM_TOP_OCR1A_MODE				(11u)
/* Timer1 Phase and Frequency Correct PWM modes */
#define TIMER1_PFC_PWM_TOP_ICR_MODE 				(8u)
#define TIMER1_PFC_PWM_TOP_OCR1A_MODE				(9u)
/* Timer1 General modes END */

// choose OC0 pin action
#define TIMER1_CTC_PIN_DISCONNECTED					(0u)
#define TIMER1_CTC_SET_PIN							(1u)
#define TIMER1_CTC_CLEAR_PIN						(2u)
#define TIMER1_CTC_TOGGLE_PIN						(3u)
#define TIMER1_INVERTED_PWM							(4u)
#define TIMER1_NON_INVERTED_PWM						(5u)
#define TIMER1_TOGGLE_OC1A_PWM						(6u)

//TIMER1 Pre-scaler Values
#define TIMER1_PRESCALER_VALUE_DIV_BY_1			(0u)
#define TIMER1_PRESCALER_VALUE_DIV_BY_8			(1u)
#define TIMER1_PRESCALER_VALUE_DIV_BY_64		(2u)
#define TIMER1_PRESCALER_VALUE_DIV_BY_256		(3u)
#define TIMER1_PRESCALER_VALUE_DIV_BY_1024		(4u)
// Timer1 CLK source selection (Timer mode Or Counter mode)
#define TIMER1_INTERNAL_CLK_SOURCE				(0u)
#define TIMER1_EXTERNAL_CLK_SOURCE				(1u)
#define TIMER1_EXTERNAL_CLK_RISING_EDGE			(1u)
#define TIMER1_EXTERNAL_CLK_FALLING_EDGE		(0u)

/* -------------------- MACRO Functions Definitions -------------------- */
#define TIMER1_MODULE_DISABLE()				{TCCR1B &= 0xF8;}

/* -------------------- Data Type Declarations -------------------- */
typedef struct{
	void (*tmr1_interruptHanlderNotify) (void);		// Call back function
	uint8 timer1_general_mode;						// default mode is normal mode
	uint8 timer1_clk_src					:1;		// default is internal clock source (no pre-scaler)
	uint8 timer1_prescaler_value			:3;		// default value is no pre-scaler
	uint8 timer1_edge_detect				:1;		// default is Rising edge detection
	uint8									:3;
}timer1_t;

/* -------------------- Software Interfaces -------------------- */
Std_ReturnType timer1_init(const timer1_t* tmr_obj);
Std_ReturnType timer1_Deinit(const timer1_t* tmr_obj);
Std_ReturnType timer1_write_counter_value(const uint16 value);	// be careful in use
Std_ReturnType timer1_read_counter_value(uint16* ret_value);
void timer1_delayInSeconds(uint8 a_delaySecond);
#endif

#endif /* TIMER_16BIT_HAL_TIMER1_H_ */
