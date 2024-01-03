/* 
 * File:   mcal_external_interrupt.c
 * Author: AhmedSalah
 *
 * Created on September 1, 2023, 2:06 PM
 */



#include "mcal_external_interrupt.h"


static std_ReturnType Interrupt_INTX_Enable(const external_interrupt_INTX_t* _INTX);
static std_ReturnType Interrupt_INTX_Disable(const external_interrupt_INTX_t* _INTX);
static std_ReturnType Interrupt_INTX_Edge_init(const external_interrupt_INTX_t* _INTX);
static std_ReturnType Interrupt_INTX_Priority_init(const external_interrupt_INTX_t* _INTX);
static std_ReturnType Interrupt_INTX_Pin_init(const external_interrupt_INTX_t* _INTX);
static std_ReturnType Interrupt_INTX_Handler(const external_interrupt_INTX_t* _INTX);


static std_ReturnType Interrupt_RBX_Enable(const external_interrupt_RBX_t* _RBX);
static std_ReturnType Interrupt_RBX_Disable(const external_interrupt_RBX_t* _RBX);
static std_ReturnType Interrupt_RBX_Priority_init(const external_interrupt_RBX_t* _RBX);
static std_ReturnType Interrupt_RBX_Pin_init(const external_interrupt_RBX_t* _RBX);
static std_ReturnType Interrupt_RBX_Handler(const external_interrupt_RBX_t* _RBX);

static void (*INT0_Interrupt_Handler)(void)=NULL;
static void (*INT1_Interrupt_Handler)(void)=NULL;
static void (*INT2_Interrupt_Handler)(void)=NULL;

static void (*RB4_Interrupt_Handler_HIGH)(void)=NULL;
static void (*RB4_Interrupt_Handler_LOW)(void)=NULL;
static void (*RB5_Interrupt_Handler_HIGH)(void)=NULL;
static void (*RB5_Interrupt_Handler_LOW)(void)=NULL;
static void (*RB6_Interrupt_Handler_HIGH)(void)=NULL;
static void (*RB6_Interrupt_Handler_LOW)(void)=NULL;
static void (*RB7_Interrupt_Handler_HIGH)(void)=NULL;
static void (*RB7_Interrupt_Handler_LOW)(void)=NULL;
/**
 * 
 * @param _INTX
 * @return Status of the function
 *         E_OK: the function executed successfully
 *         E_NOT_OK: the function failed   
 */
std_ReturnType External_Interrupt_INTX_Initialization(const external_interrupt_INTX_t* _INTX)
{
    std_ReturnType ret=E_OK;
    if(NULL== _INTX)
    {
        ret=E_NOT_OK;
    }    
    else
    {
        ret=Interrupt_INTX_Disable(_INTX);
        ret=Interrupt_INTX_Edge_init(_INTX);
        ret=Interrupt_INTX_Pin_init(_INTX);
        /*call back function */
        ret=Interrupt_INTX_Handler(_INTX);
        #if INTERRUPT_PRIORITY_FEATURE == INTERRUPT_PRIORITY_FEAUTURE_ENABLE
            Interrupt_priority_Enable();
            ret=Interrupt_INTX_Priority_init(_INTX);
        #else
            Interrupt_priority_Disable();
        #endif
        ret=Interrupt_INTX_Enable(_INTX);
    }
    return ret;
}
/**
 * 
 * @param _INTX
 * @return Status of the function
 *         E_OK: the function executed successfully
 *         E_NOT_OK: the function failed
 */
std_ReturnType External_Interrupt_INTX_DeInitialization(const external_interrupt_INTX_t* _INTX)
{
    std_ReturnType ret=E_OK;
    if(NULL== _INTX)
    {
        ret=E_NOT_OK;
    }    
    else
    {
        ret=Interrupt_INTX_Disable(_INTX);
    }
    return ret;   
}
/**
 * 
 * @param _RBX
 * @return Status of the function
 *         E_OK: the function executed successfully
 *         E_NOT_OK: the function failed
 */
