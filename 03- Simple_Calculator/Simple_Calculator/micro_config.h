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
//1MHz Clock frequency
#ifndef F_CPU
#define F_CPU 1000000UL
#endif
#include <avr/io.h>
#include <avr/interrupt.h>
#include <util/delay.h>



#define MODULE_ENABLE				(1)
#define MODULE_DISABLE				(0)

#define TIMER0_MODULE				MODULE_DISABLE
#define TIMER1_MODULE				MODULE_DISABLE
#define TIMER2_MODULE				MODULE_DISABLE

#define ADC_MODULE					MODULE_DISABLE
#define INTERRUPT_MODULE			MODULE_DISABLE
#define ICU_MODULE					MODULE_DISABLE
#define USART_MODULE				MODULE_DISABLE
#define SPI_MODULE					MODULE_DISABLE
#define I2C_MODULE					MODULE_DISABLE
#define EEPROM_MODULE				MODULE_DISABLE
#define WATCHDOG_MODULE				MODULE_DISABLE

#define LCD_MODULE					MODULE_ENABLE
#define KEYPAD_MODULE				MODULE_ENABLE
#define LED_MODULE					MODULE_DISABLE
#define EXTERNAL_EEPROM_MODULE		MODULE_DISABLE
#endif /* MICRO_CONFIG_H_ */
