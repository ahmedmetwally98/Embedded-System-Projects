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

#ifndef F_CPU
#define F_CPU 8000000UL
#endif
#include <avr/io.h>
#include <avr/interrupt.h>
#include <util/delay.h>
//4MHz Clock frequency


#define MODULE_ENABLE				(1)
#define MODULE_DISABLE				(0)

#define TIMER0_MODULE				MODULE_DISABLE
#define TIMER1_MODULE				MODULE_ENABLE

#define INTERRUPT_MODULE			MODULE_ENABLE
#define ICU_MODULE					MODULE_ENABLE


#define LCD_MODULE					MODULE_ENABLE

#endif /* MICRO_CONFIG_H_ */
