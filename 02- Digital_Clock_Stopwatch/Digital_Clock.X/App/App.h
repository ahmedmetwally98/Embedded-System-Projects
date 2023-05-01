/* 
 * File:   App.h
 * Author: ahmed
 *
 * Created on April 23, 2023, 6:45 PM
 */

#ifndef APP_H
#define	APP_H

#include "../MCAL_Layer/MCAL_Layer_init.h"
#include "../ECU_Layer/ECU_Layer_init.h"

#define DIGITAL_CLOCK_PROGRAM       0
#define STOPWATCH_PROGRAM           1

extern timer3_config_t g_tmr3Obj;
extern timer1_config_t g_tmr1Obj;
extern button_config_t g_resetButtonObj;
extern button_config_t g_stopButtonObj;
extern button_config_t g_resumeButtonObj;
extern keypad_matrix_t g_keyObj;
void tmr1_callBackNotify(void);
void tmr3_callBackNotify(void);
void interrupt1_callBackNotify_changeProgram(void);
void interrupt2_callBackNotify(void);

void reset_stopWatch(uint8);
void stop_stopWatch(uint8);
void resume_stopWatch(uint8);

void ChangeClock(void);
void Display_clock(uint8, uint8, uint8);

Std_ReturnType application_init(void);
#endif	/* APP_H */

