/* 
 * File:   ecu_7segment.c
 * Author: ahmed
 *
 * Created on January 31, 2023, 11:08 PM
 */

#include "ecu_7segment.h"


Std_ReturnType seven_segment_initialize(const segment_t *segment_ptr)
{
    Std_ReturnType ret = E_OK;
    if (NULL == segment_ptr)
    {
        ret = E_NOT_OK;
    }
    else
    {
        ret = GPIO_pin_initialize(&(segment_ptr->segment_pins[SEGMENT_PIN0]));
        ret = GPIO_pin_initialize(&(segment_ptr->segment_pins[SEGMENT_PIN1]));
        ret = GPIO_pin_initialize(&(segment_ptr->segment_pins[SEGMENT_PIN2]));
        ret = GPIO_pin_initialize(&(segment_ptr->segment_pins[SEGMENT_PIN3]));
    }
    return ret;
}

Std_ReturnType seven_segment_write_number(const segment_t *segment_ptr, uint8 number)
{
    Std_ReturnType ret = E_OK;
    if ((NULL == segment_ptr) || (number > (uint8)9) || (number < (uint8)0))
    {
        ret = E_NOT_OK;
    }
    else
    {
        uint8 value = 0x00;
        value = ((number >> SEGMENT_PIN0) & BIT_MASK);
        ret = GPIO_pin_write_logic(&(segment_ptr->segment_pins[SEGMENT_PIN0]), value);
        value = ((number >> SEGMENT_PIN1) & BIT_MASK);
        ret = GPIO_pin_write_logic(&(segment_ptr->segment_pins[SEGMENT_PIN1]), value);
        value = ((number >> SEGMENT_PIN2) & BIT_MASK);
        ret = GPIO_pin_write_logic(&(segment_ptr->segment_pins[SEGMENT_PIN2]), value);
        value = ((number >> SEGMENT_PIN3) & BIT_MASK);
        ret = GPIO_pin_write_logic(&(segment_ptr->segment_pins[SEGMENT_PIN3]), value);
    }
    return ret;
}        

