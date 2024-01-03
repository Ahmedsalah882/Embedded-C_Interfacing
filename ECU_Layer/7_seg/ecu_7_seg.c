/* 
 * File:   ecu_7_seg.c
 * Author: AhmedSalah
 *
 * Created on August 23, 2023, 1:55 PM
 */

#include "ecu_7_seg.h"

/**
 * 
 * @param seven_seg
 * @return status of the function
 *         E_OK: the function executed successfully
 *         E_NOT_OK: the function failed  
 */
std_ReturnType seven_seg_initialize(const seven_seg_t* seven_seg)
{
    std_ReturnType ret= E_OK;
    if (NULL== seven_seg)
    {
        ret=E_NOT_OK;
    }
    else
    {
       ret=gpio_pin_inialize(&(seven_seg->seven_seg_pin[SEVEN_SEG_PIN0]));
       ret=gpio_pin_inialize(&(seven_seg->seven_seg_pin[SEVEN_SEG_PIN1]));
       ret=gpio_pin_inialize(&(seven_seg->seven_seg_pin[SEVEN_SEG_PIN2]));
       ret=gpio_pin_inialize(&(seven_seg->seven_seg_pin[SEVEN_SEG_PIN3]));
    }
    return ret;
}

/**
 * 
 * @param seven_seg
 * @param number
 * @return status of the function
 *         E_OK: the function executed successfully
 *         E_NOT_OK: the function failed  
 */
std_ReturnType seven_seg_write_number(const seven_seg_t * seven_seg ,uint8 number)
{
    std_ReturnType ret= E_OK;
    if (NULL== seven_seg || number > SEVEN_SEG_MAX_NUM_DISPLAY   || number <  SEVEN_SEG_MIN_NUM_DISPLAY    )
    {
        ret=E_NOT_OK;
    }
    else
    {
     ret=gpio_pin_write_logic(&(seven_seg->seven_seg_pin[SEVEN_SEG_PIN0]), number & 0x01); //this gets the first bit in number
     ret=gpio_pin_write_logic(&(seven_seg->seven_seg_pin[SEVEN_SEG_PIN1]), (number>>1) & 0x01);//this gets the second bit in number
     ret=gpio_pin_write_logic(&(seven_seg->seven_seg_pin[SEVEN_SEG_PIN2]), (number>>2) & 0x01);//this gets the third bit in number
     ret=gpio_pin_write_logic(&(seven_seg->seven_seg_pin[SEVEN_SEG_PIN3]), (number>>3) & 0x01);//this gets the first bit in number
    }
    return ret;
}