std_ReturnType External_Interrupt_RBX_Initialization(const external_interrupt_RBX_t* _RBX)
{
    std_ReturnType ret=E_OK;
    if(NULL== _RBX)
    {
        ret=E_NOT_OK;
    }    
    else
    {
        ret=Interrupt_RBX_Disable(_RBX);
        ret=Interrupt_RBX_Pin_init(_RBX);
        /*call back function */
        ret=Interrupt_RBX_Handler(_RBX);
        #if INTERRUPT_PRIORITY_FEATURE == INTERRUPT_PRIORITY_FEAUTURE_ENABLE
        Interrupt_priority_Enable();    
        ret=Interrupt_RBX_Priority_init(_RBX);
        #else
        Interrupt_priority_Disable();
        #endif
        Interrupt_RBX_Enable(_RBX);
    }
    return ret;    
}
/**
 * 
 * @param _RBX
 * @return Status of the function
 *         E_OK: the function executed successfully
 *         E_NOT_OK: the function failed
 */
std_ReturnType External_Interrupt_RBX_DeInitialization(const external_interrupt_RBX_t* _RBX)
{
  std_ReturnType ret=E_OK;
    if(NULL== _RBX)
    {
        ret=E_NOT_OK;
    }    
    else
    {
        Interrupt_RBX_Disable(_RBX);
    }
    return ret;  
}        
/**
 * 
 * @param _INTX
 * @return Status of the function
 *         E_OK: the function executed successfully
 *         E_NOT_OK: the function failed
 */
static std_ReturnType Interrupt_INTX_Enable(const external_interrupt_INTX_t* _INTX)
{
    std_ReturnType ret=E_OK;
    if(NULL== _INTX)
    {
        ret=E_NOT_OK;
    }    
    else
    {
        switch(_INTX->source)
        {    
                case INTERRUPR_EXT_INT0: 
                #if INTERRUPT_PRIORITY_FEATURE == INTERRUPT_PRIORITY_FEAUTURE_DISABLE
                    Interrupt_Global_Enable() ;
                    Interrupt_Peripheral_Enable();         
                #else
                    Interrupt_High_Priority_Enable();
                #endif    
                    Interrupt_INT0_Enable() ;
                    break;
                case INTERRUPR_EXT_INT1: 
                #if INTERRUPT_PRIORITY_FEATURE == INTERRUPT_PRIORITY_FEAUTURE_DISABLE
                    Interrupt_Global_Enable() ;
                    Interrupt_Peripheral_Enable();         
                #else
                    if(INTERRUPT_HIGH_PRIORITY==_INTX->priority)
                    {
                       Interrupt_High_Priority_Enable();
                    }
                    else if(INTERRUPT_LOW_PRIORITY==_INTX->priority)
                    {
                        Interrupt_Low_Priority_Enable();
                    }
                    else { /* NO THING*/}
                    
                  
                #endif   
                    Interrupt_INT1_Enable() ;
                    break;
                case INTERRUPR_EXT_INT2: 
                #if INTERRUPT_PRIORITY_FEATURE == INTERRUPT_PRIORITY_FEAUTURE_DISABLE
                    Interrupt_Global_Enable() ;
                    Interrupt_Peripheral_Enable();         
                #else
                    if(INTERRUPT_HIGH_PRIORITY==_INTX->priority)
                    {
                       Interrupt_High_Priority_Enable();
                    }
                    else if(INTERRUPT_LOW_PRIORITY==_INTX->priority)
                    {
                        Interrupt_Low_Priority_Enable();
                    }
                    else { /* NO THING*/}
                #endif  
                    Interrupt_INT2_Enable() ; 
                    break;
                default: ret=E_NOT_OK;break;
    
        }
    }    
    return ret;
}
/**
 * 
 * @param _INTX
 * @return Status of the function
 *         E_OK: the function executed successfully
 *         E_NOT_OK: the function failed
 */
static std_ReturnType Interrupt_INTX_Disable(const external_interrupt_INTX_t* _INTX)
{
    std_ReturnType ret=E_OK;
    if(NULL== _INTX)
    {
        ret=E_NOT_OK;
    }    
    else
    {
        switch(_INTX->source)
        {
                case INTERRUPR_EXT_INT0: Interrupt_INT0_Disable() ; Interrupt_INT0_Clear_Flag();break;
                case INTERRUPR_EXT_INT1: Interrupt_INT1_Disable() ; Interrupt_INT1_Clear_Flag();break;
                case INTERRUPR_EXT_INT2: Interrupt_INT2_Disable() ; Interrupt_INT2_Clear_Flag();break;
                default: ret=E_NOT_OK;break;
    
        }
    }    
    return ret;
}

