/* 
 * File:   HAL_GPIO.c
 * Author: AhmedSalah
 *
 * Created on August 16, 2023, 1:57 PM
 */

#include "hal_gpio.h"
/* Reference to  Data Direction register */
volatile uint8* tris_registers[] ={&TRISA ,&TRISB ,&TRISC ,&TRISD ,&TRISE};
/* Reference to  Port Status Register */
volatile uint8* port_registers[] ={&PORTA ,&PORTB ,&PORTC ,&PORTD ,&PORTE};
/* Reference to  Data Latch  Register */
volatile uint8* lat_registers[]  ={&LATA  ,&LATB  ,&LATC  ,&LATD  ,&LATE};

/**
 * 
 * @param _pin_config
 * @return status of the function
 *         E_OK : function done successfully
 *         E_NOT_OK: function failed       
 */
#if GPIO_PORT_PIN_CONFIGURATION ==CONFIG_ENABLE
std_ReturnType gpio_pin_direction_inialize(const pin_config_t * _pin_config)
{
    std_ReturnType ret=E_OK;
    if(NULL==_pin_config || _pin_config->pin >  PORT_PIN_MAX_NUMBER-1)
    {
        ret=E_NOT_OK;
    }
    else
    {
        switch(_pin_config->direction)
        {
            case GPIO_DIRECTION_OUTPUT:
                CLEAR_BIT(*tris_registers[_pin_config->port],_pin_config->pin);
            break;    
            
            case GPIO_DIRECTION_INPUT:
                SET_BIT(*tris_registers[_pin_config->port],_pin_config->pin);
            break;
            
            default:
                 ret=E_NOT_OK;
            break;    
        }
    }
    
    return ret;
}
#endif

/**
 * 
 * @param _pin_config
 * @param dir
 * @return status of the function
 *         E_OK : function done successfully
 *         E_NOT_OK: function failed     
 */
#if GPIO_PORT_PIN_CONFIGURATION ==CONFIG_ENABLE
std_ReturnType gpio_pin_get_direction(const pin_config_t *_pin_config, direction_t * dir )
{
    std_ReturnType ret=E_OK;
    if(NULL==_pin_config || NULL== dir || _pin_config->pin >  PORT_PIN_MAX_NUMBER-1)
    {
        ret=E_NOT_OK;
    }
    else
    {
            *dir= READ_BIT(*tris_registers[_pin_config->port],_pin_config->pin);      
    }
    
    return ret;
}
#endif
/**
 * 
 * @param _pin_config
 * @param logic
 * @return status of the function
 *         E_OK : function done successfully
 *         E_NOT_OK: function failed     
 */
#if GPIO_PORT_PIN_CONFIGURATION ==CONFIG_ENABLE
std_ReturnType gpio_pin_write_logic(const pin_config_t* _pin_config, logic_t logic)
{
    std_ReturnType ret=E_OK;
    if(NULL==_pin_config || _pin_config->pin >  PORT_PIN_MAX_NUMBER-1)
    {
        ret=E_NOT_OK;
    }
    else
    {
        switch (logic)
        {
            case GPIO_HIGH:
                SET_BIT(*lat_registers[_pin_config->port],_pin_config->pin);
            break;
            
            case GPIO_LOW:
                CLEAR_BIT(*lat_registers[_pin_config->port],_pin_config->pin);
            break;
            
            default:
                ret=E_NOT_OK;
            break;    
        }     
    }
    
    return ret;
    
}
#endif
/**
 * 
 * @param _pin_config
 * @param logic
 * @return status of the function
 *         E_OK : function done successfully
 *         E_NOT_OK: function failed     
 */
#if GPIO_PORT_PIN_CONFIGURATION ==CONFIG_ENABLE
std_ReturnType gpio_pin_read_logic(const pin_config_t* _pin_config, logic_t* logic)
{
    std_ReturnType ret=E_OK;
    if(NULL==_pin_config || NULL==logic || _pin_config->pin >  PORT_PIN_MAX_NUMBER-1)
    {
        ret=E_NOT_OK;
    }
    else
    {
        *logic=READ_BIT(*port_registers[_pin_config->port],_pin_config->pin);
    }
    
    return ret;
}
#endif
/**
 * 
 * @param _pin_config
 * @return status of the function
 *         E_OK : function done successfully
 *         E_NOT_OK: function failed     
 */
