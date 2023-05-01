/*
 * mcal_init.h
 *
 *  Created on: Apr 24, 2023
 *      Author: ahmed
 */

#ifndef MCAL_INIT_MCAL_INIT_H_
#define MCAL_INIT_MCAL_INIT_H_

#include "ADC/adc.h"
#include "Timer0/Timer0.h"
#include "DIO_Driver/hal_DIO.h"


extern Std_ReturnType ret;
extern void ADC_callBack_notify(void);
Std_ReturnType MCAL_init(void);

#endif /* MCAL_INIT_MCAL_INIT_H_ */
