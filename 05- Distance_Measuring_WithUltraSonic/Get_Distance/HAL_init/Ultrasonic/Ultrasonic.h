/* 
 * File:   Ultrasonic.h
 */

#ifndef ULTRASONIC_H
#define	ULTRASONIC_H

#include "../../MCAL_init/DIO_Driver/hal_DIO.h"

#define SOUND_SPEED_CM_SECOND       34000

typedef struct{
	gpio_config_pin_t Trigger_Pin;
	gpio_config_pin_t Echo_Pin;
}ultrasonic_t;

Std_ReturnType Ultrasonic_Init(const ultrasonic_t *_config);
Std_ReturnType Ultrasonic_TriggerPin(const ultrasonic_t *_config);
uint16 Ultrasonic_getDistance(const uint16 a_pulseLength);

#endif	/* ULTRASONIC_H */

