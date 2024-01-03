/* 
 * File:   mcal_interrupt_manager.c
 * Author: AhmedSalah
 *
 * Created on August 31, 2023, 4:03 AM
 */


#include "mcal_interrupt_manager.h"
 
static volatile uint8 RB4_Flag=One_INIT,RB5_Flag=One_INIT,RB6_Flag=One_INIT,RB7_Flag=One_INIT;


#if INTERRUPT_PRIORITY_FEATURE == INTERRUPT_PRIORITY_FEAUTURE_ENABLE
void __interrupt() Interrupt_High_Priority(void)
{
    if((INTERRUPT_EXTERNAL_FEATURE_ENABLE==INTCONbits.INT0E) && (INTERRUPT_OCCUR==INTCONbits.INT0F))
    {
        INT0_ISR();
    }    
    else{/* Nothing */}
    if((INTERRUPT_EXTERNAL_FEATURE_ENABLE==INTCON3bits.INT1E) && (INTERRUPT_OCCUR==INTCON3bits.INT1F))
    {
        INT1_ISR();
    }    
    else{/* Nothing */}
    
    
    
}


void __interrupt(low_priority) Interrupt_Low_Priority(void)
{
    
    if((INTERRUPT_EXTERNAL_FEATURE_ENABLE==INTCON3bits.INT2E) && (INTERRUPT_OCCUR==INTCON3bits.INT2F))
    {
        INT2_ISR();
    }    
    else{/* Nothing */}
    
}

