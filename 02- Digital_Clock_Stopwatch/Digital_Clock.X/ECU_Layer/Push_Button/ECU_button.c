/* 
 * File:   ECU_button.c
 * Author: ahmed
 *
 * Created on January 22, 2023, 2:22 AM
 */

#include "ECU_button.h"


#if BUTTON_CONFIG == CONFIG_ENABEL
/**
 * @brief Initialize the assigned pin to be input
 * @param btn_config
 * @return state of the function, where
 *                  E_OK     : function executed successfully !
 *                  E_NOT_OK : function has issue while performing this action !
 */
Std_ReturnType BUTTON_initialize(const button_config_t *btn_config)
{
    Std_ReturnType ret = E_NOT_OK;
    if (NULL == btn_config)
    {
        ret = E_NOT_OK;
    }
    else
    {
        ret = GPIO_pin_direction_initialize(&(btn_config->button_pin));
    }
    return ret;
}

/**
 * @brief Read the state of the button
 * @param btn_config
 * @param btn_state_ptr
 * @return state of the function, where
 *                  E_OK     : function executed successfully !
 *                  E_NOT_OK : function has issue while performing this action !
 */
Std_ReturnType BUTTON_read_state(const button_config_t *btn_config, button_state_t *btn_state_ptr)
{
    Std_ReturnType ret = E_NOT_OK;
    logic_t btn_pin_logic = GPIO_HIGH;
    if (NULL == btn_config || NULL == btn_state_ptr)
    {
        ret = E_NOT_OK;
    }
    else
    {
        ret = GPIO_pin_read_logic(&(btn_config->button_pin), &btn_pin_logic);
        if (btn_config->btn_connection == BUTTON_ACTIVE_HIGH)
        {
            if (btn_pin_logic == GPIO_HIGH)
            {
                *btn_state_ptr = BUTTON_PRESSED;
            }
            else
            {
                *btn_state_ptr = BUTTON_RELEASED;
            }
        }
        else if (btn_config->btn_connection == BUTTON_ACTIVE_LOW)
        {
            if (btn_pin_logic == GPIO_HIGH)
            {
                *btn_state_ptr = BUTTON_RELEASED;
            }
            else
            {
                *btn_state_ptr = BUTTON_PRESSED;
            } 
        }
        else
        {/* do nothing */}
    }
    return ret;
}
#endif