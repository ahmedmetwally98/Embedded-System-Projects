/* 
 * File:   hal_gpio.c
 * Author: ahmed
 *
 * Created on January 8, 2023, 4:26 PM
 */

#include "hal_gpio.h"

/* Reference to the Data Direction Control Registers */
volatile uint8 *TRIS_Registers[] = {&TRISA, &TRISB, &TRISC, &TRISD, &TRISE};
/* Reference to the Data Latch Registers (Read and Write to data Latch) */
volatile uint8 *LAT_Registers [] = {&LATA, &LATB, &LATC, &LATD, &LATE};
/* Reference to the Port Status Registers */
volatile uint8 *PORT_Registers[] = {&PORTA, &PORTB, &PORTC, &PORTD, &PORTE};


#if GPIO_PORT_PIN_CONFIGURATIONS == CONFIG_ENABLE
/**
 * @brief Initialize the direction of a specific pin @ref direction_t
 * @param _pin_config_ptr
 * @return Status of the Function
 *          E_OK     : The Function done successfully
 *          E_NOT_OK : The Function has issue to perform this task
 */
Std_ReturnType GPIO_pin_direction_initialize(const pin_config_t *_pin_config_ptr)
{
    Std_ReturnType ret = E_OK;
    if (NULL == _pin_config_ptr || _pin_config_ptr->pin > PORT_PIN_MAX_NUMBER-1
            || _pin_config_ptr->port > PORT_MAX_NUMBER-1)
    {
        ret = E_NOT_OK;
    }
    else
    {
        switch(_pin_config_ptr->direction)
        {
            case GPIO_DIRECTION_OUTPUT : 
                CLEAR_BIT(*TRIS_Registers[_pin_config_ptr->port], _pin_config_ptr->pin);
                break;
            case GPIO_DIRECTION_INPUT  :
                SET_BIT(*TRIS_Registers[_pin_config_ptr->port], _pin_config_ptr->pin);
                break;
            default :
                ret = E_NOT_OK;
                break;
        }
    }
    return ret;
}
#endif


#if GPIO_PORT_PIN_CONFIGURATIONS == CONFIG_ENABLE
/**
 * @param _pin_config_ptr
 * @param direction_status_ptr
 * @return Status of the Function
 *          E_OK     : The Function done successfully
 *          E_NOT_OK : The Function has issue to perform this task
 */
Std_ReturnType GPIO_pin_get_direction_status(const pin_config_t *_pin_config_ptr, direction_t *direction_status_ptr)
{
    Std_ReturnType ret = E_OK;
    if (NULL == _pin_config_ptr || NULL == direction_status_ptr || _pin_config_ptr->pin > PORT_PIN_MAX_NUMBER-1
            || _pin_config_ptr->port > PORT_MAX_NUMBER-1)
    {
        ret = E_NOT_OK;
    }
    else
    {
        *direction_status_ptr = READ_BIT(*TRIS_Registers[_pin_config_ptr->port], _pin_config_ptr->pin);    
    }
    return ret;
}
#endif


#if GPIO_PORT_PIN_CONFIGURATIONS == CONFIG_ENABLE
/**
 * @param _pin_config_ptr
 * @param log_value_ptr
 * @return Status of the Function
 *          E_OK     : The Function done successfully
 *          E_NOT_OK : The Function has issue to perform this task
 */
Std_ReturnType GPIO_pin_read_logic (const pin_config_t *_pin_config_ptr, logic_t *log_value_ptr)
{
    Std_ReturnType ret = E_OK;
    if (NULL == _pin_config_ptr || NULL == log_value_ptr || _pin_config_ptr->pin > PORT_PIN_MAX_NUMBER-1
            || _pin_config_ptr->port > PORT_MAX_NUMBER-1)
    {
        ret = E_NOT_OK;
    }
    else
    {
        *log_value_ptr = READ_BIT(*PORT_Registers[_pin_config_ptr->port], _pin_config_ptr->pin);
    }
    return ret;
}
#endif


#if GPIO_PORT_PIN_CONFIGURATIONS == CONFIG_ENABLE
/**
 * @param _pin_config_ptr
 * @param log_value
 * @return Status of the Function
 *          E_OK     : The Function done successfully
 *          E_NOT_OK : The Function has issue to perform this task
 */
Std_ReturnType GPIO_pin_write_logic (const pin_config_t * _pin_config_ptr, logic_t _logic)
{
    Std_ReturnType ret = E_OK;
    if (NULL == _pin_config_ptr || _pin_config_ptr->pin > PORT_PIN_MAX_NUMBER-1
            || _pin_config_ptr->port > PORT_MAX_NUMBER-1)
    {
        ret = E_NOT_OK;
    }
    else
    {
        /* useless to write in LAT register, while the pin is defined as input*/
        if (_pin_config_ptr->direction == GPIO_DIRECTION_INPUT)
        {
            ret = E_NOT_OK;
        }
        else
        {
            switch(_logic)
            {
                case GPIO_LOW :
                    CLEAR_BIT(*LAT_Registers[_pin_config_ptr->port], _pin_config_ptr->pin);
                    break;
                case GPIO_HIGH :
                    SET_BIT  (*LAT_Registers[_pin_config_ptr->port], _pin_config_ptr->pin);
                    break;
                default :
                    ret = E_NOT_OK;
                    break;
            }
        }       
    }
    return ret;
}
#endif

#if GPIO_PORT_PIN_CONFIGURATIONS == CONFIG_ENABLE
/**
 * @param _pin_config_ptr
 * @return Status of the Function
 *          E_OK     : The Function done successfully
 *          E_NOT_OK : The Function has issue to perform this task
 */
