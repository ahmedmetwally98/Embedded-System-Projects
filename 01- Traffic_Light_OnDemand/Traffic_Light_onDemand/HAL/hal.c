/*
 * hal.c
 *
 *  Created on: Apr 11, 2023
 *      Author: ahmed
 */

//#include "hal.h"
#include "hal.h"

/* ---------------------- Global Variables Definitions --------------------- */
led_t g_ledRed = {PORT_C, GPIO_PIN0, LED_OFF, NEGATIVE_CONNECTION};
led_t g_ledYellow = {PORT_C, GPIO_PIN1, LED_OFF, NEGATIVE_CONNECTION};
led_t g_ledGreen = {PORT_C, GPIO_PIN2, LED_OFF, NEGATIVE_CONNECTION};
led_t g_ledHand = {PORT_A, GPIO_PIN0, LED_OFF, NEGATIVE_CONNECTION};
led_t g_ledPedestrian = {PORT_A, GPIO_PIN1, LED_OFF, NEGATIVE_CONNECTION};

/* ---------------------------- Function Definition -------------------------*/
Std_ReturnType HAL_initLayer(void)
{
	Std_ReturnType ret = E_NOT_OK;
	ret  = LED_initialize(&g_ledRed);
	ret &= LED_initialize(&g_ledYellow);
	ret &= LED_initialize(&g_ledGreen);
	ret &= LED_initialize(&g_ledHand);
	ret &= LED_initialize(&g_ledPedestrian);
	return ret;
}
