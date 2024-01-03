/* 
 * File:   ecu_push_button.h
 * Author: AhmedSalah
 *
 * Created on August 20, 2023, 2:23 PM
 */

#ifndef ECU_PUSH_BUTTON_H
#define	ECU_PUSH_BUTTON_H

/* Section: Includes */
#include "ecu_push_button_config.h"
#include "../../MCAL_Layer/GPIO/hal_gpio.h"

/* Section: Macro Definitions */

/* Section: Macro Functions */


/* Section: Data Type Declarations */
typedef enum{
    BUTTON_PRESSED,
    BUTTON_RELEASED        
}button_status_t;

typedef enum{
    BUTTON_ACTIVE_LOW,
    BUTTON_ACTIVE_HIGH        
}button_connection_t;

typedef struct{
    pin_config_t pin;
    button_status_t button_status   ;
    button_connection_t button_connection;

}button_t;

/* Section: Function Prototypes */
std_ReturnType button_initialize(const button_t * _button);
std_ReturnType button_read_state(const button_t* _button, button_status_t * _button_status);



#endif	/* ECU_PUSH_BUTTON_H */