Std_ReturnType GPIO_pin_toggle_logic (const pin_config_t * _pin_config_ptr)
{
    Std_ReturnType ret = E_OK;
    if (NULL == _pin_config_ptr || _pin_config_ptr->pin > PORT_PIN_MAX_NUMBER-1
            || _pin_config_ptr->port > PORT_MAX_NUMBER-1)
    {
        ret = E_NOT_OK;
    }
    else
    {
        /* useless to write in LAT Register, while the pin is defined as input*/
        if (_pin_config_ptr->direction == GPIO_DIRECTION_INPUT)
        {
            ret = E_NOT_OK;
        }
        else
        {
            TOGGLE_BIT(*LAT_Registers[_pin_config_ptr->port], _pin_config_ptr->pin);
        }
    }
    return ret;
}
#endif

#if GPIO_PORT_PIN_CONFIGURATIONS == CONFIG_ENABLE
/**
 * @param _pin_config_ptr
 * @return Status of the Function
 *          E_OK     : The Function done successfully
 *          E_NOT_OK : The Function has issue to perform this task
 */
Std_ReturnType GPIO_pin_initialize (const pin_config_t * _pin_config_ptr)
{
    Std_ReturnType ret = E_OK;
    if (NULL == _pin_config_ptr || _pin_config_ptr->port > PORT_MAX_NUMBER-1 
            || _pin_config_ptr->pin > PORT_PIN_MAX_NUMBER-1)
    {
        ret = E_NOT_OK;
    }
    else
    {
        ret  = GPIO_pin_direction_initialize(_pin_config_ptr);
        ret &= GPIO_pin_write_logic(_pin_config_ptr, _pin_config_ptr->logic);
    }
    return ret;
}
#endif

#if GPIO_PORT_CONFIGURATIONS == CONFIG_ENABLE
/**
 * 
 * @param _port
 * @param direction
 * @return Status of the Function
 *          E_OK     : The Function done successfully
 *          E_NOT_OK : The Function has issue to perform this task
 */
Std_ReturnType GPIO_port_direction_initialize(port_index_t _port, uint8 direction)
{
    Std_ReturnType ret = E_OK;
    if (_port > PORT_MAX_NUMBER-1)
    {
        ret = E_NOT_OK;
    }
    else
    {
        *TRIS_Registers[_port] = direction;
    }
    return ret;
}
#endif

#if GPIO_PORT_CONFIGURATIONS == CONFIG_ENABLE
/**
 * @brief Initialize port with specific bits directions and values
 * @param _port
 * @param direction
 * @return 
 */
Std_ReturnType GPIO_port_initialize(port_index_t _port, uint8 direction, uint8 logic)
{
    Std_ReturnType ret = E_OK;
    if (_port > PORT_MAX_NUMBER-1)
    {
        ret = E_NOT_OK;
    }
    else
    {
        ret  = GPIO_port_direction_initialize(_port, direction);       
        ret &= GPIO_port_write_logic(_port, logic);    
    }
    return ret;
}
#endif

#if GPIO_PORT_CONFIGURATIONS == CONFIG_ENABLE
/**
 * 
 * @param _port
 * @param direction_status
 * @return Status of the Function
 *          E_OK     : The Function done successfully
 *          E_NOT_OK : The Function has issue to perform this task
 */
Std_ReturnType GPIO_port_get_direction_status(port_index_t _port, uint8 *direction_status)
{
    Std_ReturnType ret = E_OK;
    if (NULL == direction_status || _port > PORT_MAX_NUMBER-1)
    {
        ret = E_NOT_OK;
    }
    else
    {
        *direction_status = *TRIS_Registers[_port];
    }
    return ret;
}
#endif

#if GPIO_PORT_CONFIGURATIONS == CONFIG_ENABLE
/**
 * 
 * @param _port
 * @param port_logic
 * @return Status of the Function
 *          E_OK     : The Function done successfully
 *          E_NOT_OK : The Function has issue to perform this task
 */
Std_ReturnType GPIO_port_write_logic (port_index_t _port, uint8 port_logic)
{
    Std_ReturnType ret = E_OK;
    if (_port > PORT_MAX_NUMBER-1)
    {
        ret = E_NOT_OK;
    }
    else
    {
        *(LAT_Registers[_port]) = port_logic;
    }
    return ret;
}
#endif

#if GPIO_PORT_CONFIGURATIONS == CONFIG_ENABLE
/**
 * 
 * @param _port
 * @param port_logic_ptr
 * @return Status of the Function
 *          E_OK     : The Function done successfully
 *          E_NOT_OK : The Function has issue to perform this task
 */
Std_ReturnType GPIO_port_read_logic (port_index_t _port, uint8 *port_logic_ptr)
{
    Std_ReturnType ret = E_OK;
    if (NULL == port_logic_ptr || _port > PORT_MAX_NUMBER-1)
    {
        ret = E_NOT_OK;
    }
    else
    {
        *port_logic_ptr = *PORT_Registers[_port];
    }
    return ret;
}
#endif


#if GPIO_PORT_CONFIGURATIONS == CONFIG_ENABLE
/**
 * 
 * @param _port
 * @return Status of the Function
 *          E_OK     : The Function done successfully
 *          E_NOT_OK : The Function has issue to perform this task
 */
Std_ReturnType GPIO_port_toggle(port_index_t _port)
{
    Std_ReturnType ret = E_OK;
    if (_port > PORT_MAX_NUMBER-1)
    {
        ret = E_NOT_OK;
    }
    else
    {
        *LAT_Registers[_port] ^= PORT_MASK;       
    }
    return ret;
}
#endif
