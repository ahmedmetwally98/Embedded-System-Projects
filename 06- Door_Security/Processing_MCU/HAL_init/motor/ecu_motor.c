/* 
 * File:   ecu_motor.c
 * Author: ahmed
 *
 * Created on January 31, 2023, 1:26 AM
 */


#include "ecu_motor.h"


#if DC_MOTOR_MODULE == MODULE_ENABLE
/**
 * @brief  Initialize the assigned pins to be OUTPUT that controls the DC_motor 
 * @param  _dc_motor_ptr Pointer to the motor object configuration
 * @return STATUS of the function
 *          E_OK     : action executed successfully !
 *          E_NOT_OK : action execution faild !
 */
Std_ReturnType dc_motor_init (const dc_motor_t *_dc_motor_ptr)
{
    Std_ReturnType ret = E_OK;
    if (_dc_motor_ptr == NULL)
    {
        ret = E_NOT_OK;
    }
    else
    {   
        ret = GPIO_pin_initialize(&(_dc_motor_ptr->dc_motor_pin[DC_MOTOR_PIN1]));
        ret = GPIO_pin_initialize(&(_dc_motor_ptr->dc_motor_pin[DC_MOTOR_PIN2]));
    }
    return ret;
    
}
/**
 * @brief  rotate motor to right direction
 * @param  _dc_motor_ptr Pointer to the motor object configuration
 * @return STATUS of the function
 *          E_OK     : action executed successfully !
 *          E_NOT_OK : action execution faild !
 */
Std_ReturnType dc_motor_move_right(const dc_motor_t *_dc_motor_ptr)
{
    Std_ReturnType ret = E_OK;
    if (_dc_motor_ptr == NULL)
    {
        ret = E_NOT_OK;
    }
    else
    {
        GPIO_pin_write_logic(&(_dc_motor_ptr->dc_motor_pin[DC_MOTOR_PIN1]), GPIO_HIGH);
        GPIO_pin_write_logic(&(_dc_motor_ptr->dc_motor_pin[DC_MOTOR_PIN2]), GPIO_LOW);
    }
    return ret;
}
/**
 * @brief  rotate motor to left direction  
 * @param  _dc_motor_ptr Pointer to the motor object configuration
 * @return STATUS of the function
 *          E_OK     : action executed successfully !
 *          E_NOT_OK : action execution faild !
 */
Std_ReturnType dc_motor_move_left (const dc_motor_t *_dc_motor_ptr)
{
    Std_ReturnType ret = E_OK;
    if (_dc_motor_ptr == NULL)
    {
        ret = E_NOT_OK;
    }
    else
    {
        GPIO_pin_write_logic(&(_dc_motor_ptr->dc_motor_pin[DC_MOTOR_PIN1]), GPIO_LOW);
        GPIO_pin_write_logic(&(_dc_motor_ptr->dc_motor_pin[DC_MOTOR_PIN2]), GPIO_HIGH);
    }
    return ret;
}
/**
 * @brief  stop the motor 
 * @param  _dc_motor_ptr Pointer to the motor object configuration
 * @return STATUS of the function
 *          E_OK     : action executed successfully !
 *          E_NOT_OK : action execution faild !
 */
Std_ReturnType dc_motor_stop (const dc_motor_t *_dc_motor_ptr)
{
    Std_ReturnType ret = E_OK;
    if (_dc_motor_ptr == NULL)
    {
        ret = E_NOT_OK;
    }
    else
    {
        GPIO_pin_write_logic(&(_dc_motor_ptr->dc_motor_pin[DC_MOTOR_PIN1]), GPIO_LOW);
        GPIO_pin_write_logic(&(_dc_motor_ptr->dc_motor_pin[DC_MOTOR_PIN2]), GPIO_LOW);
    }
    return ret;
}
#endif
