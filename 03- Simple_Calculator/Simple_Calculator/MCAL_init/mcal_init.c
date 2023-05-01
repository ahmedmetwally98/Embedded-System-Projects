/*
 * mcal_init.c
 *
 *  Created on: Apr 24, 2023
 *      Author: ahmed
 */

#include "mcal_init.h"

interrupt_INTx_t g_int0Obj = {
		.int_source = INT0_EXT,
		.int_sense = INTx_SENSE_RISING_EDGE,
		.EXT_InterruptHandler=interrupt_callBackNotify
};

Std_ReturnType mcal_init(void)
{
	ret = Interrupt_INTx_Init(&g_int0Obj);
	return ret;
}
