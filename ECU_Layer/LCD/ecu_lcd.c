/* 
 * File:   ecu_lcd.c
 * Author: AhmedSalah
 *
 * Created on August 26, 2023, 1:52 PM
 */



#include "ecu_lcd.h"

static std_ReturnType lcd_4bit_send_enable_signal(const lcd_4bit_t* _lcd);
static std_ReturnType lcd_4bit_set_cursor(const lcd_4bit_t* _lcd ,uint8 row,uint8 column);
static std_ReturnType lcd_send_4bit(const lcd_4bit_t* _lcd, uint8 _data_command);

static std_ReturnType lcd_8bit_send_enable_signal(const lcd_8bit_t* _lcd);
static std_ReturnType lcd_8bit_set_cursor(const lcd_8bit_t* _lcd,uint8 row,uint8 column);

/**
 * 
 * @param _lcd_4bit
 * @return status of the function 
 *         E_OK: the function executed successfully
 *         E_NOT_OK: the function failed  
 */
std_ReturnType lcd_4bit_initialize(const lcd_4bit_t* _lcd_4bit)
{
     std_ReturnType ret=E_OK;
     if(NULL== _lcd_4bit)
     {
      ret=E_NOT_OK;   
     }
     else
     {
         uint8 l_data_pins_counter=ZERO_INIT;
         float32 volt=VCC_5V;
         ret=gpio_pin_inialize(&(_lcd_4bit->rs_pin));
         ret=gpio_pin_inialize(&(_lcd_4bit->en_pin));
         for(l_data_pins_counter=0;l_data_pins_counter<LCD_DATA_PINS_4BIT;l_data_pins_counter++)
         {
                    ret=gpio_pin_inialize(&(_lcd_4bit->data_pins[l_data_pins_counter]));
         }
         
         if(VCC_5V==volt)
         {
             __delay_ms(20);
         }
         else if (VCC_3_3V==volt)
         {
             __delay_ms(45);
         }    
         ret=lcd_4bit_send_command(_lcd_4bit,0x30);
         __delay_ms(5);
         ret=lcd_4bit_send_command(_lcd_4bit,0x30);
         __delay_us(150);
         ret=lcd_4bit_send_command(_lcd_4bit,0x30);
         
       
         ret=lcd_4bit_send_command(_lcd_4bit,LCD_CLEAR_DISPLAY);
         ret=lcd_4bit_send_command(_lcd_4bit,LCD_CURSOR_RETURN_HOME);
         ret=lcd_4bit_send_command(_lcd_4bit,LCD_ENTRY_MODE_INCREMENT_NO_SHIFITNG);
         ret=lcd_4bit_send_command(_lcd_4bit,LCD_DISPLAY_ON_CURSOR_ON_BLINK_OFF);
         ret=lcd_4bit_send_command(_lcd_4bit,LCD_4BIT_2_LINE_DISPLAY_5X8_DOT);
         ret=lcd_4bit_send_command(_lcd_4bit,LCD_DDRAM_ADDRESS_START);
         
     }
     
     return ret;
}
/**
 * 
 * @param _lcd_4bit
 * @param command
 * @return status of the function 
 *         E_OK: the function executed successfully
 *         E_NOT_OK: the function failed 
 */
std_ReturnType lcd_4bit_send_command(const lcd_4bit_t* _lcd_4bit, uint8 command)
{
     std_ReturnType ret=E_OK;
     if(NULL== _lcd_4bit)
     {
      ret=E_NOT_OK;   
     }
     else
     {
         ret=gpio_pin_write_logic(&(_lcd_4bit->rs_pin),GPIO_LOW);
         
         ret=lcd_send_4bit(_lcd_4bit,command >> 4);
         ret=lcd_4bit_send_enable_signal(_lcd_4bit);
         ret=lcd_send_4bit(_lcd_4bit,command );
         ret=lcd_4bit_send_enable_signal(_lcd_4bit);
     }
     
     return ret;
}
/**
 * 
 * @param _lcd_4bit
 * @param data
 * @return status of the function 
 *         E_OK: the function executed successfully
 *         E_NOT_OK: the function failed 
 */
