
#include "Ultrasonic.h"

Std_ReturnType Ultrasonic_Init(const ultrasonic_t *_config){
    Std_ReturnType ret = E_OK;
    
    if(NULL == _config){
        ret = E_NOT_OK;
    }
    else{
        ret = GPIO_pin_initialize(&(_config->Trigger_Pin));
        ret &= GPIO_pin_initialize(&(_config->Echo_Pin));
    }
    
    return ret;
}

Std_ReturnType Ultrasonic_TriggerPin(const ultrasonic_t *_config){
    Std_ReturnType ret = E_OK;
    if(NULL == _config){
        ret = E_NOT_OK;
    }
    else{
        /* Send Trigger Signal to the Ultrasonic Trigger Pin */
        ret = GPIO_pin_write_logic(&(_config->Trigger_Pin), GPIO_HIGH);
        _delay_us(10);
        ret = GPIO_pin_write_logic(&(_config->Trigger_Pin), GPIO_LOW);
    }
    
    return ret;
}

uint16 Ultrasonic_getDistance(const uint16 a_pulseLength)
{	// return distance by using formula (S(cm) = V(cm/s)*T(us) / 2000000 )
	return (uint16)(a_pulseLength * (SOUND_SPEED_CM_SECOND/2000000.0));
}
