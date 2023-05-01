/*
 * hal_DIO.h
 *
 *  Created on: Mar 12, 2023
 *      Author: ahmed
 */

#ifndef HAL_DIO_H_
#define HAL_DIO_H_

/* -------------------- Includes -------------------- */
#include "../../micro_config.h"
#include "../../std_types.h"
#include "../../common_macros.h"

/* -------------------- MACRO Definitions -------------------- */
#define GPIO_LOW					0x00
#define GPIO_HIGH					0x01U
#define GPIO_DIRECTION_INPUT		0x00
#define GPIO_DIRECTION_OUTPUT		0x01U

#define PORT_GPIO_HIGH				0xFFU
#define PORT_GPIO_LOW				0x00
#define PORT_DIRECTION_OUTPUT		0xFFU
#define PORT_DIRECTION_INPUT		0x00


/* -------------------- MACRO Functions Definitions -------------------- */


/* -------------------- Data Type Declarations -------------------- */
typedef enum{
	GPIO_PIN0 = 0,
	GPIO_PIN1,
	GPIO_PIN2,
	GPIO_PIN3,
	GPIO_PIN4,
	GPIO_PIN5,
	GPIO_PIN6,
	GPIO_PIN7
}gpio_pin_t;

typedef enum{
	PORT_A,
	PORT_B,
	PORT_C,
	PORT_D
}gpio_port_t;

typedef struct{
	uint8 port			:3;
	uint8 pin			:3;
	uint8 direction		:1;
	uint8 logic			:1;
}gpio_config_pin_t;

/* -------------------- Software Interfaces -------------------- */
Std_ReturnType GPIO_pin_direction_initialize(const gpio_config_pin_t*);
Std_ReturnType GPIO_pin_initialize(const gpio_config_pin_t*);
Std_ReturnType GPIO_pin_read_direction(const gpio_config_pin_t*, uint8* Direction_read);
Std_ReturnType GPIO_pin_write_logic(const gpio_config_pin_t*, uint8 logic);
Std_ReturnType GPIO_pin_read_logic(const gpio_config_pin_t*, uint8* logic_res);
Std_ReturnType GPIO_pin_toggle_logic(const gpio_config_pin_t*);
Std_ReturnType GPIO_pin_PullUp_Enable(const gpio_config_pin_t*);
Std_ReturnType GPIO_pin_PullUp_Disable(const gpio_config_pin_t*);

Std_ReturnType GPIO_port_direction_initialize(gpio_port_t _port, uint8 port_direction);
Std_ReturnType GPIO_port_initialize(gpio_port_t _port, uint8 port_direction, uint8 port_logic);
Std_ReturnType GPIO_port_read_direction(gpio_port_t _port, uint8* port_direction);
Std_ReturnType GPIO_port_write_logic(gpio_port_t _port, uint8 port_logic);
Std_ReturnType GPIO_port_read_logic(gpio_port_t _port, uint8* port_logic);
Std_ReturnType GPIO_port_toggle(gpio_port_t _port);
Std_ReturnType GPIO_port_PullUp_Enable(gpio_port_t _port);
Std_ReturnType GPIO_port_PullUp_Disable(gpio_port_t _port);


#endif /* HAL_DIO_H_ */
