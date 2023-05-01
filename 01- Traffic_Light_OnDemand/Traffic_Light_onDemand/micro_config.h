 /******************************************************************************
 *
 * Module: Micro - Configuration
 *
 * File Name: Micro_Config.h
 *
 * Description: File include all Microcontroller libraries
 *
 * Author: Mohamed Tarek
 *
 *******************************************************************************/

#ifndef MICRO_CONFIG_H_
#define MICRO_CONFIG_H_

//8MHz Clock frequency
#define F_CLOCK 8000000UL


#include <avr/io.h>
#include <avr/interrupt.h>

#define MODULE_ENABLE				(1)
#define MODULE_DISABLE				(0)

#define TIMER1_MODULE				MODULE_ENABLE

#define LED_MODULE					MODULE_ENABLE
#define PUSH_BUTTON_MODULE			MODULE_ENABLE
#endif /* MICRO_CONFIG_H_ */
