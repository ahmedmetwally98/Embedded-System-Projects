/*
 * hal_init.c
 *
 *  Created on: Apr 24, 2023
 *      Author: ahmed
 */

#include "hal_init.h"

/* ---------------------- Global variables ----------------------- */

const dc_motor_t g_dcMotorObj = {
		.dc_motor_pin[DC_MOTOR_PIN1]={PORT_D, GPIO_PIN4, GPIO_DIRECTION_OUTPUT, GPIO_LOW},
		.dc_motor_pin[DC_MOTOR_PIN2]={PORT_D, GPIO_PIN5, GPIO_DIRECTION_OUTPUT, GPIO_LOW}
};

Std_ReturnType HAL_init(void)
{
	ret = dc_motor_init(&g_dcMotorObj);
	return ret;
}
