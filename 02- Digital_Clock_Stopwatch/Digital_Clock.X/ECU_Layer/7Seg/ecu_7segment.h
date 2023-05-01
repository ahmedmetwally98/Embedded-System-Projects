/* 
 * File:   ecu_7segment.h
 * Author: ahmed
 *
 * Created on January 31, 2023, 11:08 PM
 */

#ifndef ECU_7SEGMENT_H
#define	ECU_7SEGMENT_H

/* Section : Includes */
#include "../../MCAL_Layer/GPIO/hal_gpio.h"
#include "ecu_7segment_cfg.h"

/* Section : MACRO Declarations */
#define SEGMENT_PIN0    (uint8)0
#define SEGMENT_PIN1    (uint8)1
#define SEGMENT_PIN2    (uint8)2
#define SEGMENT_PIN3    (uint8)3

/* Section : MACRO Function Declarations */

/* Section : Data Type Declarations */
typedef enum
{
    SEGMENT_COMMON_CATHOD,
    SEGMENT_COMMON_ANODE        
}segment_type_t;

typedef struct
{
    pin_config_t segment_pins[4];
    segment_type_t segment_type;
}segment_t;
/* Section : Functions Declarations */
Std_ReturnType seven_segment_initialize(const segment_t *segment_ptr);
Std_ReturnType seven_segment_write_number(const segment_t *segment_ptr, uint8 number);

#endif	/* ECU_7SEGMENT_H */

