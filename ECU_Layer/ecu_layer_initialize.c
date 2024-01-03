/* 
 * File:   ecu_layer_initialize.h
 * Author: AhmedSalah
 *
 * Created on August 24, 2023, 7:21 AM
 */


#include"ecu_layer_initialize.h"

led_t led1={
  .port=PORTA_INDEX,
  .pin=GPIO_PIN1,
  .led_status=LED_OFF
};

led_t led2={
  .port=PORTC_INDEX,
  .pin=GPIO_PIN3,
  .led_status=LED_OFF
};

led_t led3={
  .port=PORTC_INDEX,
  .pin=GPIO_PIN5,
  .led_status=LED_OFF
};
/*
relay_t relay1={
  .port=PORTC_INDEX,
  .pin=GPIO_PIN0,
  .relay_status=RELAY_OFF
};


dc_motor_t dc_motor_1={
 .dc_motor_pin[DC_MOTOR_PIN1].port=PORTD_INDEX,
 .dc_motor_pin[DC_MOTOR_PIN1].pin=GPIO_PIN0,
 .dc_motor_pin[DC_MOTOR_PIN1].direction=GPIO_DIRECTION_OUTPUT,
 .dc_motor_pin[DC_MOTOR_PIN1].logic=DC_MOTOR_TURN_OFF,
 .dc_motor_pin[DC_MOTOR_PIN2].port=PORTD_INDEX,
 .dc_motor_pin[DC_MOTOR_PIN2].pin=GPIO_PIN1,
 .dc_motor_pin[DC_MOTOR_PIN2].direction=GPIO_DIRECTION_OUTPUT,
 .dc_motor_pin[DC_MOTOR_PIN2].logic=DC_MOTOR_TURN_OFF 
};

dc_motor_t dc_motor_2={
 .dc_motor_pin[DC_MOTOR_PIN1].port=PORTD_INDEX,
 .dc_motor_pin[DC_MOTOR_PIN1].pin=GPIO_PIN2,
 .dc_motor_pin[DC_MOTOR_PIN1].direction=GPIO_DIRECTION_OUTPUT,
 .dc_motor_pin[DC_MOTOR_PIN1].logic=DC_MOTOR_TURN_OFF,
 .dc_motor_pin[DC_MOTOR_PIN2].port=PORTD_INDEX,
 .dc_motor_pin[DC_MOTOR_PIN2].pin=GPIO_PIN3,
 .dc_motor_pin[DC_MOTOR_PIN2].direction=GPIO_DIRECTION_OUTPUT,
 .dc_motor_pin[DC_MOTOR_PIN2].logic=DC_MOTOR_TURN_OFF 
};


uint16 adc_res1=0,lm35_res1=0,adc_res2=0,lm35_res2=0;
uint8 lm_req=0;

button_t btn_high1={
    .pin.port=PORTD_INDEX,
    .pin.pin=GPIO_PIN0,
    .pin.direction=GPIO_DIRECTION_INPUT,
    .pin.logic=GPIO_LOW,
    .button_connection=BUTTON_ACTIVE_HIGH,
    .button_status=BUTTON_RELEASED
};

button_t btn_low1={
    .pin.port=PORTD_INDEX,
    .pin.pin=GPIO_PIN4,
    .pin.direction=GPIO_DIRECTION_INPUT,
    .pin.logic=GPIO_HIGH,
    .button_connection=BUTTON_ACTIVE_LOW,
    .button_status=BUTTON_RELEASED
};


button_status_t btn_high1_status=BUTTON_RELEASED;
button_status_t btn_low1_status=BUTTON_RELEASED;
button_status_t btn_status_valid=0;
button_status_t btn_high1_last_status=BUTTON_RELEASED;

led_status_t led_last_status=LED_OFF;
uint32 btn_counter=0;
uint8 magic_btn_flag=0;

seven_seg_t seven_seg1={
  .seven_seg_pin[0].port=PORTC_INDEX,
  .seven_seg_pin[0].pin=GPIO_PIN0,
  .seven_seg_pin[0].direction=GPIO_DIRECTION_OUTPUT,
  .seven_seg_pin[0].logic=GPIO_LOW,
  
  .seven_seg_pin[1].port=PORTC_INDEX,
  .seven_seg_pin[1].pin=GPIO_PIN1,
  .seven_seg_pin[1].direction=GPIO_DIRECTION_OUTPUT,
  .seven_seg_pin[1].logic=GPIO_LOW,
  
  .seven_seg_pin[2].port=PORTC_INDEX,
  .seven_seg_pin[2].pin=GPIO_PIN2,
  .seven_seg_pin[2].direction=GPIO_DIRECTION_OUTPUT,
  .seven_seg_pin[2].logic=GPIO_LOW,
  
  .seven_seg_pin[3].port=PORTC_INDEX,
  .seven_seg_pin[3].pin=GPIO_PIN3,
  .seven_seg_pin[3].direction=GPIO_DIRECTION_OUTPUT,
  .seven_seg_pin[3].logic=GPIO_LOW,
};
pin_config_t seg1_pin_control1={
 .port=PORTD_INDEX,
 .pin=GPIO_PIN0,
 .direction=GPIO_DIRECTION_OUTPUT,
 .logic=GPIO_LOW
};

pin_config_t seg1_pin_control2={
 .port=PORTD_INDEX,
 .pin=GPIO_PIN1,
 .direction=GPIO_DIRECTION_OUTPUT,
 .logic=GPIO_LOW
};

pin_config_t seg1_pin_control3={
 .port=PORTD_INDEX,
 .pin=GPIO_PIN2,
 .direction=GPIO_DIRECTION_OUTPUT,
 .logic=GPIO_LOW
};
pin_config_t seg1_pin_control4={
 .port=PORTD_INDEX,
 .pin=GPIO_PIN3,
 .direction=GPIO_DIRECTION_OUTPUT,
 .logic=GPIO_LOW
};

pin_config_t seg1_pin_control5={
 .port=PORTD_INDEX,
 .pin=GPIO_PIN4,
 .direction=GPIO_DIRECTION_OUTPUT,
 .logic=GPIO_LOW
};

pin_config_t seg1_pin_control6={
 .port=PORTD_INDEX,
 .pin=GPIO_PIN5,
 .direction=GPIO_DIRECTION_OUTPUT,
 .logic=GPIO_LOW
};

uint8 counter=0,sec=55,min=59,hours=24;


keypad_t keypad1={
    .keypad_row_pins[0].port=PORTC_INDEX,
    .keypad_row_pins[0].pin=GPIO_PIN0,
    .keypad_row_pins[0].direction=GPIO_DIRECTION_OUTPUT,
    .keypad_row_pins[0].logic=GPIO_LOW,
    
    .keypad_row_pins[1].port=PORTC_INDEX,
    .keypad_row_pins[1].pin=GPIO_PIN1,
    .keypad_row_pins[1].direction=GPIO_DIRECTION_OUTPUT,
    .keypad_row_pins[1].logic=GPIO_LOW,
    
    .keypad_row_pins[2].port=PORTC_INDEX,
    .keypad_row_pins[2].pin=GPIO_PIN2,
    .keypad_row_pins[2].direction=GPIO_DIRECTION_OUTPUT,
    .keypad_row_pins[2].logic=GPIO_LOW,
    
    .keypad_row_pins[3].port=PORTC_INDEX,
    .keypad_row_pins[3].pin=GPIO_PIN3,
    .keypad_row_pins[3].direction=GPIO_DIRECTION_OUTPUT,
    .keypad_row_pins[3].logic=GPIO_LOW,
    
    .keypad_column_pins[0].port=PORTC_INDEX,
    .keypad_column_pins[0].pin=GPIO_PIN4,
    .keypad_column_pins[0].direction=GPIO_DIRECTION_INPUT,
    .keypad_column_pins[0].logic=GPIO_LOW,
    
    .keypad_column_pins[1].port=PORTC_INDEX,
    .keypad_column_pins[1].pin=GPIO_PIN5,
    .keypad_column_pins[1].direction=GPIO_DIRECTION_INPUT,
    .keypad_column_pins[1].logic=GPIO_LOW,
    
    .keypad_column_pins[2].port=PORTC_INDEX,
    .keypad_column_pins[2].pin=GPIO_PIN6,
    .keypad_column_pins[2].direction=GPIO_DIRECTION_INPUT,
    .keypad_column_pins[2].logic=GPIO_LOW,
    
    .keypad_column_pins[3].port=PORTC_INDEX,
    .keypad_column_pins[3].pin=GPIO_PIN7,
    .keypad_column_pins[3].direction=GPIO_DIRECTION_INPUT,
    .keypad_column_pins[3].logic=GPIO_LOW,
};
*/

