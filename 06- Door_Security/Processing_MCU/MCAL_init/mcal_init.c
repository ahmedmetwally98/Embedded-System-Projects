/*
 * mcal_init.c
 *
 *  Created on: Apr 24, 2023
 *      Author: ahmed
 */

#include "mcal_init.h"



const gpio_config_pin_t g_buzzerObj = {PORT_D, GPIO_PIN7, GPIO_DIRECTION_OUTPUT, GPIO_LOW};

const timer1_t g_tmr1Obj = {
		.timer1_general_mode=TIMER1_NORMAL_MODE,
		.timer1_prescaler_value=TIMER1_PRESCALER_VALUE_DIV_BY_256,
		.timer1_clk_src=TIMER1_INTERNAL_CLK_SOURCE,
		.tmr1_IRQHandller_OVF=tmr_callBackNotify
};


usart_t g_uartObj2 = {
		.usart_tx_enable=USART_TX_ENABLE,
		.usart_rx_enable=USART_RX_ENABLE,
		.usart_mode=USART_ASYNC_NORMAL_SPEED_MODE,
		.baudrate=19200,
		.usart_parity=USART_PARITY_DISABLE,
		.usart_character_size=8,
};

Std_ReturnType MCAL_init(void)
{
	ret = GPIO_pin_initialize(&g_buzzerObj);
	ret = USART_Init(&g_uartObj2);
	return ret;
}

void Buzzer_turnON(void)
{
	ret = GPIO_pin_write_logic(&g_buzzerObj, GPIO_HIGH);
}

void Buzzer_turnOFF(void)
{
	ret = GPIO_pin_write_logic(&g_buzzerObj, GPIO_LOW);
}
