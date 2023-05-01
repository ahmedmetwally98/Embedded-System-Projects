/*
 * mcal_init.h
 *
 *  Created on: Apr 24, 2023
 *      Author: ahmed
 */

#ifndef MCAL_INIT_MCAL_INIT_H_
#define MCAL_INIT_MCAL_INIT_H_


#include "ICU/icu.h"
#include "DIO_Driver/hal_DIO.h"
#include "Interrupt_Driver/INT_External.h"

extern Std_ReturnType ret;

extern void interrupt_callBackNotify(void);
extern void ICU_callBackNotify(void);
Std_ReturnType MCAL_init(void);

#endif /* MCAL_INIT_MCAL_INIT_H_ */
