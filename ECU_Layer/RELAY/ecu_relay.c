/* 
 * File:   ecu_relay.c
 * Author: AhmedSalah
 *
 * Created on August 21, 2023, 9:15 AM
 */

#include "ecu_relay.h"

/**
 * @brief initialize the relay
 * @param _relay
 * @return  the status of the function
 *          E_OK: the function executed successfully
 *          E_NOT_OK: the function failed  
 */
std_ReturnType relay_initialize(const relay_t * _relay)
{
    std_ReturnType ret=E_OK;
    if(NULL== _relay)
    {
        ret=E_NOT_OK;
    }
    else
    {   
        pin_config_t pin_config={
        .port=_relay->port,
        .pin=_relay->pin,
        .direction=GPIO_DIRECTION_OUTPUT,
        .logic=_relay->relay_status
    };
        ret=gpio_pin_inialize(&pin_config);
    }
    
    return ret;        
}
/**
 * @brief turning on the relay
 * @param _relay
 * @return the status of the function
 *          E_OK: the function executed successfully
 *          E_NOT_OK: the function failed
 */
std_ReturnType relay_turn_on(const relay_t* _relay)
{
    std_ReturnType ret=E_OK;
    if(NULL== _relay)
    {
        ret=E_NOT_OK;
    }
    else
    {   
        pin_config_t pin_config={
        .port=_relay->port,
        .pin=_relay->pin,
        .direction=GPIO_DIRECTION_OUTPUT,
        .logic=_relay->relay_status
        };
        ret=gpio_pin_write_logic(&pin_config,GPIO_HIGH);
    }
    
    return ret;
}
/**
 * @brief turning off the relay
 * @param _relay
 * @return the status of the function
 *          E_OK: the function executed successfully
 *          E_NOT_OK: the function failed
 */
std_ReturnType relay_turn_off(const relay_t* _relay)
{
    std_ReturnType ret=E_OK;
    if(NULL== _relay)
    {
        ret=E_NOT_OK;
    }
    else
    {
        pin_config_t pin_config={
        .port=_relay->port,
        .pin=_relay->pin,
        .direction=GPIO_DIRECTION_OUTPUT,
        .logic=_relay->relay_status
        };
        ret=gpio_pin_write_logic(&pin_config,GPIO_LOW);
    }
    
    return ret;
}
