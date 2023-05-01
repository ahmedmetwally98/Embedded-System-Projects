/*
 * App.h
 *
 *  Created on: Mar 14, 2023
 *      Author: ahmed
 */

#ifndef APP_H_
#define APP_H_

#include "../HAL_init/hal_init.h"
#include "../MCAL_init/mcal_init.h"

#define INVALID_OPERATION			1
#define INVALID_NUM_LEN				2


extern char_lcd_t g_lcdObj_4bitMode;
extern keypad_matrix_t g_keypadObj;
extern Std_ReturnType ret;
/* ------------------- Application Functions Declarations ----------------------*/
void application_initialize(void);
// used to clear screen to get next operation
void interrupt_callBackNotify(void);

void get_operand(uint8 key_val);
void get_operation(uint8 key_val);
Std_ReturnType check_operation(void);
uint32 get_result(uint32 op1, uint32 op2, uint8 operation);
void show_operation_result(const uint8* str);
void show_error_msg(void);
void reset_values(void);

#endif /* APP_H_ */
