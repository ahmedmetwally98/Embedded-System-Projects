/*
 * mcal_init.h
 *
 *  Created on: Apr 24, 2023
 *      Author: ahmed
 */

#ifndef MCAL_INIT_MCAL_INIT_H_
#define MCAL_INIT_MCAL_INIT_H_

#include "Interrupt_Driver/INT_External.h"


extern Std_ReturnType ret;

extern void interrupt_callBackNotify(void);
Std_ReturnType mcal_init(void);

#endif /* MCAL_INIT_MCAL_INIT_H_ */
