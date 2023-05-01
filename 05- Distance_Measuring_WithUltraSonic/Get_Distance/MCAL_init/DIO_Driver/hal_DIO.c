/*
 * hal_DIO.c
 *
 *  Created on: Mar 12, 2023
 *      Author: ahmed
 */


#include "hal_DIO.h"

volatile uint8 *DDR_registers[4] = {&DDRA, &DDRB, &DDRC, &DDRD};
volatile uint8 *PORT_registers[4] = {&PORTA, &PORTB, &PORTC, &PORTD};
volatile uint8 *PIN_registers[4] = {&PINA, &PINB, &PINC, &PIND};


Std_ReturnType GPIO_pin_direction_initialize(const gpio_config_pin_t* gpio_obj)
{
	Std_ReturnType ret = E_OK;
	if (NULL == gpio_obj)
	{
		ret = E_NOT_OK;
	}
	else
	{
		ret = E_OK;
		if(gpio_obj->direction == GPIO_DIRECTION_INPUT)
		{
			CLEAR_BIT(*DDR_registers[gpio_obj->port], gpio_obj->pin);
		}
		else if(gpio_obj->direction == GPIO_DIRECTION_OUTPUT)
		{
			SET_BIT(*DDR_registers[gpio_obj->port], gpio_obj->pin);
		}
	}
	return ret;
}
Std_ReturnType GPIO_pin_initialize(const gpio_config_pin_t* gpio_obj)
{
	Std_ReturnType ret = E_OK;
		if (NULL == gpio_obj)
		{
			ret = E_NOT_OK;
		}
		else
		{
			ret = GPIO_pin_direction_initialize(gpio_obj);
			ret = GPIO_pin_write_logic(gpio_obj, gpio_obj->logic);
		}
		return ret;
}
Std_ReturnType GPIO_pin_read_direction(const gpio_config_pin_t* gpio_obj, uint8* Direction_read)
{
	Std_ReturnType ret = E_OK;
	if (NULL == gpio_obj)
	{
		ret = E_NOT_OK;
	}
	else
	{
		*Direction_read = READ_BIT(*DDR_registers[gpio_obj->port], gpio_obj->pin);
	}
	return ret;
}
Std_ReturnType GPIO_pin_write_logic(const gpio_config_pin_t* gpio_obj, uint8 logic)
{
	Std_ReturnType ret = E_OK;
	if (NULL == gpio_obj)
	{
		ret = E_NOT_OK;
	}
	else
	{
		if(logic == GPIO_HIGH)
		{
			SET_BIT(*PORT_registers[gpio_obj->port], gpio_obj->pin);
		}
		else if(logic == GPIO_LOW)
		{
			CLEAR_BIT(*PORT_registers[gpio_obj->port], gpio_obj->pin);
		}
	}
	return ret;
}
Std_ReturnType GPIO_pin_read_logic(const gpio_config_pin_t* gpio_obj, uint8* logic_res)
{
	Std_ReturnType ret = E_OK;
	if (NULL == gpio_obj)
	{
		ret = E_NOT_OK;
	}
	else
	{
		*logic_res = READ_BIT(*PIN_registers[gpio_obj->port], gpio_obj->pin);
	}
	return ret;
}
Std_ReturnType GPIO_pin_toggle_logic(const gpio_config_pin_t* gpio_obj)
{
	Std_ReturnType ret = E_OK;
	if (NULL == gpio_obj)
	{
		ret = E_NOT_OK;
	}
	else
	{
		TOGGLE_BIT(*PORT_registers[gpio_obj->port], gpio_obj->pin);
	}
	return ret;
}
Std_ReturnType GPIO_pin_PullUp_Enable(const gpio_config_pin_t* gpio_obj)
{
	Std_ReturnType ret = E_OK;
	if (NULL == gpio_obj)
	{
		ret = E_NOT_OK;
	}
	else
	{
		CLEAR_BIT(*(DDR_registers[gpio_obj->port]), gpio_obj->pin);
		SET_BIT(*(PORT_registers[gpio_obj->port]), gpio_obj->pin);
		CLEAR_BIT(SFIOR, PUD);
	}
	return ret;
}
Std_ReturnType GPIO_pin_PullUp_Disable(const gpio_config_pin_t* gpio_obj)
{
	Std_ReturnType ret = E_OK;
	if (NULL == gpio_obj)
	{
		ret = E_NOT_OK;
	}
	else
	{
		CLEAR_BIT(*PORT_registers[gpio_obj->port], gpio_obj->pin);
	}
	return ret;
}

Std_ReturnType GPIO_port_direction_initialize(gpio_port_t _port, uint8 port_direction)
{
	Std_ReturnType ret = E_OK;
	if (!(_port >= PORT_A && _port <= PORT_D))
	{
		ret = E_NOT_OK;
	}
	else
	{
		*DDR_registers[_port] = port_direction;
	}
	return ret;
}
Std_ReturnType GPIO_port_initialize(gpio_port_t _port, uint8 port_direction, uint8 port_logic)
{
	Std_ReturnType ret = E_OK;
	if (!(_port >= PORT_A && _port <= PORT_D))
	{
		ret = E_NOT_OK;
	}
	else
	{
		*DDR_registers[_port] = port_direction;
		*PORT_registers[_port] = port_logic;
	}
		return ret;
}
Std_ReturnType GPIO_port_read_direction(gpio_port_t _port, uint8* port_direction)
{
	Std_ReturnType ret = E_OK;
	if (!(_port >= PORT_A && _port <= PORT_D))
	{
		ret = E_NOT_OK;
	}
	else
	{
		*port_direction = *DDR_registers[_port];
	}
	return ret;
}
Std_ReturnType GPIO_port_write_logic(gpio_port_t _port, uint8 port_logic)
{
	Std_ReturnType ret = E_OK;
	if (!(_port >= PORT_A && _port <= PORT_D))
	{
		ret = E_NOT_OK;
	}
	else
	{
		*PORT_registers[_port] = port_logic;
	}
	return ret;
}
Std_ReturnType GPIO_port_read_logic(gpio_port_t _port, uint8* port_logic)
{
	Std_ReturnType ret = E_OK;
	if (!(_port >= PORT_A && _port <= PORT_D))
	{
		ret = E_NOT_OK;
	}
	else
	{
		*port_logic = *PIN_registers[_port];
	}
	return ret;
}
Std_ReturnType GPIO_port_toggle(gpio_port_t _port)
{
	Std_ReturnType ret = E_OK;
	if (!(_port >= PORT_A && _port <= PORT_D))
	{
		ret = E_NOT_OK;
	}
	else
	{
		*PORT_registers[_port] = *PORT_registers[_port] ^ 0xFF;
	}
	return ret;
}
Std_ReturnType GPIO_port_PullUp_Enable(gpio_port_t _port)
{
	Std_ReturnType ret = E_OK;
	if (!(_port >= PORT_A && _port <= PORT_D))
	{
		ret = E_NOT_OK;
	}
	else
	{
		*DDR_registers[_port] = *DDR_registers[_port] & 0x00;
		*PORT_registers[_port] = *PORT_registers[_port] | 0xFF;
		CLEAR_BIT(SFIOR, PUD);
	}
	return ret;
}
Std_ReturnType GPIO_port_PullUp_Disable(gpio_port_t _port)
{
	Std_ReturnType ret = E_OK;
	if (!(_port >= PORT_A && _port <= PORT_D))
	{
		ret = E_NOT_OK;
	}
	else
	{
		*PORT_registers[_port] = 0x00;
	}
	return ret;
}
