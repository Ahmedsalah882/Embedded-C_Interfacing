/* 
 * File:   ecu_push_button.c
 * Author: AhmedSalah
 *
 * Created on August 20, 2023, 2:23 PM
 */


#include "ecu_push_button.h"

/**
 * 
 * @param _button_t
 * @return :status of the function 
 *         E_OK: the function executed successfully
 *         E_NOT_OK: the function failed     
 */
std_ReturnType button_initialize(const button_t * _button)
{
    std_ReturnType ret= E_OK;
    if (NULL== _button)
    {
        ret= E_NOT_OK;
    }
    else
    {
        // Did n`t use the pin initialize function as it contain write logic and this is input device 
        ret=gpio_pin_direction_inialize(&(_button->pin));
    }
    return ret;
}

/**
 * 
 * @param _button_t
 * @param _button_status_t
 * @return :status of the function 
 *         E_OK: the function executed successfully
 *         E_NOT_OK: the function failed
 */
std_ReturnType button_read_state(const button_t* _button, button_status_t * _button_status)
{
    std_ReturnType ret= E_OK;
    if (NULL== _button || NULL== _button_status)
    {
        ret= E_NOT_OK;
    }
    else
    {
        logic_t pin_logic=GPIO_LOW;
        ret=gpio_pin_read_logic(&(_button->pin),&pin_logic);
        if (BUTTON_ACTIVE_HIGH==_button->button_connection)
        {
            if (GPIO_LOW==pin_logic)
            {
             *_button_status=BUTTON_RELEASED;   
            }
            else
            {
                *_button_status=BUTTON_PRESSED;
            }
        }
        else if (BUTTON_ACTIVE_LOW==_button->button_connection)
        {
            if (GPIO_LOW==pin_logic)
            {
                *_button_status=BUTTON_PRESSED;
            }
            else
            {
                *_button_status=BUTTON_RELEASED;
            }
        }
        else{  /* DO Nothing*/}
        
    }
    return ret;
}        