/**
 * 
 * @param _INTX
 * @return Status of the function
 *         E_OK: the function executed successfully
 *         E_NOT_OK: the function failed
 */
static std_ReturnType Interrupt_INTX_Edge_init(const external_interrupt_INTX_t* _INTX)
{
    std_ReturnType ret=E_OK;
    if(NULL== _INTX)
    {
        ret=E_NOT_OK;
    }    
    else
    {
         switch(_INTX->source)
         {     
                case INTERRUPR_EXT_INT0:
                    if(INTERRUPT_EXT_RISING_EDGE==_INTX->edge)
                    {
                        Interrupt_INT0_Rising_Edge_Trigger() ;
                    }
                    else if(INTERRUPT_EXT_FALLING_EDGE==_INTX->edge)
                    {
                        Interrupt_INT0_Falling_Edge_Trigger() ;
                    }
                    else { /* NO THING*/}
                    break;
                case INTERRUPR_EXT_INT1:
                    if(INTERRUPT_EXT_RISING_EDGE==_INTX->edge)
                    {
                        Interrupt_INT1_Rising_Edge_Trigger() ;
                    }
                    else if(INTERRUPT_EXT_FALLING_EDGE==_INTX->edge)
                    {
                        Interrupt_INT1_Falling_Edge_Trigger() ;
                    }
                    else { /* NO THING*/}
                    break;
                case INTERRUPR_EXT_INT2: 
                    if(INTERRUPT_EXT_RISING_EDGE==_INTX->edge)
                    {
                        Interrupt_INT2_Rising_Edge_Trigger() ;
                    }
                    else if(INTERRUPT_EXT_FALLING_EDGE==_INTX->edge)
                    {
                        Interrupt_INT2_Falling_Edge_Trigger() ;
                    }
                    else { /* NO THING*/}
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
 * @param _INTX
 * @return Status of the function
 *         E_OK: the function executed successfully
 *         E_NOT_OK: the function failed
 */
#if INTERRUPT_PRIORITY_FEATURE == INTERRUPT_PRIORITY_FEAUTURE_ENABLE
static std_ReturnType Interrupt_INTX_Priority_init(const external_interrupt_INTX_t* _INTX)
{
    std_ReturnType ret=E_OK;
    if(NULL== _INTX)
    {
        ret=E_NOT_OK;
    }    
    else
    {
        switch(_INTX->source)
        {
                case INTERRUPR_EXT_INT0:
                     /* NO THING*/
                    break;
                case INTERRUPR_EXT_INT1:
                    if(INTERRUPT_HIGH_PRIORITY==_INTX->priority)
                    {
                        Interrupt_INT1_High_Priority() ;
                    }
                    else if(INTERRUPT_LOW_PRIORITY==_INTX->priority)
                    {
                        Interrupt_INT1_Low_Priority() ;
                    }
                    else { /* NO THING*/}
                    break;
                case INTERRUPR_EXT_INT2: 
                    if(INTERRUPT_HIGH_PRIORITY==_INTX->priority)
                    {
                        Interrupt_INT2_High_Priority() ;
                    }
                    else if(INTERRUPT_LOW_PRIORITY==_INTX->priority)
                    {
                        Interrupt_INT2_Low_Priority() ;
                    }
                    else { /* NO THING*/}
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
 * @param _INTX
 * @return Status of the function
 *         E_OK: the function executed successfully
 *         E_NOT_OK: the function failed
 */
static std_ReturnType Interrupt_INTX_Pin_init(const external_interrupt_INTX_t* _INTX)
{
    std_ReturnType ret=E_OK;
    if(NULL== _INTX)
    {
        ret=E_NOT_OK;
    }    
    else
    {   
        ret=gpio_pin_direction_inialize(&(_INTX->pin));
    }
    return ret;
}


/**
 * 
 * @param _RBX
 * @return 
 */
static std_ReturnType Interrupt_RBX_Pin_init(const external_interrupt_RBX_t* _RBX)
{
    std_ReturnType ret=E_OK;
    if(NULL== _RBX)
    {
        ret=E_NOT_OK;
    }    
    else
    {   
        ret=gpio_pin_direction_inialize(&(_RBX->pin));
    }
    return ret;
}

/**
 * 
 * @param _RBX
 * @return 
 */
#if INTERRUPT_PRIORITY_FEATURE == INTERRUPT_PRIORITY_FEAUTURE_ENABLE
static std_ReturnType Interrupt_RBX_Priority_init(const external_interrupt_RBX_t* _RBX)
{
    std_ReturnType ret=E_OK;
    if(NULL== _RBX)
    {
        ret=E_NOT_OK;
    }    
    else
    {
                    if(INTERRUPT_HIGH_PRIORITY==_RBX->priority)
                    {
                        Interrupt_RB_Port_ON_Change_High_Priority() ;
                    }
                    else if(INTERRUPT_LOW_PRIORITY==_RBX->priority)
                    {
                        Interrupt_RB_Port_ON_Change_Low_Priority() ;
                    }
                    else { /* NO THING*/}
    }    
    return ret;
}
#endif

/**
 *      
 * @param _RBX
 * @return 
 */
static std_ReturnType Interrupt_RBX_Enable(const external_interrupt_RBX_t* _RBX)                                
{
    std_ReturnType ret=E_OK;
    if(NULL== _RBX)
    {
        ret=E_NOT_OK;
    }    
    else
    {
       #if INTERRUPT_PRIORITY_FEATURE == INTERRUPT_PRIORITY_FEAUTURE_DISABLE
                    Interrupt_Global_Enable() ;
                    Interrupt_Peripheral_Enable();         
                #else
                    if(INTERRUPT_HIGH_PRIORITY==_RBX->priority)
                    {
                        Interrupt_High_Priority_Enable();
                    }
                    else if(INTERRUPT_LOW_PRIORITY==_RBX->priority)
                    {
                       Interrupt_Low_Priority_Enable();
                    }
                    else { /* NO THING*/}
                #endif   
       Interrupt_RB_Port_ON_Change_Enable();
    }    
    return ret;
}

/**
 * 
 * @param _RBX
 * @return 
 */
static std_ReturnType Interrupt_RBX_Disable(const external_interrupt_RBX_t* _RBX)
{
    std_ReturnType ret=E_OK;
    if(NULL== _RBX)
    {
        ret=E_NOT_OK;
    }    
    else
    {
       Interrupt_RB_Port_ON_Change_Disable();
       Interrupt_RB_Port_ON_Change_Flag_Cleared();
    }    
    return ret;
}
/**
 * 
 * @param _INTX
 * @return 
 */
static std_ReturnType Interrupt_INTX_Handler(const external_interrupt_INTX_t* _INTX)
{
    std_ReturnType ret=E_OK;
    if(NULL== _INTX)
    {
        ret=E_NOT_OK;
    }    
    else
    {
        switch(_INTX->source)
        {
                case INTERRUPR_EXT_INT0: INT0_Interrupt_Handler=_INTX->Interrupt_INTX_Handler ;break;
                case INTERRUPR_EXT_INT1: INT1_Interrupt_Handler=_INTX->Interrupt_INTX_Handler ;break;
                case INTERRUPR_EXT_INT2: INT2_Interrupt_Handler=_INTX->Interrupt_INTX_Handler ;break;
                default: ret=E_NOT_OK;break;
    
        }
    }    
   return ret; 
}
/**
 * 
 * @param _RBX
 * @return 
 */
static std_ReturnType Interrupt_RBX_Handler(const external_interrupt_RBX_t* _RBX)
{
    std_ReturnType ret=E_OK;
    if(NULL== _RBX)
    {
        ret=E_NOT_OK;
    }    
    else
    {   
        switch(_RBX->pin.pin)
        {
                case GPIO_PIN4:
                    RB4_Interrupt_Handler_HIGH=_RBX->Interrupt_RBX_Handler_HIGH ; 
                    RB4_Interrupt_Handler_LOW=_RBX->Interrupt_RBX_Handler_LOW  ;
                    break;
                case GPIO_PIN5: 
                    RB5_Interrupt_Handler_LOW=_RBX->Interrupt_RBX_Handler_LOW  ;
                    RB5_Interrupt_Handler_HIGH=_RBX->Interrupt_RBX_Handler_HIGH  ;
                    break;
                case GPIO_PIN6:
                    RB6_Interrupt_Handler_LOW=_RBX->Interrupt_RBX_Handler_LOW  ;
                    RB6_Interrupt_Handler_HIGH=_RBX->Interrupt_RBX_Handler_HIGH  ;
                    break;
                case GPIO_PIN7: 
                    RB7_Interrupt_Handler_LOW=_RBX->Interrupt_RBX_Handler_LOW  ;
                    RB7_Interrupt_Handler_HIGH=_RBX->Interrupt_RBX_Handler_HIGH  ;
                    break;
                default: ret=E_NOT_OK;break;
    
        }
      
    }    
    return ret;
}

void INT0_ISR(void)
{
    /*CLEAR Flag*/
    Interrupt_INT0_Clear_Flag();
    /*some code*/
    
    /*call back function*/
    if(INT0_Interrupt_Handler)  {INT0_Interrupt_Handler();}
}

void INT1_ISR(void)
{
    /*CLEAR Flag*/
    Interrupt_INT1_Clear_Flag();
    /*some code*/
    
    /*call back function*/
    if(INT1_Interrupt_Handler)  {INT1_Interrupt_Handler();}
}

void INT2_ISR(void)
{
    /*CLEAR Flag*/
    Interrupt_INT2_Clear_Flag();
    /*some code*/
    
    /*call back function*/
    if(INT2_Interrupt_Handler)  {INT2_Interrupt_Handler();}
}

void RB4_ISR(uint8 RB_logic_Source)
{
    /*CLEAR Flag*/
    Interrupt_RB_Port_ON_Change_Flag_Cleared();
    /*some code*/
    
    /*call back function*/
    if(GPIO_HIGH==RB_logic_Source)
    {    
    if(RB4_Interrupt_Handler_HIGH)  
    {RB4_Interrupt_Handler_HIGH();}
    }
    else { /*Nothing*/ }
    if(GPIO_LOW==RB_logic_Source)
    {    
    if(RB4_Interrupt_Handler_LOW) 
    {RB4_Interrupt_Handler_LOW();}
    }
    else { /*Nothing*/ }
    
    
}


void RB5_ISR(uint8 RB_logic_Source)
{
    /*CLEAR Flag*/
    Interrupt_RB_Port_ON_Change_Flag_Cleared();
    /*some code*/
    
    /*call back function*/
    if(GPIO_HIGH==RB_logic_Source)
    {    
    if(RB5_Interrupt_Handler_HIGH) 
    {RB5_Interrupt_Handler_HIGH();}
    }
    else { /*Nothing*/ }
    if(GPIO_LOW==RB_logic_Source)
    {    
    if(RB5_Interrupt_Handler_LOW)
    {RB5_Interrupt_Handler_LOW();}
    }
    else { /*Nothing*/ }
}

void RB6_ISR(uint8 RB_logic_Source)
{
    /*CLEAR Flag*/
    Interrupt_RB_Port_ON_Change_Flag_Cleared();
    /*some code*/
    
    /*call back function*/
    if(GPIO_HIGH==RB_logic_Source)
    {    
    if(RB6_Interrupt_Handler_HIGH)
    {RB6_Interrupt_Handler_HIGH();}
    }
    else { /*Nothing*/ }
    if(GPIO_LOW==RB_logic_Source)
    {    
    if(RB6_Interrupt_Handler_LOW) 
    {RB6_Interrupt_Handler_LOW();}
    }
    else { /*Nothing*/ }
}

void RB7_ISR(uint8 RB_logic_Source)
{
    /*CLEAR Flag*/
    Interrupt_RB_Port_ON_Change_Flag_Cleared();
    /*some code*/
    
    /*call back function*/
    if(GPIO_HIGH==RB_logic_Source)
    {    
    if(RB7_Interrupt_Handler_HIGH)
    {RB7_Interrupt_Handler_HIGH();}
    }
    else { /*Nothing*/ }
    if(GPIO_LOW==RB_logic_Source)
    {    
    if(RB7_Interrupt_Handler_LOW)  
    {RB7_Interrupt_Handler_LOW();}
    }
    else { /*Nothing*/ }
}