std_ReturnType lcd_4bit_send_char_data(const lcd_4bit_t* _lcd_4bit ,uint8 data)
{
     std_ReturnType ret=E_OK;
     if(NULL== _lcd_4bit)
     {
      ret=E_NOT_OK;   
     }
     else
     {
         ret=gpio_pin_write_logic(&(_lcd_4bit->rs_pin),GPIO_HIGH);
         
         ret=lcd_send_4bit(_lcd_4bit,data >> 4);
         ret=lcd_4bit_send_enable_signal(_lcd_4bit);
         ret=lcd_send_4bit(_lcd_4bit,data );
         ret=lcd_4bit_send_enable_signal(_lcd_4bit);
     }
     
     return ret;
}
/**
 * 
 * @param _lcd_4bit
 * @param row
 * @param column
 * @param data
 * @return status of the function 
 *         E_OK: the function executed successfully
 *         E_NOT_OK: the function failed 
 */
std_ReturnType lcd_4bit_send_char_data_specific_position(const lcd_4bit_t* _lcd_4bit
                                                 ,uint8 row,uint8 column, uint8 data)
{
     std_ReturnType ret=E_OK;
     if(NULL== _lcd_4bit)
     {
      ret=E_NOT_OK;   
     }
     else
     {
         ret=lcd_4bit_set_cursor(_lcd_4bit,row,column);
         ret=lcd_4bit_send_char_data(_lcd_4bit,data);
     }
     
     return ret;
}
/**
 * 
 * @param _lcd_4bit
 * @param string
 * @return status of the function 
 *         E_OK: the function executed successfully
 *         E_NOT_OK: the function failed 
 */
std_ReturnType lcd_4bit_send_string(const lcd_4bit_t* _lcd_4bit ,uint8* string)
{
     std_ReturnType ret=E_OK;
     if(NULL== _lcd_4bit || NULL== string )
     {
      ret=E_NOT_OK;   
     }
     else
     {  uint8 l_counter_string=ZERO_INIT;
         while(string[l_counter_string])
         {
             ret=lcd_4bit_send_char_data(_lcd_4bit,string[l_counter_string]);
             l_counter_string++;
         }
     }
     
     return ret;
}
/**
 * 
 * @param _lcd_4bit
 * @param row
 * @param column
 * @param string
 * @return status of the function 
 *         E_OK: the function executed successfully
 *         E_NOT_OK: the function failed 
 */
std_ReturnType lcd_4bit_send_string_specific_position(const lcd_4bit_t* _lcd_4bit
                                                 ,uint8 row,uint8 column,uint8* string)
{
     std_ReturnType ret=E_OK;
     if(NULL== _lcd_4bit || NULL== string )
     {
      ret=E_NOT_OK;   
     }
     else
     {
         ret=lcd_4bit_set_cursor(_lcd_4bit,row,column);
         ret=lcd_4bit_send_string(_lcd_4bit,string);
     }
     
     return ret;    
}
/**
 * 
 * @param _lcd_4bit
 * @param row
 * @param column
 * @param _char
 * @param mem_loc
 * @return status of the function 
 *         E_OK: the function executed successfully
 *         E_NOT_OK: the function failed 
 */
std_ReturnType lcd_4bit_send_custom_char(const lcd_4bit_t* _lcd_4bit,
                                                uint8 row,uint8 column,
                                        const uint8 _char[],uint8 mem_loc)
{
     std_ReturnType ret=E_OK;
     if(NULL== _lcd_4bit  )
     {
      ret=E_NOT_OK;   
     }
     else
     {
         uint8 l_counter=ZERO_INIT;
       mem_loc--; 
       ret=lcd_4bit_send_command(_lcd_4bit,(LCD_CGRAM_ADDRESS_START + (mem_loc*8)) );
       for(l_counter=ZERO_INIT; l_counter<8;l_counter++)
       {
           ret=lcd_4bit_send_char_data(_lcd_4bit,_char[l_counter]);
       }
       ret=lcd_4bit_send_char_data_specific_position(_lcd_4bit,row,column,mem_loc);
     }
     
     return ret;
}




/**
 * 
 * @param _lcd_8bit
 * @return status of the function 
 *         E_OK: the function executed successfully
 *         E_NOT_OK: the function failed 
 */
