
/* 
 * File:   mcal_interrupt_manager.c
 * Author: ahmed
 *
 * Created on February 16, 2023, 11:18 PM
 */

#include "mcal_interrupt_manager.h"
#include "mcal_internal_interrupt.h"

uint8 flag_RB[4] = {1,1,1,1};

#if (INTERRUPT_PRIORITY_FEATURE == INTERRUPT_FEATURE_ENABLE)
void __interrupt() InterruptManagerHigh(void)
{
#if INTERRUPT_EXTERNAL_INTx_FEATURE == INTERRUPT_FEATURE_ENABLE
    if((INTERRUPT_ENABLE==INTCONbits.INT0E) && (INTERRUPT_OCCUR==INTCONbits.INT0F))
    { 
        INT0_ISR();
    }
#endif
    
#if INTERRUPT_EXTERNAL_OnChange_FEATURE == INTERRUPT_FEATURE_ENABLE
    if ((INTERRUPT_ENABLE == INTCONbits.RBIE) && (INTERRUPT_OCCUR == INTCONbits.RBIF)
            && (PORTBbits.RB4 == 1) && (flag_RB[0]==1))
    {
        flag_RB[0]=0;
        INT_RB4_ISR(1);
    }
    if ((INTERRUPT_ENABLE == INTCONbits.RBIE) && (INTERRUPT_OCCUR == INTCONbits.RBIF)
            && (PORTBbits.RB4 == 0) && (flag_RB[0]==0))
    {
        flag_RB[0]=1;
        INT_RB4_ISR(0);
    }
    if ((INTERRUPT_ENABLE == INTCONbits.RBIE) && (INTERRUPT_OCCUR == INTCONbits.RBIF)
            && (PORTBbits.RB5 == 1) && (flag_RB[1]==1))
    {
        flag_RB[1]=0;
        INT_RB5_ISR(1);
    }
    if ((INTERRUPT_ENABLE == INTCONbits.RBIE) && (INTERRUPT_OCCUR == INTCONbits.RBIF)
            && (PORTBbits.RB5 == 0) && (flag_RB[1]==0))
    {
        flag_RB[1]=1;
        INT_RB5_ISR(0);
    }
    if ((INTERRUPT_ENABLE == INTCONbits.RBIE) && (INTERRUPT_OCCUR == INTCONbits.RBIF)
            && (PORTBbits.RB6 == 1) && (flag_RB[2]==1))
    {
        flag_RB[2]=0;
        INT_RB6_ISR(1);
    }
    if ((INTERRUPT_ENABLE == INTCONbits.RBIE) && (INTERRUPT_OCCUR == INTCONbits.RBIF)
            && (PORTBbits.RB6 == 0) && (flag_RB[2]==0))
    {
        flag_RB[2]=1;
        INT_RB6_ISR(0);
    }
    if ((INTERRUPT_ENABLE == INTCONbits.RBIE) && (INTERRUPT_OCCUR == INTCONbits.RBIF)
            && (PORTBbits.RB7 == 1) && (flag_RB[3]==1))
    {
        flag_RB[3]=0;
        INT_RB7_ISR(1);
    }
    if ((INTERRUPT_ENABLE == INTCONbits.RBIE) && (INTERRUPT_OCCUR == INTCONbits.RBIF)
            && (PORTBbits.RB7 == 0) && (flag_RB[3]==0))
    {
        flag_RB[3]=1;
        INT_RB7_ISR(0);
    }
#endif
}

void __interrupt(low_priority) InterruptManagerLow(void)
{
#if INTERRUPT_EXTERNAL_INTx_FEATURE == INTERRUPT_FEATURE_ENABLE
    if((INTERRUPT_ENABLE==INTCON3bits.INT1E) && (INTERRUPT_OCCUR==INTCON3bits.INT1F))
    {
        INT1_ISR();
    }
    if((INTERRUPT_ENABLE==INTCON3bits.INT2E) && (INTERRUPT_OCCUR==INTCON3bits.INT2F))
    { 
        INT2_ISR();
    }
#endif
    
    
#if TIMER1_INTERRUPT_FEATURE == INTERRUPT_FEATURE_ENABLE
    if((INTERRUPT_ENABLE == PIE1bits.TMR1IE) && (INTERRUPT_OCCUR == PIR1bits.TMR1IF))
    {
        TMR1_ISR();
    }
#endif
    
#if TIMER3_INTERRUPT_FEATURE == INTERRUPT_FEATURE_ENABLE
    if((INTERRUPT_ENABLE == PIE2bits.TMR3IE) && (INTERRUPT_OCCUR == PIR2bits.TMR3IF))
    {
        TMR3_ISR();
    }
#endif
    

}

