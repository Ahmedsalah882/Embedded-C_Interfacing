/* 
 * File:   ecu_lm35.h
 * Author: AhmedSalah
 *
 * Created on September 11, 2023, 8:13 PM
 */

#ifndef ECU_LM35_H
#define	ECU_LM35_H


/* Section: Includes */
#include "ecu_lm35_config.h"
#include"../../MCAL_Layer/ADC/mcal_adc.h"
#include"../../MCAL_Layer/ADC/mcal_adc_config.h"

/* Section: Macro Definitions */

/* Section: Macro Functions */

/* Section: Data Type Declarations */



/* Section: Function Prototypes */
std_ReturnType Read_LM35_Temp(const adc_t* lm35, uint8* result);







#endif	/* ECU_LM35_H */