std_ReturnType lcd_8bit_initialize(const lcd_8bit_t* _lcd_8bit)
{
    std_ReturnType ret=E_OK;
     if(NULL== _lcd_8bit  )
     {
      ret=E_NOT_OK;   
     }
     else
     {
         uint8 l_data_pins_counter=ZERO_INIT;
         float32 volt=VCC_5V;
         ret=gpio_pin_inialize(&(_lcd_8bit->rs_pin));
         ret=gpio_pin_inialize(&(_lcd_8bit->en_pin));
         for(l_data_pins_counter=0;l_data_pins_counter<LCD_DATA_PINS_8BIT;l_data_pins_counter++)
         {
                    ret=gpio_pin_inialize(&(_lcd_8bit->data_pins[l_data_pins_counter]));
         }
         if(VCC_5V==volt)
         {
             __delay_ms(20);
         }
         else if (VCC_3_3V==volt)
         {
             __delay_ms(45);
         }    
         ret=lcd_8bit_send_command(_lcd_8bit,0x30);
         __delay_ms(5);
         ret=lcd_8bit_send_command(_lcd_8bit,0x30);
         __delay_us(150);
         ret=lcd_8bit_send_command(_lcd_8bit,0x30);
         
         ret=lcd_8bit_send_command(_lcd_8bit,LCD_CLEAR_DISPLAY);
         ret=lcd_8bit_send_command(_lcd_8bit,LCD_CURSOR_RETURN_HOME);
         ret=lcd_8bit_send_command(_lcd_8bit,LCD_ENTRY_MODE_INCREMENT_NO_SHIFITNG);
         ret=lcd_8bit_send_command(_lcd_8bit,LCD_DISPLAY_ON_CURSOR_ON_BLINK_OFF);
         ret=lcd_8bit_send_command(_lcd_8bit,LCD_8BIT_2_LINE_DISPLAY_5X8_DOT);
         ret=lcd_8bit_send_command(_lcd_8bit,LCD_DDRAM_ADDRESS_START);
     }
     
     return ret;
}
/**
 * 
 * @param _lcd_8bit
 * @param command
 * @return status of the function 
 *         E_OK: the function executed successfully
 *         E_NOT_OK: the function failed 
 */
std_ReturnType lcd_8bit_send_command(const lcd_8bit_t* _lcd_8bit, uint8 command)
{
     std_ReturnType ret=E_OK;
     if(NULL== _lcd_8bit  )
     {
      ret=E_NOT_OK;   
     }
     else
     {   uint8 l_command_counter=ZERO_INIT;   
         ret=gpio_pin_write_logic(&(_lcd_8bit->rs_pin),GPIO_LOW);
         
         for(l_command_counter=ZERO_INIT;l_command_counter<LCD_DATA_PINS_8BIT;l_command_counter++)
         {
             ret=gpio_pin_write_logic(&(_lcd_8bit->data_pins[l_command_counter])
                     , (command >> l_command_counter) & 0x01);
         }
         ret=lcd_8bit_send_enable_signal(_lcd_8bit);
     }
     
     return ret;
}
/**
 * 
 * @param _lcd_8bit
 * @param data
 * @return status of the function 
 *         E_OK: the function executed successfully
 *         E_NOT_OK: the function failed 
 */
std_ReturnType lcd_8bit_send_char_data(const lcd_8bit_t* _lcd_8bit ,uint8 data)
{
     std_ReturnType ret=E_OK;
     if(NULL== _lcd_8bit  )
     {
      ret=E_NOT_OK;   
     }
     else
     {
         uint8 l_data_counter=ZERO_INIT;   
         ret=gpio_pin_write_logic(&(_lcd_8bit->rs_pin),GPIO_HIGH);
         
         for(l_data_counter=ZERO_INIT;l_data_counter<LCD_DATA_PINS_8BIT;l_data_counter++)
         {
             ret=gpio_pin_write_logic(&(_lcd_8bit->data_pins[l_data_counter])
                     , (data >> l_data_counter) & 0x01);
         }
         ret=lcd_8bit_send_enable_signal(_lcd_8bit);
     }
     
     return ret;
}
/**
 * 
 * @param _lcd_8bit
 * @param row
 * @param column
 * @param data
 * @return status of the function 
 *         E_OK: the function executed successfully
 *         E_NOT_OK: the function failed 
 */
std_ReturnType lcd_8bit_send_char_data_specific_position(const lcd_8bit_t* _lcd_8bit
                                                   ,uint8 row,uint8 column,uint8 data)
{
     std_ReturnType ret=E_OK;
     if(NULL== _lcd_8bit  )
     {
      ret=E_NOT_OK;   
     }
     else
     {
         uint8 l_data_counter=ZERO_INIT;
         ret=lcd_8bit_set_cursor(_lcd_8bit,row,column);
         ret=lcd_8bit_send_char_data(_lcd_8bit,data);
     }
     
     return ret;
}
/**
 * 
 * @param _lcd_8bit
 * @param string
 * @return status of the function 
 *         E_OK: the function executed successfully
 *         E_NOT_OK: the function failed 
 */