#else
void __interrupt() Interrupt_Manager(void)
{
    if((INTERRUPT_EXTERNAL_FEATURE_ENABLE==INTCONbits.INT0E) && (INTERRUPT_OCCUR==INTCONbits.INT0F))
    {
        INT0_ISR();
    }    
    else{/* Nothing */}
    if((INTERRUPT_EXTERNAL_FEATURE_ENABLE==INTCON3bits.INT1E) && (INTERRUPT_OCCUR==INTCON3bits.INT1F))
    {
        INT1_ISR();
    }
    else{/* Nothing */}
    if((INTERRUPT_EXTERNAL_FEATURE_ENABLE==INTCON3bits.INT2E) && (INTERRUPT_OCCUR==INTCON3bits.INT2F))
    {
        INT2_ISR(); 
    }    
    else{/* Nothing */}
    
    /************************ PORTB RB4 ON Change Interrupt Start*********************************/
    if((INTERRUPT_EXTERNAL_FEATURE_ENABLE==INTCONbits.RBIE) && (INTERRUPT_OCCUR==INTCONbits.RBIF)
            && (PORTBbits.RB4==GPIO_HIGH) &&(One_INIT==RB4_Flag))
    {
        RB4_Flag=ZERO_INIT;
        RB4_ISR(GPIO_HIGH);
    }    
    else{/* Nothing */}
    if((INTERRUPT_EXTERNAL_FEATURE_ENABLE==INTCONbits.RBIE) && (INTERRUPT_OCCUR==INTCONbits.RBIF)
            && (PORTBbits.RB4==GPIO_LOW)&&(ZERO_INIT==RB4_Flag))
    {
        RB4_Flag=One_INIT;
        RB4_ISR(GPIO_LOW);
    }    
    else{/* Nothing */}
    /************************ PORTB RB4 ON Change Interrupt End*********************************/
    /************************ PORTB RB5 ON Change Interrupt Start*********************************/
    if((INTERRUPT_EXTERNAL_FEATURE_ENABLE==INTCONbits.RBIE) && (INTERRUPT_OCCUR==INTCONbits.RBIF)
            && (PORTBbits.RB5==GPIO_HIGH)&&(One_INIT==RB5_Flag))
    {
        RB5_Flag=ZERO_INIT;
        RB5_ISR(GPIO_HIGH);
    }    
    else{/* Nothing */}
    if((INTERRUPT_EXTERNAL_FEATURE_ENABLE==INTCONbits.RBIE) && (INTERRUPT_OCCUR==INTCONbits.RBIF)
            && (PORTBbits.RB5==GPIO_LOW)&&(ZERO_INIT==RB5_Flag))
    {
        RB5_Flag=One_INIT;
        RB5_ISR(GPIO_LOW);
    }    
    else{/* Nothing */}
    /************************ PORTB RB5 ON Change Interrupt End*********************************/
    /************************ PORTB RB6 ON Change Interrupt Start*********************************/
    if((INTERRUPT_EXTERNAL_FEATURE_ENABLE==INTCONbits.RBIE) && (INTERRUPT_OCCUR==INTCONbits.RBIF)
            && (PORTBbits.RB6==GPIO_HIGH)&&(One_INIT==RB6_Flag))
    {
        RB6_Flag=ZERO_INIT;
        RB6_ISR(GPIO_HIGH);
    }    
    else{/* Nothing */}
    if((INTERRUPT_EXTERNAL_FEATURE_ENABLE==INTCONbits.RBIE) && (INTERRUPT_OCCUR==INTCONbits.RBIF)
            && (PORTBbits.RB6==GPIO_LOW)&&(ZERO_INIT==RB6_Flag))
    {
        RB6_Flag=One_INIT;
        RB6_ISR(GPIO_LOW);
    }    
    else{/* Nothing */}
    /************************ PORTB RB6 ON Change Interrupt End*********************************/
    /************************ PORTB RB7 ON Change Interrupt Start*********************************/
    if((INTERRUPT_EXTERNAL_FEATURE_ENABLE==INTCONbits.RBIE) && (INTERRUPT_OCCUR==INTCONbits.RBIF) 
            && (PORTBbits.RB7==GPIO_HIGH)&&(One_INIT==RB7_Flag))
    {
        RB7_Flag=ZERO_INIT;
        RB7_ISR(GPIO_HIGH);
    }    
    else{/* Nothing */}
    if((INTERRUPT_EXTERNAL_FEATURE_ENABLE==INTCONbits.RBIE) && (INTERRUPT_OCCUR==INTCONbits.RBIF)
            && (PORTBbits.RB7==GPIO_LOW)&&(ZERO_INIT==RB7_Flag))
    {
        RB7_Flag=One_INIT;
        RB7_ISR(GPIO_LOW);
    }    
    else{/* Nothing */}
    /************************ PORTB RB7 ON Change Interrupt End*********************************/
    
    /************************ ADC Interrupt Start*********************************/
    
    if((ADC_INTERRUPT_FEATURE_ENABLE==PIE1bits.ADIE) && (INTERRUPT_OCCUR==PIR1bits.ADIF))
    {
        ADC_ISR();   
    }    
    else{/* Nothing */}
    /************************ ADC Interrupt End*********************************/
    /************************ Timer0 Interrupt Start*********************************/
    
    if((TIMER0_INTERRUPT_FEATURE_ENABLE==T0CONbits.TMR0ON) && (INTERRUPT_OCCUR==INTCONbits.TMR0IF))
    {
        Timer0_ISR();   
    }    
    else{/* Nothing */}
    /************************ Timer0 Interrupt End*********************************/
    /************************ Timer1 Interrupt Start*********************************/
    
    if((TIMER1_INTERRUPT_FEATURE_ENABLE==PIE1bits.TMR1IE) && (INTERRUPT_OCCUR==PIR1bits.TMR1IF))
    {
        Timer1_ISR();   
    }    
    else{/* Nothing */}
    /************************ Timer1 Interrupt End*********************************/
    /************************ Timer2 Interrupt Start*********************************/
    
    if((TIMER1_INTERRUPT_FEATURE_ENABLE==PIE1bits.TMR2IE) && (INTERRUPT_OCCUR==PIR1bits.TMR2IF))
    {
        Timer2_ISR();   
    }    
    else{/* Nothing */}
    /************************ Timer1 Interrupt End*********************************/
    /************************ Timer3 Interrupt Start*********************************/
    
    if((TIMER3_INTERRUPT_FEATURE_ENABLE==PIE2bits.TMR3IE) && (INTERRUPT_OCCUR==PIR2bits.TMR3IF))
    {
        Timer3_ISR();   
    }    
    else{/* Nothing */}
    /************************ Timer3 Interrupt End*********************************/
    /************************ CCP1 Interrupt Start*********************************/
    
    if((CCP1_INTERRUPT_FEATURE==PIE1bits.CCP1IE) && (INTERRUPT_OCCUR==PIR1bits.CCP1IF))
    {
        CCP1_ISR();   
    }    
    else{/* Nothing */}
    /************************ CCP2 Interrupt End*********************************/
    if((CCP2_INTERRUPT_FEATURE==PIE2bits.CCP2IE) && (INTERRUPT_OCCUR==PIR2bits.CCP2IF))
    {
       // CCP2_ISR();   
    }    
    else{/* Nothing */}
    /************************ CCP2 Interrupt End*********************************/
}

#endif