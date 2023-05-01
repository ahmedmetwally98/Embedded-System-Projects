/* 
 * File:   App.c
 * Author: ahmed
 *
 * Created on April 23, 2023, 6:45 PM
 */

#include "App.h"

uint8 clk_hours=ZERO_INIT, clk_minutes=ZERO_INIT, clk_seconds=ZERO_INIT;
uint8 tmr1_flag = ZERO_INIT;
        
uint8 w_hours=ZERO_INIT, w_minutes=ZERO_INIT, w_seconds=ZERO_INIT;
uint8 tmr3_flag=ZERO_INIT;

volatile uint8 value=0;
volatile uint8 program = DIGITAL_CLOCK_PROGRAM;

Std_ReturnType ret = E_OK;
int main(void)
{
    application_init();
    while(1)
    {
        if(DIGITAL_CLOCK_PROGRAM == program)
        {
            Display_clock(clk_hours, clk_minutes, clk_seconds);
        }
        else if(STOPWATCH_PROGRAM == program)
        {
            Display_clock(w_hours, w_minutes, w_seconds);
        }
    }
    
    return 0;
}
Std_ReturnType application_init(void)
{
    ret = ECU_Layer_init();
    ret = MCAL_Layer_init();
    return ret;
}
void tmr1_callBackNotify(void)
{
    tmr1_flag++;
    if(4 == tmr1_flag)
    {
        clk_seconds++;
        if(clk_seconds > 59)
        {
            clk_minutes++;
            clk_seconds = 0;
        }
        if(clk_minutes > 59)
        {
            clk_hours++;
            clk_minutes = 0;
        }
        if(clk_hours > 23)
        {
            clk_hours = 0;
        }
        tmr1_flag=0;
    }
}
void tmr3_callBackNotify(void)
{
    tmr3_flag++;
    if(4 == tmr3_flag)
    {
        w_seconds++;
        if(w_seconds > 59)
        {
            w_minutes++;
            w_seconds=0;
        }
        if(w_minutes > 59)
        {
            w_hours++;
            w_minutes=0;
        }
        if(w_hours > 23)
        {
            w_hours = 0;
        }
        tmr3_flag=0;
    }
}
void interrupt1_callBackNotify_changeProgram(void)
{
    // change the program
    program = !program;
    if(DIGITAL_CLOCK_PROGRAM == program)
    {
        Timer3_DeInit(&g_tmr3Obj);
        w_seconds = 0;
        w_minutes = 0;
        w_hours   = 0;
    }
    else if(STOPWATCH_PROGRAM == program)
    {
        Timer3_Init(&g_tmr3Obj);
    }
}

void interrupt2_callBackNotify_changeClock(void)
{
    Timer1_DeInit(&g_tmr1Obj);
    uint8 temp = clk_hours;
    ret = GPIO_port_write_logic(PORTD_INDEX, 0b00100000);
    ret = GPIO_port_write_logic(PORTA_INDEX, (uint8)(clk_hours/10));
    // getting hours value in tens position
    value='\0';
    do{
        ret = Keypad_getValue(&g_keyObj, &value);
        if(value == '=')
        {    // return without changing time
            return;
        }
    }while(value == '\0' || !(value >= '0' && value <= '2'));  
    clk_hours = value-48;
    
    ret = GPIO_port_write_logic(PORTA_INDEX, (uint8)clk_hours);
    __delay_ms(250);
    ret = GPIO_port_write_logic(PORTD_INDEX, 0b00010000);
    ret = GPIO_port_write_logic(PORTA_INDEX, (uint8)(temp%10));
    // getting hours value in ones position
    value = '\0';
    do{
        ret = Keypad_getValue(&g_keyObj, &value);
        if(value == '=')
        {    // return without changing time
            clk_hours = temp;
            return;
        }
    }while(value == '\0' || !(value>='0' && value <= '9'));
    clk_hours = clk_hours*10 + (value-48); 
    
    ret = GPIO_port_write_logic(PORTA_INDEX, (uint8)(clk_hours%10));
    __delay_ms(250);
    
    // getting minutes value in tens position
    ret = GPIO_port_write_logic(PORTD_INDEX, 0b00001000);
    ret = GPIO_port_write_logic(PORTA_INDEX, (uint8)(clk_minutes/10));
    temp = clk_minutes;
    value='\0';
    do{
        ret = Keypad_getValue(&g_keyObj, &value);
        if(value == '=')
        {    // return without changing time
            return;
        }
    }while(value == '\0' || !(value >= '0' && value <= '5'));  
    clk_minutes = value-48;
    
    ret = GPIO_port_write_logic(PORTC_INDEX, (uint8)clk_minutes);
    __delay_ms(250);
    ret = GPIO_port_write_logic(PORTD_INDEX, 0b00000100);
    ret = GPIO_port_write_logic(PORTA_INDEX, (uint8)(temp%10));
    // getting minutes value in ones position
    value = '\0';
    do{
        ret = Keypad_getValue(&g_keyObj, &value);
        if(value == '=')
        {    // return without changing time
            clk_minutes = temp;
            return;
        }
    }while(value == '\0' || !(value>='0' && value <= '9'));
    clk_minutes = clk_minutes*10 + (value-48); 
    
    ret = GPIO_port_write_logic(PORTA_INDEX, (uint8)(clk_minutes%10));
    ret = GPIO_port_write_logic(PORTC_INDEX, 0x00);
    __delay_ms(250);
    Timer1_Init(&g_tmr1Obj);
}

void Display_clock(uint8 hr, uint8 min, uint8 sec)
{
    ret = GPIO_port_write_logic(PORTD_INDEX, 0b00000010);
    ret = GPIO_port_write_logic(PORTA_INDEX, (uint8)(sec/10));
    __delay_ms(3);
    ret = GPIO_port_write_logic(PORTD_INDEX, 0b00000001);
    ret = GPIO_port_write_logic(PORTA_INDEX, (uint8)(sec%10));
    __delay_ms(3);
    ret = GPIO_port_write_logic(PORTD_INDEX, 0b00001000);
    ret = GPIO_port_write_logic(PORTA_INDEX, (uint8)(min/10));
    __delay_ms(3);
    ret = GPIO_port_write_logic(PORTD_INDEX, 0b00000100);
    ret = GPIO_port_write_logic(PORTA_INDEX, (uint8)(min%10));
    __delay_ms(3);
    ret = GPIO_port_write_logic(PORTD_INDEX, 0b00100000);   
    ret = GPIO_port_write_logic(PORTA_INDEX, (uint8)(hr/10));
    __delay_ms(3);
    ret = GPIO_port_write_logic(PORTD_INDEX, 0b00010000);
    ret = GPIO_port_write_logic(PORTA_INDEX, (uint8)(hr%10));
    __delay_ms(3);
}

void reset_stopWatch(uint8 flag)
{
    if(flag == 0)
    {
        ret = Timer3_DeInit(&g_tmr3Obj);
        w_hours = 0;
        w_minutes = 0;
        w_seconds = 0;
        ret = Timer3_Init(&g_tmr3Obj);
    }
    
}
void stop_stopWatch(uint8 flag)
{
    if(flag == 0)
    {
        ret = Timer3_DeInit(&g_tmr3Obj);
    }
}
void resume_stopWatch(uint8 flag)
{
    if(flag == 0)
    {
        ret = Timer3_Init(&g_tmr3Obj);
    }
}