std_ReturnType lcd_8bit_send_string(const lcd_8bit_t* _lcd_8bit ,uint8* string)
{
     std_ReturnType ret=E_OK;
     if(NULL== _lcd_8bit || NULL== string )
     {
      ret=E_NOT_OK;   
     }
     else
     {
         uint8 l_counter_char=ZERO_INIT;
         while(string[l_counter_char])
         {    
            ret=lcd_8bit_send_char_data(_lcd_8bit,string[l_counter_char]);
            l_counter_char++;
     
         }
     }
     return ret;
}
/**
 * 
 * @param _lcd_8bit
 * @param row
 * @param column
 * @param string
 * @return status of the function 
 *         E_OK: the function executed successfully
 *         E_NOT_OK: the function failed 
 */
std_ReturnType lcd_8bit_send_string_specific_position(const lcd_8bit_t* _lcd_8bit
                                                   ,uint8 row,uint8 column,uint8* string)
{
     std_ReturnType ret=E_OK;
     if(NULL== _lcd_8bit || NULL== string  )
     {
      ret=E_NOT_OK;   
     }
     else
     {
         ret=lcd_8bit_set_cursor(_lcd_8bit,row,column);
         ret=lcd_8bit_send_string(_lcd_8bit,string);
     }
     
     return ret;
}
/**
 * 
 * @param _lcd_8bit
 * @param row
 * @param column
 * @param _char
 * @param mem_loc
 * @return status of the function 
 *         E_OK: the function executed successfully
 *         E_NOT_OK: the function failed 
 */
std_ReturnType lcd_8bit_send_custom_char(const lcd_8bit_t* _lcd_8bit,
                                                uint8 row,uint8 column,
                                        const uint8 _char[],uint8 mem_loc)
{
     std_ReturnType ret=E_OK;
     if(NULL== _lcd_8bit  )
     {
      ret=E_NOT_OK;   
     }
     else
     { 
       uint8 l_counter=ZERO_INIT;
       mem_loc--; 
       ret=lcd_8bit_send_command(_lcd_8bit,(LCD_CGRAM_ADDRESS_START + (mem_loc*8)) );
       for(l_counter=ZERO_INIT; l_counter<8;l_counter++)
       {
           ret=lcd_8bit_send_char_data(_lcd_8bit,_char[l_counter]);
       }
       ret=lcd_8bit_send_char_data_specific_position(_lcd_8bit,row,column,mem_loc);
     }
     
     return ret;
}


/**
 * 
 * @param value
 * @param string
 * @return status of the function 
 *         E_OK: the function executed successfully
 *         E_NOT_OK: the function failed 
 */
std_ReturnType convert_byte_to_string(uint8 value, uint8* string)
{
     std_ReturnType ret=E_OK;
     uint8 temp_str[4]={0};
     uint8 str_counter=0;
     if(NULL== string  )
     {
      ret=E_NOT_OK;   
     }
     else
     { 
       memset(string,' ',3);
       string[4]='\0';          /* to force the lcd stop printing */
       sprintf(temp_str,"%i",value);
       /*to remove the \0 added at the end by sprintf*/
       while(temp_str[str_counter])
       {
           string[str_counter]=temp_str[str_counter];
           str_counter++;
       }
     }
     
     return ret;
}
/**
 * 
 * @param value
 * @param string
 * @return status of the function 
 *         E_OK: the function executed successfully
 *         E_NOT_OK: the function failed 
 */
std_ReturnType convert_short_to_string(uint16 value, uint8* string)
{
     std_ReturnType ret=E_OK;
     uint8 temp_str[6]={0};
     uint8 str_counter=0;
     if(NULL== string  )
     {
      ret=E_NOT_OK;   
     }
     else
     {
       memset(string,' ',5);
       string[5]='\0';  /*to force the lcd stop printing*/
       sprintf(temp_str,"%i",value);
       /*to solve the \0 added at the end of string by sprintf */
       while(temp_str[str_counter])
       {
           string[str_counter]=temp_str[str_counter];
           str_counter++;
       }        
     }
     
     return ret;
}
/**
 * 
 * @param value
 * @param string
 * @ret
 * 
 * 
 * 
 * urn status of the function 
 *         E_OK: the function executed successfully
 *         E_NOT_OK: the function failed 
 */
std_ReturnType convert_int_to_string(uint32 value, uint8* string)
{
     std_ReturnType ret=E_OK;
     uint8 temp_str[11]={0};
     uint8 str_counter=0;
     if(NULL== string  )
     {
      ret=E_NOT_OK;   
     }
     else
     {
       memset(string,' ',10);
       string[11]='\0';        /* to force the lcd stop printng*/
       sprintf(string,"%i",value);
       /*to remove the null at the end added by sprintf */
       while(temp_str[str_counter])
       {
           string[str_counter]=temp_str[str_counter];
           str_counter++;
       }
     }
     
     return ret;
}
/**
 * 
 * @param _lcd
 * @return status of the function 
 *         E_OK: the function executed successfully
 *         E_NOT_OK: the function failed
 */
