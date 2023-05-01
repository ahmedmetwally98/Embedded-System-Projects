/*
 * hal_init.h
 *
 *  Created on: Apr 24, 2023
 *      Author: ahmed
 */

#ifndef HAL_INIT_HAL_INIT_H_
#define HAL_INIT_HAL_INIT_H_

#include "External_EEPROM/external_eeprom.h"
#include "motor/ecu_motor.h"

extern Std_ReturnType ret;
Std_ReturnType HAL_init(void);


#endif /* HAL_INIT_HAL_INIT_H_ */
