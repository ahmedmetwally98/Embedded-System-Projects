/*
 * mcal_init.c
 *
 *  Created on: Apr 24, 2023
 *      Author: ahmed
 */

#include "mcal_init.h"

const interrupt_INTx_t g_int0Obj=
{
.int_source=INT2_EXT,
.int_sense=INT2_SENSE_RISING_EDGE,
.EXT_InterruptHandler= interrupt_callBackNotify
};

const icu_ConfigType g_icuObj = {
		.icu_noiseCancel=ICU_NOISE_CANCEL_DISABLE,
		.icu_edgeSelect=ICU_RISING_EDGE_DETECT,
		.timer1Clock=F_CPU_8,
		.icu_interruptHandlerNotify=ICU_callBackNotify
};

Std_ReturnType MCAL_init(void)
{
	ret = Interrupt_INTx_Init(&g_int0Obj);
	ret = ICU_init(&g_icuObj);
	return ret;
}
