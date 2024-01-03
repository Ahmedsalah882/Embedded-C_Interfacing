/* 
 * File:   ecu_dc_motor.h
 * Author: AhmedSalah   
 *
 * Created on August 22, 2023, 10:09 AM
 */

#ifndef ECU_DC_MOTOR_H
#define	ECU_DC_MOTOR_H

/* Section: Includes */
#include "ecu_dc_motor_config.h"
#include "../../MCAL_Layer/GPIO/hal_gpio.h"

/* Section: Macro Definitions */
#define DC_MOTOR_PIN1       0x00
#define DC_MOTOR_PIN2       0x01
/* Section: Macro Functions */

/* Section: Data Type Declarations */
typedef enum{
    DC_MOTOR_TURN_OFF,
    DC_MOTOR_TURN_ON        
}dc_motor_status_t;


typedef struct {
   pin_config_t dc_motor_pin[2];
}dc_motor_t;



/* Section: Function prototype */
std_ReturnType dc_motor_initalize(const dc_motor_t* _dc_motor);
std_ReturnType dc_motor_move_right(const dc_motor_t* _dc_motor );
std_ReturnType dc_motor_move_left(const dc_motor_t* _dc_motor);
std_ReturnType dc_motor_stop(const dc_motor_t* _dc_motor);
        
#endif	/* ECU_DC_MOTOR_H */

