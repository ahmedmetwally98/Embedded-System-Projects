 /* App.c
 *
 *  Created on: Mar 13, 2023
 *      Author: ahmed
 */


#include "App.h"

Std_ReturnType ret = E_NOT_OK;
/* g_TrafficLightState global variable represents the state of the traffic light right now
 * 0 -> Red
 * 1 -> Yellow
 * 2 -> Green
 * */
uint8 g_TrafficLight = 0, Flag = 0;;
/* for controlling Counting sequence (up/down) of g_trafficLight */
volatile uint8 g_TrafficPrevState = 1;
/* g_onDemondButton global variable represents the button state.
 * 0 -> Button is not Pressed.
 * 1 -> Button is Pressed.
 * this global variable should be used to handle multi-pressings on the button.
 * */
volatile uint8 g_onDemondButton = 0;

int main(void)
{
	application_initialize();

	while(1)
	{
		if(1 == g_onDemondButton && !Flag)
		{	/* Traffic entered on Demand State */
			/* Check traffic state before take any action */
			Flag = 1;
			if(g_TrafficLight == TRAFFIC_RED_STATE)
			{
				/* No change, still in Red State*/
				timer1_delayInSeconds(REQUIRED_DELAY);
			}
			else if(g_TrafficLight == TRAFFIC_YELLOW_STATE)
			{
				/* Change state to Red state */
				g_TrafficPrevState = TRAFFIC_YELLOW_STATE;
				g_TrafficLight = TRAFFIC_RED_STATE;
				timer1_delayInSeconds(REQUIRED_DELAY);
			}
			else if(g_TrafficLight == TRAFFIC_GREEN_STATE)
			{
				/* Change state to yellow state */
				g_TrafficPrevState = TRAFFIC_GREEN_STATE;
				g_TrafficLight = TRAFFIC_YELLOW_STATE;
				timer1_delayInSeconds(REQUIRED_DELAY);
			}
		}
		if(g_TrafficLight == TRAFFIC_RED_STATE)
		{
			traffic_redAction();
		}
		else if(g_TrafficLight == TRAFFIC_YELLOW_STATE)
		{
			traffic_yellowAction();
		}
		else if(g_TrafficLight == TRAFFIC_GREEN_STATE)
		{
			traffic_greenAction();
		}
	}
	return 0;
}


void application_initialize(void)
{
	timer1_delayInSeconds(REQUIRED_DELAY);
	ret = MCAL_initLayer();
	ret &= HAL_initLayer();
}

void timer1_countEndNotify(void)
{
	/* if previous state or the current one is RED then count up */
	if(g_TrafficPrevState == TRAFFIC_RED_STATE || g_TrafficLight == TRAFFIC_RED_STATE)
	{
		g_TrafficPrevState = g_TrafficLight;
		g_TrafficLight++;
	}
	/* if previous state or the current one is GREEN then count Down */
	else if(g_TrafficPrevState == TRAFFIC_GREEN_STATE || g_TrafficLight == TRAFFIC_GREEN_STATE)
	{
		g_TrafficPrevState = g_TrafficLight;
		g_TrafficLight--;
	}
	if(g_TrafficPrevState == TRAFFIC_RED_STATE)
	{
		g_onDemondButton = 0;
		Flag = 0;
	}
	timer1_delayInSeconds(REQUIRED_DELAY);
}

void int1_eventOccurNotify(void)
{
	if (0 == g_onDemondButton)
	{
		/* go to On Demand State */
		g_onDemondButton= 1;
	}
}

void traffic_redAction(void)
{
	ret = LED_turn_on(&g_ledRed);
	ret = LED_turn_on(&g_ledPedestrian);
	ret = LED_turn_off(&g_ledYellow);
	ret = LED_turn_off(&g_ledHand);
	ret = LED_turn_off(&g_ledGreen);
}
void traffic_greenAction(void)
{
	ret = LED_turn_on(&g_ledGreen);
	ret = LED_turn_on(&g_ledHand);
	ret = LED_turn_off(&g_ledYellow);
	ret = LED_turn_off(&g_ledRed);
	ret = LED_turn_off(&g_ledPedestrian);
}
void traffic_yellowAction(void)
{
	ret = LED_turn_on(&g_ledYellow);
	ret = LED_turn_on(&g_ledHand);
	ret = LED_turn_off(&g_ledRed);
	ret = LED_turn_off(&g_ledGreen);
	ret = LED_turn_off(&g_ledPedestrian);
}





