/* 
 * File:   ecu_motor.h
 * Author: ahmed
 *
 * Created on January 31, 2023, 1:26 AM
 */

#ifndef ECU_MOTOR_H
#define	ECU_MOTOR_H

/* Section : Includes */
#include "../../MCAL_init/DIO_Driver/hal_DIO.h"
#include "ecu_motor_cfg.h"
#if DC_MOTOR_MODULE == MODULE_ENABLE
/* Section : MACRO Declarations */

#define DC_MOTOR_STATUS_ON      0x01U
#define DC_MOTOR_STATUS_OFF     0x00U

/* Section : MACRO Function Declarations */

/* Section : Data Type Declarations */
// this structure is describing each pin configuration of the dc motor 


// this structure describe the dc motor (2 pins [right- left])
typedef struct {
	gpio_config_pin_t dc_motor_pin[2];
}dc_motor_t;

/* Section : Functions Declarations */
Std_ReturnType dc_motor_init (const dc_motor_t *_dc_motor_ptr);
Std_ReturnType dc_motor_move_right(const dc_motor_t *_dc_motor_ptr);
Std_ReturnType dc_motor_move_left (const dc_motor_t *_dc_motor_ptr);
Std_ReturnType dc_motor_stop (const dc_motor_t *_dc_motor_ptr);
        
#endif
#endif	/* ECU_MOTOR_H */

