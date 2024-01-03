/* 
 * File:   ecu_lcd.h
 * Author: AhmedSalah
 *
 * Created on August 26, 2023, 1:49 PM
 */

#ifndef ECU_LCD_H
#define	ECU_LCD_H

/* Section: Includes */
#include "ecu_lcd_config.h"
#include "../../MCAL_Layer/GPIO/hal_gpio.h"
#include "../../MCAL_Layer/std_lib.h"
/* Section: Macro Definitions */
#define LCD_CLEAR_DISPLAY                                             0x01

#define LCD_CURSOR_RETURN_HOME                                        0x02

#define LCD_ENTRY_MODE_DECREMENT_NO_SHIFTING                          0x04
#define LCD_ENTRY_MODE_INCREMENT_NO_SHIFITNG                          0x06
#define LCD_ENTRY_MODE_SHIFT_LEFT                                     0x07
#define LCD_ENTRY_MODE_SHIFT_RIGHT                                    0x05

#define LCD_DISPLAY_OFF_CURSOR_OFF_BLINK_OFF                          0x08    
#define LCD_DISPLAY_OFF_CURSOR_OFF_BLINK_ON                           0x09
#define LCD_DISPLAY_OFF_CURSOR_ON_BLINK_OFF                           0x0A
#define LCD_DISPLAY_OFF_CURSOR_ON_BLINK_ON                            0x0B
#define LCD_DIAPLAY_ON_CURSOR_OFF_BLINK_OFF                           0x0C
#define LCD_DISPLAY_ON_CURSOR_OFF_BLINK_ON                            0x0D
#define LCD_DISPLAY_ON_CURSOR_ON_BLINK_OFF                            0x0E
#define LCD_DISPLAY_ON_CURSOR_ON_BLINK_ON                             0x0F

#define LCD_CURSOR_MOVEE_LEFT                                         0x10
#define LCD_CURSOR_MOVE_RIGHT                                         0x14
#define LCD_DISPLAY_SHIFT_LEFT                                        0x18
#define LCD_DISPLAY_SHIFT_RIGHT                                       0x1C

#define LCD_4BIT_1_LINE_DISPLAY_5X8_DOT                               0x20
#define LCD_4BIT_1_LINE_DISPLAY_5X11_DOT                              0x24
#define LCD_4BIT_2_LINE_DISPLAY_5X8_DOT                               0x28
#define LCD_4BIT_2_LINE_DISPLAT_5X11_DOT                              0x2C
#define LCD_8BIT_1_LINE_DISPLAY_5X8_DOT                               0x30
#define LCD_8BIT_1_LINE_DISPLAY_5X11_DOT                              0x34
#define LCD_8BIT_2_LINE_DISPLAY_5X8_DOT                               0x38
#define LCD_8BIT_2_LINE_DISPLAY_5X11_DOT                              0x3C



#define LCD_CGRAM_ADDRESS_START                                      0x40
#define LCD_DDRAM_ADDRESS_START                                      0x80

#define LCD_DATA_PINS_4BIT                                           0x04
#define LCD_DATA_PINS_8BIT                                           0x08

#define VCC_5V                                                      5
#define VCC_3_3V                                                    3.3

#define ROW1                                                        0x01
#define ROW2                                                        0x02
#define ROW3                                                        0x03
#define ROW4                                                        0x04

/* Section: Macro Functions */

/* Section: Data Type Declarations */

typedef struct{
    pin_config_t rs_pin;
    pin_config_t en_pin;
    pin_config_t data_pins[4];
}lcd_4bit_t;

typedef struct{
    pin_config_t rs_pin;
    pin_config_t en_pin;
    pin_config_t data_pins[8];
}lcd_8bit_t;


/* Section: function prototype */
std_ReturnType lcd_4bit_initialize(const lcd_4bit_t* _lcd_4bit);
std_ReturnType lcd_4bit_send_command(const lcd_4bit_t* _lcd_4bit, uint8 command);
std_ReturnType lcd_4bit_send_char_data(const lcd_4bit_t* _lcd_4bit ,uint8 data);
std_ReturnType lcd_4bit_send_char_data_specific_position(const lcd_4bit_t* _lcd_4bit
                                                 ,uint8 row,uint8 column, uint8 data);
std_ReturnType lcd_4bit_send_string(const lcd_4bit_t* _lcd_4bit ,uint8* string);
std_ReturnType lcd_4bit_send_string_specific_position(const lcd_4bit_t* _lcd_4bit
                                                 ,uint8 row,uint8 column,uint8* string);
std_ReturnType lcd_4bit_send_custom_char(const lcd_4bit_t* _lcd_4bit,
                                                uint8 row,uint8 column,
                                        const uint8 _char[],uint8 mem_loc);


std_ReturnType lcd_8bit_initialize(const lcd_8bit_t* _lcd_8bit);
std_ReturnType lcd_8bit_send_command(const lcd_8bit_t* _lcd_8bit, uint8 command);
std_ReturnType lcd_8bit_send_char_data(const lcd_8bit_t* _lcd_8bit ,uint8 data);
std_ReturnType lcd_8bit_send_char_data_specific_position(const lcd_8bit_t* _lcd_8bit
                                                   ,uint8 row,uint8 column,uint8 data);
std_ReturnType lcd_8bit_send_string(const lcd_8bit_t* _lcd_8bit ,uint8* string);
std_ReturnType lcd_8bit_send_string_specific_position(const lcd_8bit_t* _lcd_8bit
                                                   ,uint8 row,uint8 column,uint8* string);
std_ReturnType lcd_8bit_send_custom_char(const lcd_8bit_t* _lcd_8bit,
                                                uint8 row,uint8 column,
                                        const uint8 _char[],uint8 mem_loc);

std_ReturnType convert_byte_to_string(uint8 value, uint8* string);
std_ReturnType convert_short_to_string(uint16 value, uint8* string);
std_ReturnType convert_int_to_string(uint32 value, uint8* string);

#endif	/* ECU_LCD_H */

