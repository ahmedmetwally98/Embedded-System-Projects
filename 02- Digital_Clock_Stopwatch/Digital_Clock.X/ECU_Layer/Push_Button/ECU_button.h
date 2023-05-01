/* 
 * File:   ECU_button.h
 * Author: ahmed
 *
 * Created on January 22, 2023, 2:22 AM
 */

#ifndef ECU_BUTTON_H
#define	ECU_BUTTON_H

/* Section : Includes */
#include "ECU_button_cfg.h"
#include "../../MCAL_Layer/GPIO/hal_gpio.h"

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
    BUTTON_ACTIVE_LOW,
    BUTTON_ACTIVE_HIGH
}button_connection_t;

typedef struct
{
    pin_config_t button_pin;
    button_state_t btn_state;
    button_connection_t btn_connection;
}button_config_t;
        
/* Section : Functions Declarations */
Std_ReturnType BUTTON_initialize(const button_config_t *btn_config);
Std_ReturnType BUTTON_read_state(const button_config_t *btn_config, button_state_t *btn_state_ptr);

#endif	/* ECU_BUTTON_H */

