/* 
 * File:   ecu_led.h
 * Author: HP
 *
 * Created on August 16, 2023, 2:16 PM
 */

#ifndef ECU_LED_H
#define	ECU_LED_H

/* Section: Includes */
#include "../../MCAL_Layer/GPIO/hal_gpio.h"
#include "ecu_led_config.h"

/* Section: Macro Definitions */

/* Section: Macro Functions */

/* Section: Data type Declarations*/
typedef enum{
    LED_OFF,
    LED_ON        
}led_status_t;

typedef struct{
    uint8 port          :3;
    uint8 pin           :3;
    uint8 led_status    :1;
    uint8 reseved       :1;   /* For Future Use*/
}led_t;


/* Section: Function Prototype */
std_ReturnType led_initialize(const led_t* _led_t);
std_ReturnType led_turn_on(const led_t* _led_t);
std_ReturnType led_turn_off(const led_t* _led_t);
std_ReturnType led_toggle(const led_t* _led_t);

#endif	/* ECU_LED_H */