#if GPIO_PORT_PIN_CONFIGURATION ==CONFIG_ENABLE
std_ReturnType gpio_pin_toggle_logic(const pin_config_t* _pin_config)
{
    std_ReturnType ret=E_OK;
    if(NULL==_pin_config || _pin_config->pin >  PORT_PIN_MAX_NUMBER-1)
    {
        ret=E_NOT_OK;
    }
    else
    {
        TOGGLE_BIT(*lat_registers[_pin_config->port],_pin_config->pin);
    }
    
    return ret;
}
#endif
/**
 * 
 * @param _pin_config 
 * @return status of the function
 *         E_OK : function done successfully
 *         E_NOT_OK: function failed     
 */
#if GPIO_PORT_PIN_CONFIGURATION ==CONFIG_ENABLE
std_ReturnType gpio_pin_inialize(pin_config_t* _pin_config)
{
    std_ReturnType ret =E_OK;
    if(NULL==_pin_config || _pin_config->pin > PORT_PIN_MAX_NUMBER-1)
    {
        ret=E_NOT_OK;
    }
    else
    {
        ret=gpio_pin_direction_inialize(_pin_config);
        ret=gpio_pin_write_logic(_pin_config,_pin_config->logic);
    }
    return ret;
}
#endif


/**
 * 
 * @param port_index
 * @param dir
 * @return status of the function
 *         E_OK : function done successfully
 *         E_NOT_OK: function failed     
 */
#if GPIO_PORT_CONFIGURATION ==CONFIG_ENABLE
std_ReturnType gpio_port_direction_inialize(port_index_t  port_index, uint8 dir)
{
    std_ReturnType ret=E_OK;
    
    if(port_index > PORT_MAX_NUMBER-1)
    {
        ret=E_NOT_OK;
    }  
    else
    {
            *tris_registers[port_index]=dir;      
    }     
    
    return ret;
}
#endif
/**
 * 
 * @param port_index
 * @param dir
 * @return status of the function
 *         E_OK : function done successfully
 *         E_NOT_OK: function failed     
 */
#if GPIO_PORT_CONFIGURATION ==CONFIG_ENABLE
std_ReturnType gpio_port_get_direction( port_index_t port_index, uint8 * dir )
{
    std_ReturnType ret=E_OK;
    if(NULL==dir || port_index > PORT_MAX_NUMBER-1 )
    {
        ret=E_NOT_OK;
    }
    else
    {
        *dir=*tris_registers[port_index];
    }
    
    return ret;
}
#endif
/**
 * 
 * @param port_index
 * @param logic
 * @return status of the function
 *         E_OK : function done successfully
 *         E_NOT_OK: function failed     
 */
#if GPIO_PORT_CONFIGURATION ==CONFIG_ENABLE
std_ReturnType gpio_port_write_logic( port_index_t port_index, uint8 logic)
{
    std_ReturnType ret=E_OK;
     if(port_index > PORT_MAX_NUMBER-1)
    {
        ret=E_NOT_OK;
    }  
    else
    {
            *lat_registers[port_index]=logic;      
    }     
    
    return ret;
}
#endif
/**
 * 
 * @param port_index
 * @param logic
 * @return status of the function
 *         E_OK : function done successfully
 *         E_NOT_OK: function failed     
 */
#if GPIO_PORT_CONFIGURATION ==CONFIG_ENABLE
std_ReturnType gpio_port_read_logic(port_index_t port_index, uint8* logic)
{
    std_ReturnType ret=E_OK;
    if(NULL==logic || port_index > PORT_MAX_NUMBER-1)
    {
        ret=E_NOT_OK;
    }
    else
    {
        *logic=*port_registers[port_index];
    }
    
    return ret;
}
#endif
/**
 * 
 * @param port_index
 * @return status of the function
 *         E_OK : function done successfully
 *         E_NOT_OK: function failed     
 */
#if GPIO_PORT_CONFIGURATION ==CONFIG_ENABLE
std_ReturnType gpio_port_toggle_logic(port_index_t port_index)
{
    std_ReturnType ret=E_OK;
     if(port_index > PORT_MAX_NUMBER-1)
    {
        ret=E_NOT_OK;
    }  
    else
    {
         *lat_registers[port_index]^= PORT_MASK;
    }       
    
    return ret;
}
#endif
