/*
 * mcal.c
 *
 *  Created on: Apr 11, 2023
 *      Author: ahmed
 */


#include "mcal.h"

/* ---------------------- Global Variables Definitions --------------------- */
timer1_t g_tmr1Obj = {
		.tmr1_interruptHanlderNotify=timer1_countEndNotify,
		.timer1_prescaler_value=TIMER1_PRESCALER_VALUE_DIV_BY_1024,
		.timer1_general_mode=TIMER1_NORMAL_MODE,
		.timer1_clk_src=TIMER1_INTERNAL_CLK_SOURCE
};

/* Interrupt sensing on Rising edge. (Pull-Down resistor connection) */
interrupt_INTx_t g_int1Obj = {
		.EXT_InterruptHandler=int1_eventOccurNotify,
		.int_source=INT1_EXT,
		.int_sense=INTx_SENSE_RISING_EDGE,
};

/* ---------------------------- Function Definition -------------------------*/

Std_ReturnType MCAL_initLayer(void)
{
	Std_ReturnType ret = E_NOT_OK;
	ret = timer1_init(&g_tmr1Obj);
	ret &= Interrupt_INTx_Init(&g_int1Obj);

	return ret;
}
