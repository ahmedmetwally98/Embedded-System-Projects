/* 
 * File:   ECU_button.h
 * Author: ahmed
 *
 * Created on January 22, 2023, 2:22 AM
 */

#ifndef ECU_BUTTON_H
#define	ECU_BUTTON_H

/* Section : Includes */
#include "../../MCAL/DIO_Driver/hal_DIO.h"

/* Section : MACRO Declarations */
            

/* Section : MACRO Function Declarations */

/* Section : Data Type Declarations */
typedef enum 
{
	BUTTON_RELEASED,
    BUTTON_PRESSED
}button_state_t;

typedef enum
{
    PULL_DOWN,
    PULL_UP
}button_connection_t;

typedef struct
{
	gpio_config_pin_t button_pin;
    button_state_t button_state;
    button_connection_t button_connection;
}button_config_t;
        
/* Section : Functions Declarations */
Std_ReturnType BUTTON_initialize(const button_config_t *btn_config);
Std_ReturnType BUTTON_read_state(const button_config_t *btn_config, button_state_t *btn_state_ptr);

#endif	/* ECU_BUTTON_H */

