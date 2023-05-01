 /* App.c
 *
 *  Created on: Mar 13, 2023
 *      Author: ahmed
 */


#include "App.h"

Std_ReturnType ret = E_OK;

volatile uint8 g_signalCaptureFlag = 0;
volatile uint16 g_icuTimeLaps = 0;

uint16 distance;
uint8 distance_str[6] = {0};

int main(void)
{
	application_initialize();

	while(1)
	{
		distance = Ultrasonic_getDistance(g_icuTimeLaps);
		ret = LCD_convert_short_to_string(distance, &(distance_str[0]));
		ret = lcd_4bit_send_string_data_pos(&g_lcdObj_4bitMode, 2, 11, &(distance_str[0]));
	}
	return 0;
}


void application_initialize(void)
{
	ret = HAL_init();
	ret = MCAL_init();
}


void interrupt_callBackNotify(void)
{
	ret = Ultrasonic_TriggerPin(&g_ultrasonicObj);
}

void ICU_callBackNotify(void)
{
	g_signalCaptureFlag++;
	if(2 == g_signalCaptureFlag)
	{
		// take time lapse
		ret = ICU_getInputCaptureValue(&g_icuTimeLaps);
		// convert edge to detect the next measurement
		ICU_setEdgeDetectionType(ICU_RISING_EDGE_DETECT);
		g_signalCaptureFlag = 0;
	}
	else if(1 == g_signalCaptureFlag)
	{
		ICU_clearTimerValue();
		// convert edge detection to get a shot at signal falling edge
		ICU_setEdgeDetectionType(ICU_FALLING_EDGE_DETECT);
	}
}



