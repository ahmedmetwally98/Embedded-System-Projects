/*
 * hal_init.c
 *
 *  Created on: Apr 24, 2023
 *      Author: ahmed
 */

#include "hal_init.h"

/* ---------------------- Global variables ----------------------- */

const char_lcd_t g_lcdObj_4bitMode = {
	    .RS_pin={PORT_D, GPIO_PIN0, GPIO_DIRECTION_OUTPUT, GPIO_LOW},
	    .E_pin={PORT_D, GPIO_PIN1, GPIO_DIRECTION_OUTPUT, GPIO_LOW},
	    .lcd_data_pins[0]={PORT_D, GPIO_PIN2, GPIO_DIRECTION_OUTPUT, GPIO_LOW},
	    .lcd_data_pins[1]={PORT_D, GPIO_PIN3, GPIO_DIRECTION_OUTPUT, GPIO_LOW},
	    .lcd_data_pins[2]={PORT_D, GPIO_PIN4, GPIO_DIRECTION_OUTPUT, GPIO_LOW},
	    .lcd_data_pins[3]={PORT_D, GPIO_PIN5, GPIO_DIRECTION_OUTPUT, GPIO_LOW},
};

const ultrasonic_t g_ultrasonicObj = {
		.Trigger_Pin={PORT_C, GPIO_PIN0, GPIO_DIRECTION_OUTPUT, GPIO_LOW},
		.Echo_Pin={PORT_C, GPIO_PIN1, GPIO_DIRECTION_INPUT}
};

Std_ReturnType HAL_init(void)
{
	ret = lcd_4bit_initialize(&g_lcdObj_4bitMode);
	ret = Ultrasonic_Init(&g_ultrasonicObj);

	/* display welcome message */
	ret = lcd_4bit_send_string_data(&g_lcdObj_4bitMode, "Distance Measurement");
	// move cursor to start from second line
	ret = lcd_4bit_send_command(&g_lcdObj_4bitMode, DDRAM_START_ADDRESS+ROW2_OFFSET);
	ret = lcd_4bit_send_string_data(&g_lcdObj_4bitMode, "Distance= ");
	return ret;
}