static std_ReturnType lcd_8bit_send_enable_signal(const lcd_8bit_t* _lcd)
{
     std_ReturnType ret=E_OK;
     if(NULL== _lcd  )
     {
      ret=E_NOT_OK;   
     }
     else
     {
         ret=gpio_pin_write_logic(&(_lcd->en_pin),GPIO_HIGH);
         __delay_us(5);
         ret=gpio_pin_write_logic(&(_lcd->en_pin),GPIO_LOW);
         __delay_us(5);
     }
     
     return ret;
}        
/**
 * 
 * @param _lcd
 * @return status of the function 
 *         E_OK: the function executed successfully
 *         E_NOT_OK: the function failed
 */
static std_ReturnType lcd_4bit_send_enable_signal(const lcd_4bit_t* _lcd)
{
     std_ReturnType ret=E_OK;
     if(NULL== _lcd  )
     {
      ret=E_NOT_OK;   
     }
     else
     {
         ret=gpio_pin_write_logic(&(_lcd->en_pin),GPIO_HIGH);
         __delay_us(5);
         ret=gpio_pin_write_logic(&(_lcd->en_pin),GPIO_LOW);
         __delay_us(5);
     }
     
     return ret;
}        
/**
 * 
 * @param _lcd
 * @param _data_command
 * @return status of the function 
 *         E_OK: the function executed successfully
 *         E_NOT_OK: the function failed
 */
static std_ReturnType lcd_send_4bit(const lcd_4bit_t* _lcd, uint8 _data_command)
{
    std_ReturnType ret=E_OK;
     if(NULL== _lcd  )
     {
      ret=E_NOT_OK;   
     }
     else
     {
         ret=gpio_pin_write_logic(&(_lcd->data_pins[0]), (_data_command >> 0) &(uint8)0x01 );
         ret=gpio_pin_write_logic(&(_lcd->data_pins[1]), (_data_command >> 1) &(uint8)0x01 );
         ret=gpio_pin_write_logic(&(_lcd->data_pins[2]), (_data_command >> 2) &(uint8)0x01 );
         ret=gpio_pin_write_logic(&(_lcd->data_pins[3]), (_data_command >> 3) &(uint8)0x01 );
     }
     
     return ret;
}
/**
 * 
 * @param _lcd
 * @param row
 * @param column
 * @return status of the function 
 *         E_OK: the function executed successfully
 *         E_NOT_OK: the function failed 
 */
static std_ReturnType lcd_8bit_set_cursor(const lcd_8bit_t* _lcd ,uint8 row,uint8 column)
{
    std_ReturnType ret=E_OK;
     if(NULL== _lcd  )
     {
      ret=E_NOT_OK;   
     }
     else
     {
         column--;
         switch(row)
         {
             case ROW1: 
                 ret=lcd_8bit_send_command(_lcd, (0x80 + column));
                 break;
             case ROW2: 
                 ret=lcd_8bit_send_command(_lcd, (0xc0 + column));
                 break;
             case ROW3: 
                 ret=lcd_8bit_send_command(_lcd, (0x94 + column));
                 break;
             case ROW4: 
                 ret=lcd_8bit_send_command(_lcd, (0xd4+ column));
                 break;
             default:
                 ret=E_NOT_OK;
                 break;
         }
     }
     
     return ret;
}
/**
 * 
 * @param _lcd
 * @param row
 * @param column
 * @return status of the function 
 *         E_OK: the function executed successfully
 *         E_NOT_OK: the function failed
 */
static std_ReturnType lcd_4bit_set_cursor(const lcd_4bit_t* _lcd ,uint8 row,uint8 column)
{
    std_ReturnType ret=E_OK;
     if(NULL== _lcd  )
     {
      ret=E_NOT_OK;   

     }
     else
     {
         column--;
         switch(row)
         {
             case ROW1: 
                 ret=lcd_4bit_send_command(_lcd, (0x80 + column));
                 break;
             case ROW2: 
                 ret=lcd_4bit_send_command(_lcd, (0xc0 + column));
                 break;
             case ROW3: 
                 ret=lcd_4bit_send_command(_lcd, (0x94 + column));
                 break;
             case ROW4: 
                 ret=lcd_4bit_send_command(_lcd, (0xd4+ column));
                 break;
             default:
                 ret=E_NOT_OK;
                 break;
         }
     }
     
     return ret;
}

