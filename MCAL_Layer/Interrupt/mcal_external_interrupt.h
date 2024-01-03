/* 
 * File:   mcal_external_interrupt.h
 * Author: AhmedSalah
 *
 * Created on September 1, 2023, 2:06 PM
 */

#ifndef MCAL_EXTERNAL_INTERRUPT_H
#define	MCAL_EXTERNAL_INTERRUPT_H

/* Section: Includes */
#include "mcal_interrupt_config.h"


/* Section: Macro Definitions */

/* Section: Macro Functions */
#if INTERRUPT_EXTERNAL_FEATURE == INTERRUPT_EXTERNAL_FEATURE_ENABLE
/****************************************INT0 Interrupt****************************/
/* Control External Interrupt INT0*/
#define Interrupt_INT0_Enable()                                 (INTCONbits.INT0E=1)        
#define Interrupt_INT0_Disable()                                (INTCONbits.INT0E=0)
/*Clear External Interrupt INT0 Flag*/
#define Interrupt_INT0_Clear_Flag()                             (INTCONbits.INT0F=0)

/*Trigger External INT0  ON Rising Edge*/
#define Interrupt_INT0_Rising_Edge_Trigger()                      (INTCON2bits.INTEDG0=1)
/*Trigger External INT0  ON Falling Edge*/
#define Interrupt_INT0_Falling_Edge_Trigger()                     (INTCON2bits.INTEDG0=0)

/****************************************INT1 Interrupt****************************/
/*Control External Interrupt INT1*/
#define Interrupt_INT1_Enable()                                 (INTCON3bits.INT1E=1)
#define Interrupt_INT1_Disable()                                (INTCON3bits.INT1E=0)

/*Clear External Interrupt INT1 Flag*/
#define Interrupt_INT1_Clear_Flag()                             (INTCON3bits.INT1F=0)

/*Trigger External INT1  ON Rising Edge*/
#define Interrupt_INT1_Rising_Edge_Trigger()                    (INTCON2bits.INTEDG1=1)
/*Trigger External INT1  ON Falling Edge*/
#define Interrupt_INT1_Falling_Edge_Trigger()                    (INTCON2bits.INTEDG1=0)

/****************************************INT2 Interrupt****************************/
/*Control External Interrupt INT2*/
#define Interrupt_INT2_Enable()                                 (INTCON3bits.INT2E=1)
#define Interrupt_INT2_Disable()                                (INTCON3bits.INT2E=0)

/*Clear External Interrupt INT2 Flag*/
#define Interrupt_INT2_Clear_Flag()                             (INTCON3bits.INT2F=0)

/*Trigger External INT2  ON Rising Edge*/
#define Interrupt_INT2_Rising_Edge_Trigger()                    (INTCON2bits.INTEDG2=1) 
/*Trigger External INT2  ON Falling Edge*/
#define Interrupt_INT2_Falling_Edge_Trigger()                    (INTCON2bits.INTEDG2=1)

/****************************************RB PORT ON CHANGE Interrupt****************************/
/*Control RB Port ON change Interrupt */
#define Interrupt_RB_Port_ON_Change_Enable()                    (INTCONbits.RBIE=1)
#define Interrupt_RB_Port_ON_Change_Disable()                   (INTCONbits.RBIE=0)

/*Clear RB Port ON change Interrupt Flag */
#define Interrupt_RB_Port_ON_Change_Flag_Cleared()              (INTCONbits.RBIF=0)


/*Control PortB PULLUP Feature*/
#define Interrupt_RB_Port_PULLUP_Disable()                      (INTCON2bits.nRBPU=1)
#define Interrupt_RB_Port_PULLUP_Enable()                       (INTCON2bits.nRBPU=0)       


#if INTERRUPT_PRIORITY_FEATURE == INTERRUPT_PRIORITY_FEAUTURE_ENABLE
/****************************************INT1 Interrupt Priority****************************/
/*High Priority Interrupt INT1 Feature Enabled */
#define Interrupt_INT1_High_Priority()                          (INTCON3bits.INT1P=1)             
/*Low Priority Interrupt INT1 Feature Enabled */
#define Interrupt_INT1_Low_Priority()                           (INTCON3bits.INT1P=0)

/****************************************INT2 Interrupt Priority****************************/
/*High Priority Interrupt INT2 Feature Enabled */
#define Interrupt_INT2_High_Priority()                          (INTCON3bits.INT2P=1)           
/*Low Priority Interrupt INT2 Feature Enabled */
#define Interrupt_INT2_Low_Priority()                           (INTCON3bits.INT2P=0)

/****************************************RB PORT ON CHANGE Interrupt Priority****************************/
/*High Priority Interrupt RB Port ON Change Feature Enabled */
#define Interrupt_RB_Port_ON_Change_High_Priority()             (INTCON2bits.RBIP=1)
/*Low Priority  Interrupt RB Port ON Change Feature Enabled */
#define Interrupt_RB_Port_ON_Change_Low_Priority()              (INTCON2bits.RBIP=0)



#endif

#endif


/* Section: Data Type Declarations */
typedef enum{
    INTERRUPR_EXT_INT0,
    INTERRUPR_EXT_INT1,
    INTERRUPR_EXT_INT2        
}interrupt_ext_src_t;

typedef enum{
    INTERRUPT_EXT_FALLING_EDGE,
    INTERRUPT_EXT_RISING_EDGE,            
}interrupt_ext_edge_t;

typedef struct{
void(*Interrupt_INTX_Handler)(void);   
pin_config_t pin;    
interrupt_ext_src_t source;
interrupt_ext_edge_t edge;
interrupt_priority_t priority;
}external_interrupt_INTX_t;


typedef struct{
void(*Interrupt_RBX_Handler_HIGH)(void);
void(*Interrupt_RBX_Handler_LOW)(void);
pin_config_t pin;    
interrupt_priority_t priority;    
}external_interrupt_RBX_t;

/* Section: Function Prototypes */
std_ReturnType External_Interrupt_INTX_Initialization(const external_interrupt_INTX_t* _INTX);
std_ReturnType External_Interrupt_INTX_DeInitialization(const external_interrupt_INTX_t* _INTX);
std_ReturnType External_Interrupt_RBX_Initialization(const external_interrupt_RBX_t* _RBX);
std_ReturnType External_Interrupt_RBX_DeInitialization(const external_interrupt_RBX_t* _RBX);



void INT0_ISR(void);
void INT1_ISR(void);
void INT2_ISR(void);

void RB4_ISR(uint8 RB_logic_Source);
void RB5_ISR(uint8 RB_logic_Source);
void RB6_ISR(uint8 RB_logic_Source);
void RB7_ISR(uint8 RB_logic_Source);



#endif	/* MCAL_EXTERNAL_INTERRUPT_H */

