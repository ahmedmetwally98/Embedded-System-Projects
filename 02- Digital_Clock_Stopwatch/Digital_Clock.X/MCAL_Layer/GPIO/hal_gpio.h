/* 
 * File:   hal_gpio.h
 * Author: ahmed
 *
 * Created on January 8, 2023, 4:33 PM
 */


#ifndef HAL_GPIO_H
#define	HAL_GPIO_H

/* Section : Includes */
#include "../mcal_std_types.h"
#include "../device_config.h"
#include "../std_libraries.h"
#include "hal_gpio_cfg.h"

/* Section : MACRO Declarations */
#define CPU_ARCH                    ARCH_8BIT
#define BIT_MASK                    (uint8)1
#define PORT_PIN_MAX_NUMBER         8
#define PORT_MAX_NUMBER             5
#define PORT_MASK                   0xFF

/* Section : MACRO Function Declarations */
#if (CPU_ARCH == ARCH_8BIT)
#define HWREG8(_X)          (*((volatile uint8 *)(_X)))
#elif (CPU_ARCH == ARCH_16BIT)
#define HWREG16(_X)         (*((volatile uint16 *)(_X)))
#elif (CPU_ARCH == ARCH_32BIT)
#define HWREG32 (_X)        (*((volatile uint32 *)(_X)))
#endif


/* Section : Data Type Declarations */
typedef enum {
    GPIO_LOW  = 0,
    GPIO_HIGH = 1
}logic_t;

typedef enum {
    /* to make pinx output we write 0 in the bitx of TRIS register */ 
    GPIO_DIRECTION_OUTPUT = 0, 
    /* to make pinx input we write 1 in the bitx of TRIS register */ 
    GPIO_DIRECTION_INPUT  = 1
}direction_t;

typedef enum {
    GPIO_PIN0 = 0,
    GPIO_PIN1,
    GPIO_PIN2, 
    GPIO_PIN3,
    GPIO_PIN4,
    GPIO_PIN5,
    GPIO_PIN6,
    GPIO_PIN7
}pin_index_t;

typedef enum {
    PORTA_INDEX = 0,
    PORTB_INDEX,
    PORTC_INDEX,
    PORTD_INDEX,
    PORTE_INDEX
}port_index_t;

typedef struct {
    uint8 port          : 3;    /* @ref port_index_t */
    uint8 pin           : 3;    /* @ref pin_index_t */
    uint8 direction     : 1;    /* @ref direction_t */
    uint8 logic         : 1;    /* @ref logic_t */
}pin_config_t;


/* Section : Functions Declarations */
/* 
 * in C-Function we standardizing the return to be Std_ReturnType which 
 * tell if the function is completed successfully or not.
 * if there are any value to be returned we pass a pointer to the variable to hold return value
 */
Std_ReturnType GPIO_pin_direction_initialize(const pin_config_t * _pin_config_ptr);
Std_ReturnType GPIO_pin_get_direction_status(const pin_config_t * _pin_config_ptr, direction_t *direction_status_ptr);
Std_ReturnType GPIO_pin_read_logic (const pin_config_t * _pin_config_ptr, logic_t *log_value_ptr);
Std_ReturnType GPIO_pin_write_logic (const pin_config_t * _pin_config_ptr, logic_t _logic);
Std_ReturnType GPIO_pin_toggle_logic (const pin_config_t * _pin_config_ptr);
Std_ReturnType GPIO_pin_initialize (const pin_config_t * _pin_config_ptr);

Std_ReturnType GPIO_port_direction_initialize(port_index_t _port, uint8 direction);
Std_ReturnType GPIO_port_initialize(port_index_t _port, uint8 direction, uint8 logic);
Std_ReturnType GPIO_port_get_direction_status(port_index_t _port, uint8 *direction_status);
Std_ReturnType GPIO_port_write_logic (port_index_t _port, uint8 port_logic);
Std_ReturnType GPIO_port_read_logic (port_index_t _port, uint8 *port_logic_ptr);
Std_ReturnType GPIO_port_toggle(port_index_t _port);
#endif	/* HAL_GPIO_H */

