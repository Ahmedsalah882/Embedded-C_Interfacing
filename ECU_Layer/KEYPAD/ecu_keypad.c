/* 
 * File:   ecu_keypad.c
 * Author: AhmedSalah
 *
 * Created on August 24, 2023, 4:12 AM
 */

#include "ecu_keypad.h"

static const uint8 keypad_buttons[KEYPAD_MAX_ROWS][KEYPAD_MAX_COLUMNS]={
                                                                          {'7','8','9','/'},
                                                                          {'4','5','6','*'},
                                                                          {'1','2','3','-'},
                                                                          {'#','0','=','+'}
                                                                        };
/**
 * @brief initialize the keypad
 * @param _keypad
 * @return status of the function 
 *         E_OK : the function executed successfully
 *         E_NOT_OK: the function failed 
 */
std_ReturnType keypad_initialize(const keypad_t * _keypad)
{
    std_ReturnType ret= E_OK;
    if (NULL==_keypad)
    {
        ret=E_NOT_OK;
    }   
    else
    {
        uint8 row_counter=ZERO_INIT, column_counter=ZERO_INIT;
        for(row_counter;row_counter<KEYPAD_MAX_ROWS;row_counter++)
        {
            for(column_counter;column_counter<KEYPAD_MAX_COLUMNS;column_counter++)
            {
                ret=gpio_pin_inialize(&(_keypad->keypad_column_pins[column_counter]));
            }
            ret=gpio_pin_inialize(&(_keypad->keypad_row_pins[row_counter]));
            
        }
        
        
        
    }   
    return ret;
}
/**
 * @brief get the button pressed from the keypad
 * @param _keypad
 * @param value
 * @return status of the function 
 *         E_OK : the function executed successfully
 *         E_NOT_OK: the function failed 
 */
std_ReturnType keypad_get_value(const keypad_t* _keypad, uint8 * value )
{
    std_ReturnType ret= E_OK;
    if (NULL==_keypad || NULL== value)
    {
        ret=E_NOT_OK;
    }   
    else
    {  uint8 row_counter=ZERO_INIT,column_counter=ZERO_INIT,counter=ZERO_INIT,column_stauts=GPIO_LOW;
        for(row_counter=ZERO_INIT;row_counter<KEYPAD_MAX_ROWS;row_counter++)
        {   
            for(counter=ZERO_INIT;counter<KEYPAD_MAX_ROWS;counter++)
            {
                ret=gpio_pin_write_logic(&(_keypad->keypad_row_pins[counter]),GPIO_LOW);
            }
             
            ret=gpio_pin_write_logic(&(_keypad->keypad_row_pins[row_counter]),GPIO_HIGH);
            for(column_counter=ZERO_INIT;column_counter<KEYPAD_MAX_COLUMNS;column_counter++)
            {   ret=gpio_pin_read_logic(&(_keypad->keypad_column_pins[column_counter]),&column_stauts);
                if(GPIO_HIGH==column_stauts)
                {
                    *value=keypad_buttons[row_counter][column_counter];
                }
            }
        }
        
    }   
    return ret;
}