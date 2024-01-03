/* 
 * File:   ecu_7_seg.h
 * Author: AhmedSalah
 *
 * Created on August 23, 2023, 1:55 PM
 */

#ifndef ECU_7_SEG_H
#define	ECU_7_SEG_H


/* Section: Includes */
#include "ecu_7_seg_config.h"
#include "../../MCAL_Layer/GPIO/hal_gpio.h"

/* Section: Macro Definitions  */
#define SEVEN_SEG_MIN_NUM_DISPLAY    0
#define SEVEN_SEG_MAX_NUM_DISPLAY    9

/* Section: Macro Functions */

/* Section: Data Type Declarations */
typedef enum{
    SEVEN_SEG_PIN0,
    SEVEN_SEG_PIN1,
    SEVEN_SEG_PIN2,
    SEVEN_SEG_PIN3        
}seven_seg_pin_t;

typedef enum{
    _7_SEG_COM_ANODE,
    _7_SEG_COM_CATHODE        
}seven_seg_type_t;

typedef struct{
    pin_config_t seven_seg_pin[4];
    seven_seg_type_t seven_seg_type;
    
}seven_seg_t; 
/* Section: Function Prototypes */
std_ReturnType seven_seg_initialize(const seven_seg_t* seven_seg);
std_ReturnType seven_seg_write_number(const seven_seg_t * seven_seg ,uint8 number);


#endif	/* ECU_7_SEG_H */