std_ReturnType ret=E_NOT_OK;

void test_seven_seg_clock_project(void)
{ //to be called in the while (1)
    
    //fnum=((uint8)(num%10)) | ((uint8)(num/10)<<4); //without multiplexing
     /* 
         for(counter=0;counter<25;counter++)
         {
             //ret=gpio_port_direction_inialize(PORTD_INDEX,0x3E);                 //0011 1110
             
             ret=seven_seg_write_number(&seven_seg1,((uint8)(hours/10))); 
             ret=gpio_pin_write_logic(&seg1_pin_control1,GPIO_LOW);
             __delay_us(6667);
             ret=gpio_pin_write_logic(&seg1_pin_control1,GPIO_HIGH);
             //ret=gpio_port_direction_inialize(PORTD_INDEX,0x3D);                 //0011 1101
             
             ret=seven_seg_write_number(&seven_seg1,((uint8)(hours%10)));
             ret=gpio_pin_write_logic(&seg1_pin_control2,GPIO_LOW);
             __delay_us(6667);
             ret=gpio_pin_write_logic(&seg1_pin_control2,GPIO_HIGH);
             //ret=gpio_port_direction_inialize(PORTD_INDEX,0x3B);                 //0011 1011
             
             ret=seven_seg_write_number(&seven_seg1,((uint8)(min/10)));
             ret=gpio_pin_write_logic(&seg1_pin_control3,GPIO_LOW); 
             __delay_us(6667);
             ret=gpio_pin_write_logic(&seg1_pin_control3,GPIO_HIGH);
             //ret=gpio_port_direction_inialize(PORTD_INDEX,0x37);                 //0011 0111
             
             ret=seven_seg_write_number(&seven_seg1,((uint8)(min%10)));
             ret=gpio_pin_write_logic(&seg1_pin_control4,GPIO_LOW); 
             __delay_us(6667);
             ret=gpio_pin_write_logic(&seg1_pin_control4,GPIO_HIGH);
             //ret=gpio_port_direction_inialize(PORTD_INDEX,0x2F);                 //0010 1111
             
             ret=seven_seg_write_number(&seven_seg1,((uint8)(sec/10)));
             ret=gpio_pin_write_logic(&seg1_pin_control5,GPIO_LOW); 
             __delay_us(6667); 
             ret=gpio_pin_write_logic(&seg1_pin_control5,GPIO_HIGH);
            //ret=gpio_port_direction_inialize(PORTD_INDEX,0x1F);                 //0001 1111
            
            ret=seven_seg_write_number(&seven_seg1,((uint8)(sec%10)));
            ret=gpio_pin_write_logic(&seg1_pin_control6,GPIO_LOW); 
            __delay_us(6667);  
            ret=gpio_pin_write_logic(&seg1_pin_control6,GPIO_HIGH);
         }
         
         sec++;
         if(60==sec)
         {  
             sec=0;
             min++;
             
         }
         if(60==min)
         {  
              min=0;
             hours++;
            
         }
         if(25==hours)
         {
             hours=0;
         }
         else
         {
         continue;    
         }
         */
}
/*
lcd_4bit_t lcd_4bit={
  .rs_pin.port=PORTC_INDEX,
  .rs_pin.pin=GPIO_PIN0,
  .rs_pin.direction=GPIO_DIRECTION_OUTPUT,
  .rs_pin.logic=GPIO_LOW,
  
  .en_pin.port=PORTC_INDEX,
  .en_pin.pin=GPIO_PIN1,
  .en_pin.direction=GPIO_DIRECTION_OUTPUT,
  .en_pin.logic=GPIO_LOW,
  
  .data_pins[0].port=PORTC_INDEX,
  .data_pins[0].pin=GPIO_PIN2,
  .data_pins[0].direction=GPIO_DIRECTION_OUTPUT,
  .data_pins[0].logic=GPIO_LOW,
  
  .data_pins[1].port=PORTC_INDEX,
  .data_pins[1].pin=GPIO_PIN3,
  .data_pins[1].direction=GPIO_DIRECTION_OUTPUT,
  .data_pins[1].logic=GPIO_LOW,
  
  .data_pins[2].port=PORTC_INDEX,
  .data_pins[2].pin=GPIO_PIN4,
  .data_pins[2].direction=GPIO_DIRECTION_OUTPUT,
  .data_pins[2].logic=GPIO_LOW,
  
  
  .data_pins[3].port=PORTC_INDEX,
  .data_pins[3].pin=GPIO_PIN5,
  .data_pins[3].direction=GPIO_DIRECTION_OUTPUT,
  .data_pins[3].logic=GPIO_LOW,
  
  
  
};

lcd_8bit_t lcd_8bit={
  .rs_pin.port=PORTC_INDEX,
  .rs_pin.pin=GPIO_PIN6,
  .rs_pin.direction=GPIO_DIRECTION_OUTPUT,
  .rs_pin.logic=GPIO_LOW,
  
  .en_pin.port=PORTC_INDEX,
  .en_pin.pin=GPIO_PIN7,
  .en_pin.direction=GPIO_DIRECTION_OUTPUT,
  .en_pin.logic=GPIO_LOW,
  
  .data_pins[0].port=PORTD_INDEX,
  .data_pins[0].pin=GPIO_PIN0,
  .data_pins[0].direction=GPIO_DIRECTION_OUTPUT,
  .data_pins[0].logic=GPIO_LOW,
  
  .data_pins[1].port=PORTD_INDEX,
  .data_pins[1].pin=GPIO_PIN1,
  .data_pins[1].direction=GPIO_DIRECTION_OUTPUT,
  .data_pins[1].logic=GPIO_LOW,
  
  .data_pins[2].port=PORTD_INDEX,
  .data_pins[2].pin=GPIO_PIN2,
  .data_pins[2].direction=GPIO_DIRECTION_OUTPUT,
  .data_pins[2].logic=GPIO_LOW,
  
  
  .data_pins[3].port=PORTD_INDEX,
  .data_pins[3].pin=GPIO_PIN3,
  .data_pins[3].direction=GPIO_DIRECTION_OUTPUT,
  .data_pins[3].logic=GPIO_LOW,
  
  .data_pins[4].port=PORTD_INDEX,
  .data_pins[4].pin=GPIO_PIN4,
  .data_pins[4].direction=GPIO_DIRECTION_OUTPUT,
  .data_pins[4].logic=GPIO_LOW,
  
  .data_pins[5].port=PORTD_INDEX,
  .data_pins[5].pin=GPIO_PIN5,
  .data_pins[5].direction=GPIO_DIRECTION_OUTPUT,
  .data_pins[5].logic=GPIO_LOW,
  
  .data_pins[6].port=PORTD_INDEX,
  .data_pins[6].pin=GPIO_PIN6,
  .data_pins[6].direction=GPIO_DIRECTION_OUTPUT,
  .data_pins[6].logic=GPIO_LOW,
  
  
  .data_pins[7].port=PORTD_INDEX,
  .data_pins[7].pin=GPIO_PIN7,
  .data_pins[7].direction=GPIO_DIRECTION_OUTPUT,
  .data_pins[7].logic=GPIO_LOW,
  
  
  
};
*/
void lcd_test_number_custom_char_different_pos(void)
{  
    
/*
uint8 counter=20;
uint8 strarr[4];
uint8 customChar1[] = {0x00,0x1C,0x12,0x11,0x08,0x04,0x02,0x01};
uint8 customChar2[] = {0x00,0x07,0x09,0x11,0x02,0x04,0x08,0x10};

     //ret=lcd_8bit_send_char_data(&lcd_8bit,'Y'); 
     //__delay_ms(50);
     //ret=lcd_8bit_send_char_data(&lcd_8bit,'A'); 
     //__delay_ms(50);
     
      ret=lcd_8bit_send_char_data_specific_position(&lcd_8bit,2,3,'A');
     __delay_ms(50);
     ret=lcd_8bit_send_char_data_specific_position(&lcd_8bit,2,4,'S');
     __delay_ms(50);
     
     ret=lcd_8bit_send_string(&lcd_8bit,"Ahmed");     
    
     ret=lcd_8bit_send_string_specific_position(&lcd_8bit,3,3,"YASMMEN");
     
     
     ret=lcd_4bit_send_char_data(&lcd_4bit,'A'); 
     __delay_ms(50);
     ret=lcd_4bit_send_string(&lcd_4bit,"SALAH");
     __delay_ms(50);
     ret=lcd_4bit_send_string_specific_position(&lcd_4bit,4,1,"YASMEEN");
     while(1)
     {   
         ret=lcd_4bit_send_custom_char(&lcd_4bit,2,3,customChar1,1);
         ret=lcd_4bit_send_custom_char(&lcd_4bit,2,4,customChar2,2);
         ret=lcd_8bit_send_custom_char(&lcd_8bit,2,12,customChar1,1);
         ret=lcd_8bit_send_custom_char(&lcd_8bit,2,13,customChar2,2);
        // ret=lcd_4bit_send_char_data_specific_position(&lcd_4bit,3,3,'s');
         
         
         
         ret=lcd_8bit_send_string_specific_position(&lcd_8bit,4,3,"count:");
         
         ret=convert_byte_to_string(counter,strarr);
         ret=lcd_8bit_send_string_specific_position(&lcd_8bit,4,10,strarr);
         counter++;
         __delay_ms(250);
     }

}
 
 */
}



