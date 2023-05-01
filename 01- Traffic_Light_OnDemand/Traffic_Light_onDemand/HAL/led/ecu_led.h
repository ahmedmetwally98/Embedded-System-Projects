/* 
 * File:   ecu_led.h
 * Author: ahmed
 *
 * Created on January 8, 2023, 10:40 PM
 */

#ifndef ECU_LED_H
#define	ECU_LED_H

/* Section : Includes */
#include "../../MCAL/DIO_Driver/hal_DIO.h"

#if LED_MODULE == MODULE_ENABLE
/* Section : MACRO Declarations */
#define POSITIVE_CONNECTION			0x01U
#define NEGATIVE_CONNECTION			0x00U
/* Section : MACRO Function Declarations */

/* Section : Data Type Declarations */
typedef enum
{
    LED_OFF,
    LED_ON
}led_status_t;

typedef struct
{
    uint8 port_name         : 3;
    uint8 pin               : 3;
    uint8 led_status        : 1;     /* 1 represents Led_ON and 0 for Led_OFF */
    uint8 connection_status : 1;     /* 1 represents Positive connection and 0 for negative connection*/
}led_t;

/* Section : Functions Declarations */

Std_ReturnType LED_initialize (const led_t *led);
Std_ReturnType LED_turn_on (const led_t *led);
Std_ReturnType LED_turn_off (const led_t *led);
Std_ReturnType LED_turn_toggle (const led_t *led);
#endif

#endif	/* ECU_LED_H */

