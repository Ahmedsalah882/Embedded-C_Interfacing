/* 
 * File:   mcal_eeprom.h
 * Author: AhmedSalah
 *
 * Created on September 4, 2023, 4:04 AM
 */


#include "mcal_eeprom.h"

static std_ReturnType EEPROM_MeMory_Enable(void);
static std_ReturnType EEPROM_MeMory_Access_Address(const uint16 address);

/**
 * 
 * @param Address
 * @param _data
 * @return status of the function:
 *         E_OK: the function executed successfully
 *         E_NOT_OK: the function failed  
 */
std_ReturnType EEPROM_Memory_Read(const uint16 Address, uint8* _data)
{
    std_ReturnType ret=E_OK;
    if( NULL== _data)
    {
        ret=E_NOT_OK;
    }    
    else
    {
        EEPROM_MeMory_Enable();
        EEPROM_MeMory_Access_Address(Address);
        EEPROM_Memory_Read_Init();
        NOP();
        NOP();
        *_data=EEDATA;
    }
    return ret;
}
/**
 * 
 * @param Address
 * @param _data
 * @return status of the function:
 *         E_OK: the function executed successfully
 *         E_NOT_OK: the function failed
 */
std_ReturnType EEPROM_Memory_Write(const uint16 Address, uint8 _data)
{
        std_ReturnType ret=E_OK;
        uint8 GIE_Status=ZERO_INIT;
        #if INTERRUPT_PRIORITY_FEATURE == INTERRUPT_PRIORITY_FEAUTURE_ENABLE
        GIE_Status=INTCONbits.GIEH;
        #else
        GIE_Status=INTCONbits.GIE;
        #endif
        ret=EEPROM_MeMory_Access_Address(Address);
        EEDATA=_data;
        ret=EEPROM_MeMory_Enable();
        EEPROM_Flash_Write_Enable();
        #if INTERRUPT_PRIORITY_FEATURE == INTERRUPT_PRIORITY_FEAUTURE_ENABLE
        Interrupt_High_Priority_Disable();
        #else
        Interrupt_Global_Disable();
        #endif
        /* initiate the sequence */
        EECON2=0x55;
        EECON2=0xAA;
        EEPROM_Memory_Write_Init();
        /***************************/
        #if INTERRUPT_PRIORITY_FEATURE == INTERRUPT_PRIORITY_FEAUTURE_ENABLE
        INTCONbits.GIEH=GIE_Status;
        #else
        INTCONbits.GIE=GIE_Status;
        #endif
        /* configure the  eeprom interrupt */
        
        while(EECON1bits.WR);
        EEPROM_Flash_Write_Disable();
        
    
    return ret;
}        


static std_ReturnType EEPROM_MeMory_Enable(void)
{
   std_ReturnType ret=E_OK;
   
   EEPROM_Flash_Memory_Enable();
   EEPROM_Memory_Enable();    
    
   return ret;
}

static std_ReturnType EEPROM_MeMory_Access_Address(const uint16 address)
{
   std_ReturnType ret=E_OK;
     
  
    EEADR= (uint8)(address & 0xFF);
    EEADRH= (uint8)((address>>8) & 0x03); 
   
   return ret;
}












