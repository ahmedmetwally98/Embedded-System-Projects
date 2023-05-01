/*
 * INT_External.h
 *
 *  Created on: Mar 16, 2023
 *      Author: ahmed
 */

#ifndef INT_EXTERNAL_H_
#define INT_EXTERNAL_H_


/* -------------------- Includes -------------------- */
#include "Interrupt_config.h"
#include "../DIO_Driver/hal_DIO.h"

#if INTERRUPT_EXTERNAL_INTx_FEATURE==INTERRUPT_FEATURE_ENABLE
/* -------------------- MACRO Definitions -------------------- */
/* INT0,1 are can be sensitive to low_leve or rising and/or falling edge detection */
#define INTx_SENSE_LOW_LEVEL		  	(0)
#define INTx_SENSE_ANY_LOGICAL_CHANGE 	(1u)
#define INTx_SENSE_FALLING_EDGE			(2u)
#define INTx_SENSE_RISING_EDGE			(3u)
/* INT2 can only sensitive to rising or falling edge detection */
#define INT2_SENSE_FALLING_EDGE			(0u)
#define INT2_SENSE_RISING_EDGE			(1u)
/* Define external interrupt sources */
#define INT0_EXT						(0u)
#define INT1_EXT						(1u)
#define INT2_EXT						(2u)

/* -------------------- MACRO Functions Definitions -------------------- */
#define INT0_ENABLE()					(SET_BIT(GICR, INT0))
#define INT1_ENABLE()					(SET_BIT(GICR, INT1))
#define INT2_ENABLE()					(SET_BIT(GICR, INT2))

#define INT0_DISABLE()					(CLEAR_BIT(GICR, INT0))
#define INT1_DISABLE()					(CLEAR_BIT(GICR, INT1))
#define INT2_DISABLE()					(CLEAR_BIT(GICR, INT2))

#define INT0_CLEAR_FLAG()				(CLEAR_BIT(GIFR, INT0))
#define INT1_CLEAR_FLAG()				(CLEAR_BIT(GIFR, INT1))
#define INT2_CLEAR_FLAG()				(CLEAR_BIT(GIFR, INT2))

#define INT0_FLAG_VALUE()				(READ_BIT(GIFR, INT0))
#define INT1_FLAG_VALUE()				(READ_BIT(GIFR, INT1))
#define INT2_FLAG_VALUE()				(READ_BIT(GIFR, INT2))

/* -------------------- Data Type Declarations -------------------- */
typedef struct{
	void (*EXT_InterruptHandler)(void);
	gpio_config_pin_t int_pin;					// to define the interrupt pin as digital input pin
	uint8 int_sense							:2;	// falling, rising, any change, low level
	uint8 int_source						:2;	// int0, int1, int2
	uint8 reserved							:4;
}interrupt_INTx_t;


/* -------------------- Software Interfaces -------------------- */
Std_ReturnType Interrupt_INTx_Init(const interrupt_INTx_t* int_obj);
Std_ReturnType Interrupt_INTx_Deinit(const interrupt_INTx_t* int_obj);
#endif

#endif /* INT_EXTERNAL_H_ */