#else

void __interrupt() InterruptManager(void)
{
#if INTERRUPT_EXTERNAL_INTx_FEATURE == INTERRUPT_FEATURE_ENABLE
    if((INTERRUPT_ENABLE==INTCONbits.INT0E) && (INTERRUPT_OCCUR==INTCONbits.INT0F))
    { 
        INT0_ISR();
    }
    if((INTERRUPT_ENABLE==INTCON3bits.INT1E) && (INTERRUPT_OCCUR==INTCON3bits.INT1F))
    { 
        INT1_ISR();
    }
    if((INTERRUPT_ENABLE==INTCON3bits.INT2E) && (INTERRUPT_OCCUR==INTCON3bits.INT2F))
    {
        INT2_ISR();
    }
#endif
    
#if INTERRUPT_EXTERNAL_OnChange_FEATURE == INTERRUPT_FEATURE_ENABLE
    /* ----------------- On Change External Interrupt ISRs------------------ */
    if ((INTERRUPT_ENABLE == INTCONbits.RBIE) && (INTERRUPT_OCCUR == INTCONbits.RBIF)
            && (PORTBbits.RB4 == 1) && (flag_RB[0]==1))
    {
        flag_RB[0]=0;
        INT_RB4_ISR(1);
    }
    if ((INTERRUPT_ENABLE == INTCONbits.RBIE) && (INTERRUPT_OCCUR == INTCONbits.RBIF)
            && (PORTBbits.RB4 == 0) && (flag_RB[0]==0))
    {
        flag_RB[0]=1;
        INT_RB4_ISR(0);
    }
    if ((INTERRUPT_ENABLE == INTCONbits.RBIE) && (INTERRUPT_OCCUR == INTCONbits.RBIF)
            && (PORTBbits.RB5 == 1) && (flag_RB[1]==1))
    {
        flag_RB[1]=0;
        INT_RB5_ISR(1);
    }
    if ((INTERRUPT_ENABLE == INTCONbits.RBIE) && (INTERRUPT_OCCUR == INTCONbits.RBIF)
            && (PORTBbits.RB5 == 0) && (flag_RB[1]==0))
    {
        flag_RB[1]=1;
        INT_RB5_ISR(0);
    }
    if ((INTERRUPT_ENABLE == INTCONbits.RBIE) && (INTERRUPT_OCCUR == INTCONbits.RBIF)
            && (PORTBbits.RB6 == 1) && (flag_RB[2]==1))
    {
        flag_RB[2]=0;
        INT_RB6_ISR(1);
    }
    if ((INTERRUPT_ENABLE == INTCONbits.RBIE) && (INTERRUPT_OCCUR == INTCONbits.RBIF)
            && (PORTBbits.RB6 == 0) && (flag_RB[2]==0))
    {
        flag_RB[2]=1;
        INT_RB6_ISR(0);
    }
    if ((INTERRUPT_ENABLE == INTCONbits.RBIE) && (INTERRUPT_OCCUR == INTCONbits.RBIF)
            && (PORTBbits.RB7 == 1) && (flag_RB[3]==1))
    {
        flag_RB[3]=0;
        INT_RB7_ISR(1);
    }
    if ((INTERRUPT_ENABLE == INTCONbits.RBIE) && (INTERRUPT_OCCUR == INTCONbits.RBIF)
            && (PORTBbits.RB7 == 0) && (flag_RB[3]==0))
    {
        flag_RB[3]=1;
        INT_RB7_ISR(0);
    }
    /* On Change Interrupt ISRs End*/
#endif

    
#if TIMER1_INTERRUPT_FEATURE == INTERRUPT_FEATURE_ENABLE
    if((INTERRUPT_ENABLE == PIE1bits.TMR1IE) && (INTERRUPT_OCCUR == PIR1bits.TMR1IF))
    {
        TMR1_ISR();
    }
#endif
    
#if TIMER3_INTERRUPT_FEATURE == INTERRUPT_FEATURE_ENABLE
    if((INTERRUPT_ENABLE == PIE2bits.TMR3IE) && (INTERRUPT_OCCUR == PIR2bits.TMR3IF))
    {
        TMR3_ISR();
    }
#endif

}
#endif