uint8 keypad_value=ZERO_INIT;
void keypad_test_return_value(void)
{
     // ret=keypad_get_value(&keypad1,&keypad_value);
}


void lm35(void)
{ //uint8 lm35_res1_txt[6],lm35_res2_txt[6];
    /*
     void ADC_DEFAULT_INTERRUPT_HANDLER(void)
{   
    
   std_ReturnType ret=E_NOT_OK;
   if(0==lm_req)
   {    
        ret=ADC_GET_RESULT(&adc1,&adc_res1);
        lm_req=1;
   }
   else if(1==lm_req)
   {    
       ret=ADC_GET_RESULT(&adc1,&adc_res2);
       lm_req=0;
   }
}

      ret=lcd_4bit_send_string_specific_position(&lcd_4bit,1,1,"Temp1_readings: ");
     ret=lcd_4bit_send_string_specific_position(&lcd_4bit,2,1,"Temp2_readings: ");
     
     
     while(1)
     {      
       if(0==lm_req)
       {    
           ret=ADC_Select_Channel_Start_Conversion_Interrupt(&adc1 ,ADC_CHANNEL_AN1);
       }
       else if(1==lm_req)
       {    
           ret=ADC_Select_Channel_Start_Conversion_Interrupt(&adc1 ,ADC_CHANNEL_AN9);
       } 
       
      
  */  
      
 //    lm35_res1=adc_res1* ((float32)5000/1024) ;        /*  5000mv (vref)/ 1024 (resolution of ADC)*/
 //       lm35_res1/=10;   /*(every 10mv equal 1 deg c)*/
         
 //      lm35_res2=adc_res2* ((float32)5000/1024) ;        /*  5000mv (vref)/ 1024 (resolution of ADC)*/
 //      lm35_res2/=10;   
    
       /*       
       ret=convert_short_to_string(lm35_res1,lm35_res1_txt) ;
        
       ret=lcd_4bit_send_string_specific_position(&lcd_4bit,1,17,lm35_res1_txt);
       
          
       ret=convert_short_to_string(lm35_res2,lm35_res2_txt) ;
        
       ret=lcd_4bit_send_string_specific_position(&lcd_4bit,2,17,lm35_res2_txt);
       
       if(lm35_res1>20)
       {
           ret=dc_motor_move_left(&dc_motor_1);
       }
       else
       {
           ret=dc_motor_stop(&dc_motor_1);
       }    
       if(lm35_res2>25)
       {
           ret=dc_motor_move_right(&dc_motor_2);
       }
       else
       {
           ret=dc_motor_stop(&dc_motor_2);
       }
       
     }
     
     
     */
}

void ecu_initialize(void)
{
     //__delay_ms(2000);
    
    //ret=led_initialize(&led1);
    ret=led_initialize(&led2);
    //ret=led_initialize(&led3);
    //ret=button_initialize(&btn_high1);
    //ret=button_initialize(&btn_low1);
   // ret=relay_initialize(&relay1);
    //ret=dc_motor_initalize(&dc_motor_1);
    //ret=dc_motor_initalize(&dc_motor_2);
   // ret=seven_seg_initialize(&seven_seg1);
   // ret=gpio_pin_inialize(&seg1_pin_control1);
   // ret=gpio_pin_inialize(&seg1_pin_control2);
   // ret=gpio_pin_inialize(&seg1_pin_control3);
   // ret=gpio_pin_inialize(&seg1_pin_control4);
   // ret=gpio_pin_inialize(&seg1_pin_control5);
   // ret=gpio_pin_inialize(&seg1_pin_control6);
   // ret=keypad_initialize(&keypad1);
   // ret=lcd_4bit_initialize(&lcd_4bit);
   // ret=lcd_8bit_initialize(&lcd_8bit);
}


