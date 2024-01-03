/* 
 * File:   mcal_eeprom.h
 * Author: AhmedSalah
 *
 * Created on September 4, 2023, 4:04 AM
 */

#ifndef MCAL_EEPROM_H
#define	MCAL_EEPROM_H

/* Section: Includes */
#include "../mcal_std_types.h"
#include "../Interrupt/mcal_interrupt_config.h"
#include "../Interrupt/mcal_internal_interrupt.h"
#include "pic18f4620.h"

/* Section: Macro Definitions */

#define EEPROM_FLASH_MEMORY_FEATURE                                     EEPROM_MEMORY_FEATURE_ENABLE
#define FLASH_MEMORY_FEATURE_ENABLE                                     0x00
#define EEPROM_MEMORY_FEATURE_ENABLE                                    0x01                




/* Section: Macro Functions */
#define Configuration_Bits_Enable()                                     (EECON1bits.CFGS=1)
#define EEPROM_Flash_Memory_Enable()                                    (EECON1bits.CFGS=0)    

#define EEPROM_Flash_Write_Enable()                                     (EECON1bits.WREN=1)               
#define EEPROM_Flash_Write_Disable()                                    (EECON1bits.WREN=0)



#if EEPROM_FLASH_MEMORY_FEATURE == EEPROM_MEMORY_FEATURE_ENABLE
    
#define EEPROM_Memory_Enable()                                          (EECON1bits.EEPGD=0)                
#define EEPROM_Memory_Write_Init()                                      (EECON1bits.WR=1)
#define EEPROM_Memory_Read_Init()                                       (EECON1bits.RD=1) 

#else 
#define Flash_Memory_Enable()                                           (EECON1bits.EEPGD=1)

#endif


/* Section: Data Type Declarations */


/* Section: Function Prototypes */
std_ReturnType EEPROM_Memory_Read(const uint16 Address, uint8* _data);
std_ReturnType EEPROM_Memory_Write(const uint16 Address, uint8 _data);








#endif	/* MCAL_EEPROM_H */

