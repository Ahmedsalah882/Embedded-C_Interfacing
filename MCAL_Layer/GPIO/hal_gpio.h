/* 
 * File:   HAL_GPIO.h
 * Author: AhmedSalah
 *
 * Created on August 16, 2023, 2:24 PM
 */

#ifndef HAL_GPIO_H
#define	HAL_GPIO_H

/* Section: Includes  */
#include "pic18f4620.h"
#include "../../MCAL_Layer/mcal_std_types.h"
#include "device_config.h"
#include "hal_gpio_config.h"
/* Section: Macro Definitions */
#define BIT_MASK                              (uint8)0X01
#define PORT_MASK                             (uint8)0xFF
#define PORT_PIN_MAX_NUMBER                   (uint8)8
#define PORT_MAX_NUMBER                       (uint8)5

#define GPIO_PORT_PIN_CONFIGURATION                CONFIG_ENABLE
#define GPIO_PORT_CONFIGURATION                    CONFIG_ENABLE

/* Section: Macro Functions */
#define HWREG8(_x)                       (*((volatile uint8 *)(_x)))   
#define SET_BIT(REG,BIT_POS)             (REG|=  (BIT_MASK<<BIT_POS))
#define CLEAR_BIT(REG,BIT_POS)           (REG&= ~(BIT_MASK<<BIT_POS))
#define TOGGLE_BIT(REG,BIT_POS)          (REG^=  (BIT_MASK<<BIT_POS))
#define READ_BIT(REG,BIT_POS)            ((REG>>BIT_POS)&BIT_MASK)



/* Section: Data Type Declarations */
typedef enum{
    PORTA_INDEX =0,
    PORTB_INDEX,
    PORTC_INDEX,
    PORTD_INDEX,
    PORTE_INDEX        
}port_index_t;

typedef enum{
    GPIO_PIN0=0,
    GPIO_PIN1,
    GPIO_PIN2,
    GPIO_PIN3,
    GPIO_PIN4,        
    GPIO_PIN5,
    GPIO_PIN6,
    GPIO_PIN7
}pin_t;

typedef enum {
    GPIO_DIRECTION_OUTPUT=0,
    GPIO_DIRECTION_INPUT        
}direction_t;

typedef enum{
    GPIO_LOW=0,
    GPIO_HIGH        
}logic_t;

typedef struct {
    uint8 port              :3;     /*@ref port_index_t */
    uint8 pin               :3;     /*@ref pin_t        */
    uint8 direction         :1;     /*@ref direction_t  */    
    uint8  logic            :1;     /*@ref logic_t  */
}pin_config_t;

/* Section: Function Prototypes */
std_ReturnType gpio_pin_direction_inialize(const pin_config_t * _pin_config);
std_ReturnType gpio_pin_get_direction(const pin_config_t *_pin_config, direction_t * dir );
std_ReturnType gpio_pin_write_logic(const pin_config_t* _pin_config, logic_t logic);
std_ReturnType gpio_pin_read_logic(const pin_config_t* _pin_config, logic_t* logic);
std_ReturnType gpio_pin_toggle_logic(const pin_config_t* _pin_config);
std_ReturnType gpio_pin_inialize(pin_config_t* _pin_config);

std_ReturnType gpio_port_direction_inialize(port_index_t  port_index , uint8 dir);
std_ReturnType gpio_port_get_direction( port_index_t port_index, uint8 * dir );
std_ReturnType gpio_port_write_logic( port_index_t port_index, uint8 logic);
std_ReturnType gpio_port_read_logic(port_index_t port_index, uint8* logic);
std_ReturnType gpio_port_toggle_logic(port_index_t port_index);



#endif	/* HAL_GPIO_H */

