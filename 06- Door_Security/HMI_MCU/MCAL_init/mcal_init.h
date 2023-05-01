/*
 * mcal_init.h
 *
 *  Created on: Apr 24, 2023
 *      Author: ahmed
 */

#ifndef MCAL_INIT_MCAL_INIT_H_
#define MCAL_INIT_MCAL_INIT_H_

#include "DIO_Driver/hal_DIO.h"
#include "Timer_16bit/hal_timer1.h"
#include "USART/usart.h"

extern Std_ReturnType ret;

extern void tmr_callBackNotify(void);

void Buzzer_turnON(void);
void Buzzer_turnOFF(void);
Std_ReturnType MCAL_init(void);

#endif /* MCAL_INIT_MCAL_INIT_H_ */
