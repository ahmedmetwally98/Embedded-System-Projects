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

/*------------------- Global Variables ------------------------*/

extern const timer1_t g_tmr1Obj;
extern usart_t g_uartObj1;
extern const char_lcd_t g_lcdObj_4bitMode;
extern const keypad_matrix_t g_keypadObj;


/* ------------------- Application Functions Declarations ----------------------*/
void application_initialize(void);

void tmr_callBackNotify(void);
void display_options(void);
void display_alarm_msg(void);
void display_door_msg(void);
void get_new_password(void);
void get_password_from_user(void);

void door_option_handler(void);
void chnage_password_option_handler(void);
void invalid_password_handler(void);

#endif /* APP_H_ */
