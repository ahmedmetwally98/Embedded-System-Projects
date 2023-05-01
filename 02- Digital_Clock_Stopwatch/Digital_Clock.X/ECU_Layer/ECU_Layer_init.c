/* 
 * File:   ECU_Layer_init.c
 * Author: ahmed
 *
 * Created on March 1, 2023, 3:05 PM
 */

#include"ECU_Layer_init.h"

Std_ReturnType ret = E_NOT_OK;

keypad_matrix_t g_keyObj = {
    .keypad_rows_pins[0]={PORTC_INDEX,GPIO_PIN0,GPIO_DIRECTION_OUTPUT,GPIO_LOW},
    .keypad_rows_pins[1]={PORTC_INDEX,GPIO_PIN1,GPIO_DIRECTION_OUTPUT,GPIO_LOW},
    .keypad_rows_pins[2]={PORTC_INDEX,GPIO_PIN2,GPIO_DIRECTION_OUTPUT,GPIO_LOW},
    .keypad_rows_pins[3]={PORTC_INDEX,GPIO_PIN3,GPIO_DIRECTION_OUTPUT,GPIO_LOW},
    .keypad_cols_pins[0]={PORTC_INDEX,GPIO_PIN4,GPIO_DIRECTION_INPUT},
    .keypad_cols_pins[1]={PORTC_INDEX,GPIO_PIN5,GPIO_DIRECTION_INPUT},
    .keypad_cols_pins[2]={PORTC_INDEX,GPIO_PIN6,GPIO_DIRECTION_INPUT},
    .keypad_cols_pins[3]={PORTC_INDEX,GPIO_PIN7,GPIO_DIRECTION_INPUT},
};

segment_t g_segClock = {.segment_pins[SEGMENT_PIN0]={PORTA_INDEX, GPIO_PIN0, GPIO_DIRECTION_OUTPUT, GPIO_LOW},
                        .segment_pins[SEGMENT_PIN1]={PORTA_INDEX, GPIO_PIN1, GPIO_DIRECTION_OUTPUT, GPIO_LOW},
                        .segment_pins[SEGMENT_PIN2]={PORTA_INDEX, GPIO_PIN2, GPIO_DIRECTION_OUTPUT, GPIO_LOW},
                        .segment_pins[SEGMENT_PIN3]={PORTA_INDEX, GPIO_PIN3, GPIO_DIRECTION_OUTPUT, GPIO_LOW},
                        .segment_type=SEGMENT_COMMON_ANODE
                       };

 
Std_ReturnType ECU_Layer_init(void)
{
    ret = seven_segment_initialize(&g_segClock);
    ret = Keypad_init(&g_keyObj);
 
    return ret;
}
