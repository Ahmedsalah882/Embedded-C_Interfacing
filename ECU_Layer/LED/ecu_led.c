/* 
 * File:   ecu_led.c
 * Author: AhmedSalah
 *
 * Created on August 16, 2023, 2:16 PM
 */


#include "ecu_led.h"
/**
 * @bried inialize the led
 * @param _led_t
 * @return  statue of the function
 *          E_OK: the function executed successfully
 *          E_NOT_OK : the function failed
 */
std_ReturnType led_initialize(const led_t* _led_t)
{   
    std_ReturnType ret =E_OK;
    if(NULL==_led_t )
    {
        ret=E_NOT_OK;
    }
    else
    {
        pin_config_t pin_obj={
            .port=_led_t->port,
            .pin=_led_t->pin,
            .direction=GPIO_DIRECTION_OUTPUT,
            .logic=_led_t->led_status
        };
        ret=gpio_pin_inialize(&pin_obj);
    }
    return ret;
}
/**
 * @brief turn on led
 * @param _led_t
 * @return statue of the function
 *          E_OK: the function executed successfully
 *          E_NOT_OK : the function failed
 */
std_ReturnType led_turn_on(const led_t* _led_t)
{
    std_ReturnType ret =E_OK;
    if(NULL==_led_t )
    {
        ret=E_NOT_OK;
    }
    else
    {
        pin_config_t pin_obj={
          .port=_led_t->port,
          .pin=_led_t->pin,
          .direction=GPIO_DIRECTION_OUTPUT,
          .logic=_led_t->led_status
        };
        ret=gpio_pin_write_logic(&pin_obj,GPIO_HIGH);
    }
    return ret;
}
/**
 * @brief turn off led
 * @param _led_t
 * @return statue of the function
 *          E_OK: the function executed successfully
 *          E_NOT_OK : the function failed
 */
std_ReturnType led_turn_off(const led_t* _led_t)
{
    std_ReturnType ret =E_OK;
    if(NULL==_led_t )
    {
        ret=E_NOT_OK;
    }
    else
    {
        pin_config_t pin_obj={
          .port=_led_t->port,
          .pin=_led_t->pin,
          .direction=GPIO_DIRECTION_OUTPUT,
          .logic=_led_t->led_status
        };
        ret=gpio_pin_write_logic(&pin_obj,GPIO_LOW);
    }
    return ret;
}
/**
 * @brief toggle led
 * @param _led_t
 * @return statue of the function
 *          E_OK: the function executed successfully
 *          E_NOT_OK : the function failed
 */
std_ReturnType led_toggle(const led_t* _led_t)
{
    std_ReturnType ret =E_OK;
    if(NULL==_led_t )
    {
        ret=E_NOT_OK;
    }
    else
    {   pin_config_t pin_obj={
      .port=_led_t->port,
      .pin=_led_t->pin,
      .direction=GPIO_DIRECTION_OUTPUT,
      .logic=_led_t->led_status
    };
        ret=gpio_pin_toggle_logic(&pin_obj);
    }
    return ret;
}
