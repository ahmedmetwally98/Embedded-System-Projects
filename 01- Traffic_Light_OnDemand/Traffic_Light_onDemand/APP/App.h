/*
 * App.h
 *
 *  Created on: Mar 14, 2023
 *      Author: ahmed
 */

#ifndef APP_H_
#define APP_H_

#include "../MCAL/mcal.h"
#include "../HAL/hal.h"

/* ---------------------------- Global Variabl --------------------------------*/
extern led_t g_ledRed;
extern led_t g_ledYellow;
extern led_t g_ledGreen;
extern led_t g_ledHand;
extern led_t g_ledPedestrian;
/* Required Delay should not exceed 8 second for working properly */
#define REQUIRED_DELAY				(5u)

#define TRAFFIC_RED_STATE			(0)
#define TRAFFIC_YELLOW_STATE		(1u)
#define TRAFFIC_GREEN_STATE			(2u)
/* ------------------- Application Functions Declarations ----------------------*/
void application_initialize(void);

void timer1_countEndNotify(void);
void int1_eventOccurNotify(void);

void traffic_redAction(void);
void traffic_greenAction(void);
void traffic_yellowAction(void);

#endif /* APP_H_ */
