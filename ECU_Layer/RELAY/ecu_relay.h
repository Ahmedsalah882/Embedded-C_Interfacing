/* 
 * File:   ecu_relay.h
 * Author: AhmedSalah
 *
 * Created on August 21, 2023, 9:15 AM
 */

#ifndef ECU_RELAY_H
#define	ECU_RELAY_H

/* Section: Includes */
#include "ecu_relay_config.h"
#include"../../MCAL_Layer/GPIO/hal_gpio.h"

/* Section: Macro Definitions */

/* Section: Macro Functions */

/* Section: Data Type Declarations */
typedef enum{
    RELAY_OFF,
    RELAY_ON        
}relay_status_t;

typedef struct{
    uint8 port                      :3;
    uint8 pin                       :3;
    relay_status_t relay_status;
    uint8 reserved                  :1;
}relay_t;
/* Section: Function Prototypes */
std_ReturnType relay_initialize(const relay_t * _relay);
std_ReturnType relay_turn_on(const relay_t* _relay);
std_ReturnType relay_turn_off(const relay_t* _relay);




#endif	/* ECU_RELAY_H */

