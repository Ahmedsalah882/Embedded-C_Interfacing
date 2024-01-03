/* 
 * File:   ecu_dc_motor.c
 * Author: AhmedSalah   
 *
 * Created on August 22, 2023, 10:09 AM
 */
#include "ecu_dc_motor.h"

/**
 * @brief  initialize the dc motor 
 * @param _dc_motor
 * @return status of the function 
 *         E_OK: function executed successfully
 *         E_NOT_OK: function failed  
 */
std_ReturnType dc_motor_initalize(const dc_motor_t* _dc_motor)
{
    std_ReturnType ret=E_OK;
    if(NULL==_dc_motor)
    {
        ret=E_NOT_OK;
    }   
    else
    {
        ret=gpio_pin_inialize(&(_dc_motor->dc_motor_pin[0]));
        ret=gpio_pin_inialize(&(_dc_motor->dc_motor_pin[1]));
    }
    return ret;
}    
/**
 * @brief  move the dc motor to right
 * @param _dc_motor
 * @return status of the function 
 *         E_OK: function executed successfully
 *         E_NOT_OK: function failed
 */
std_ReturnType dc_motor_move_right(const dc_motor_t* _dc_motor )
{
    std_ReturnType ret=E_OK;
    if(NULL==_dc_motor)
    {
        ret=E_NOT_OK;
    }   
    else
    {
        ret=gpio_pin_write_logic(&(_dc_motor->dc_motor_pin[DC_MOTOR_PIN1]),GPIO_HIGH);
        ret=gpio_pin_write_logic(&(_dc_motor->dc_motor_pin[DC_MOTOR_PIN2]),GPIO_LOW);
    }
    return ret; 
}
/**
 * @brief  move the dc motor to left
 * @param _dc_motor
 * @return status of the function 
 *         E_OK: function executed successfully
 *         E_NOT_OK: function failed
 */
std_ReturnType dc_motor_move_left(const dc_motor_t* _dc_motor)
{
    std_ReturnType ret=E_OK;
    if(NULL==_dc_motor)
    {
        ret=E_NOT_OK;
    }   
    else
    {
        ret=gpio_pin_write_logic(&(_dc_motor->dc_motor_pin[DC_MOTOR_PIN1]),GPIO_LOW);
        ret=gpio_pin_write_logic(&(_dc_motor->dc_motor_pin[DC_MOTOR_PIN2]),GPIO_HIGH);
    }
    return ret; 
}
/**
 * @brief  stop the dc motor 
 * @param _dc_motor
 * @return status of the function 
 *         E_OK: function executed successfully
 *         E_NOT_OK: function failed
 */
std_ReturnType dc_motor_stop(const dc_motor_t* _dc_motor)
{
    std_ReturnType ret=E_OK;
    if(NULL==_dc_motor)
    {
        ret=E_NOT_OK;
    }   
    else
    {
       ret=gpio_pin_write_logic(&(_dc_motor->dc_motor_pin[DC_MOTOR_PIN1]),GPIO_LOW);
       ret=gpio_pin_write_logic(&(_dc_motor->dc_motor_pin[DC_MOTOR_PIN2]),GPIO_LOW);
    }
    return ret; 
}

