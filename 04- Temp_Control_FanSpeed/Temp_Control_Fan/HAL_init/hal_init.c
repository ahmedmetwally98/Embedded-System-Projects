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

const dc_motor_t g_dcMotorObj = {
		.dc_motor_pin[0] = {PORT_C, GPIO_PIN0, GPIO_DIRECTION_OUTPUT, GPIO_LOW},
		.dc_motor_pin[1] = {PORT_C, GPIO_PIN1, GPIO_DIRECTION_OUTPUT, GPIO_LOW},
};

const led_t g_ledMotorOFF = {.port_name=PORT_C, .pin=GPIO_PIN2,
		.connection_status=NEGATIVE_CONNECTION ,.led_status=LED_OFF};
const led_t g_ledMotorON = {.port_name=PORT_C, .pin=GPIO_PIN3,
		.connection_status=NEGATIVE_CONNECTION ,.led_status=LED_OFF};

Std_ReturnType HAL_init(void)
{
	ret = lcd_4bit_initialize(&g_lcdObj_4bitMode);
	ret = LED_initialize(&g_ledMotorON);
	ret = LED_initialize(&g_ledMotorOFF);
	ret = dc_motor_init(&g_dcMotorObj);
	/* display welcome message */
	ret = lcd_4bit_send_string_data(&g_lcdObj_4bitMode, "Temp. Control Fan");
	ret = lcd_4bit_send_command(&g_lcdObj_4bitMode, DDRAM_START_ADDRESS+0x40);
	ret = lcd_4bit_send_string_data(&g_lcdObj_4bitMode, "Temperature= ");
	return ret;
}
