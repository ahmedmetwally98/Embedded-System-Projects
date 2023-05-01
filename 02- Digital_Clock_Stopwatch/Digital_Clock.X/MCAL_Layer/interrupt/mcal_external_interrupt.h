/* 
 * File:   mcal_external_interrupt.h
 * Author: ahmed
 *
 * Created on February 16, 2023, 11:18 PM
 */

#ifndef MCAL_EXTERNAL_INTERRUPT_H
#define	MCAL_EXTERNAL_INTERRUPT_H

/* -------------------- Includes -------------------- */
#include "mcal_interrupt_config.h"
#include "mcal_interrupt_manager.h"

/* -------------------- MACRO Declarations -------------------- */

/* -------------------- MACRO Function Declarations -------------------- */

#if (INTERRUPT_EXTERNAL_INTx_FEATURE == INTERRUPT_FEATURE_ENABLE)
/* ----------------------- INT0 MACROS ----------------------- */
/* Disable external interrupt INT0 */
#define EXT_INT0_InterruptDisable()     (INTCONbits.INT0E = 0)
/* Enable external interrupt INT0 */
#define EXT_INT0_InterruptEnable()      (INTCONbits.INT0E = 1)
/* Clear the flag of external interrupt INT0 */
#define EXT_INT0_InterruptFlagClear()   (INTCONbits.INT0F = 0)
/* rise the flag of external interrupt INT0 on Rising edge */
#define EXT_INT0_RisingEdgeSet()        (INTCON2bits.INTEDG0 = 1)
/* rise the flag of external interrupt INT0 on Falling edge */
#define EXT_INT0_FallingEdgeSet()       (INTCON2bits.INTEDG0 = 0)

/* ----------------------- INT1 MACROS ----------------------- */
/* Enable external interrupt INT1 */
#define EXT_INT1_InterruptEnable()      (INTCON3bits.INT1E = 1)
/* Disable external interrupt INT1 */
#define EXT_INT1_InterruptDisable()      (INTCON3bits.INT1E = 0) 
/* Clear the flag of external interrupt INT0 */
#define EXT_INT1_InterruptFlagClear()    (INTCON3bits.INT1F = 0)
/* rise the flag of external interrupt INT1 on Rising edge */
#define EXT_INT1_RisingEdgeSet()         (INTCON2bits.INTEDG1 = 1)
/* rise the flag of external interrupt INT0 on Falling edge */
#define EXT_INT1_FallingEdgeSet()        (INTCON2bits.INTEDG1 = 0)
#if (INTERRUPT_PRIORITY_FEATURE == INTERRUPT_FEATURE_ENABLE)
/* Set External Interrupt INT1 as High Priority */
#define EXT_INT1_HighPrioritySet()       (INTCON3bits.INT1P = 1)
/* Set External Interrupt INT1 as Low Priority */
#define EXT_INT1_LowPrioritySet()       (INTCON3bits.INT1P = 0)
#endif

/* ----------------------- INT2 MACROS ----------------------- */
/* Enable external interrupt INT1 */
#define EXT_INT2_InterruptEnable()       (INTCON3bits.INT2E = 1)
/* Disable external interrupt INT1 */
#define EXT_INT2_InterruptDisable()      (INTCON3bits.INT2E = 0) 
/* Clear the flag of external interrupt INT0 */
#define EXT_INT2_InterruptFlagClear()    (INTCON3bits.INT2F = 0)
/* rise the flag of external interrupt INT1 on Rising edge */
#define EXT_INT2_RisingEdgeSet()         (INTCON2bits.INTEDG2 = 1)
/* rise the flag of external interrupt INT0 on Falling edge */
#define EXT_INT2_FallingEdgeSet()        (INTCON2bits.INTEDG2 = 0)
#if (INTERRUPT_PRIORITY_FEATURE == INTERRUPT_FEATURE_ENABLE)
/* Set External Interrupt INT2 as High Priority */
#define EXT_INT2_HighPrioritySet()       (INTCON3bits.INT2P = 1)
/* Set External Interrupt INT2 as Low Priority */
#define EXT_INT2_LowPrioritySet()        (INTCON3bits.INT2P = 0)
#endif

#endif

#if INTERRUPT_EXTERNAL_OnChange_FEATURE == INTERRUPT_FEATURE_ENABLE
/* Enable on Change Interrupt for PORTB Pins (RP4 : RB7) */
#define EXT_RBx_InterruptEnable()           (INTCONbits.RBIE = 1)
/* Disable on Change Interrupt for PORTB Pins (RP4 : RB7) */
#define EXT_RBx_InterruptDisable()           (INTCONbits.RBIE = 0)
/* Clear the flag of on Change Interrupt for PORTB Pins (RP4 : RB7) */
#define EXT_RBx_InterruptFlagClear()        (INTCONbits.RBIF = 0)
#if (INTERRUPT_PRIORITY_FEATURE == INTERRUPT_FEATURE_ENABLE)
/* Set External Interrupt RBx as High Priority */
#define EXT_RBx_HighPrioritySet()       (INTCON2bits.RBIP = 1)
/* Set External Interrupt RBx as Low Priority */
#define EXT_RBx_LowPrioritySet()        (INTCON2bits.RBIP = 0)
#endif

#endif
/*-------------------- Data Type Declarations -------------------- */
typedef void (*InterruptHandler)(void);

typedef enum {
    INTERRUPT_INTx_RISING_EDGE = 0,
    INTERRUPT_INTx_FALLING_EDGE        
}interrupt_INTx_edge_t;

typedef enum {
    EXT_INT0 = 0,
    EXT_INT1,
    EXT_INT2
}interrupt_INTx_source; 
#if INTERRUPT_EXTERNAL_INTx_FEATURE==INTERRUPT_FEATURE_ENABLE
typedef struct {
    void (*EXT_InterruptHandler)(void);
    pin_config_t INTx_mcu_pin;
    interrupt_INTx_edge_t INTx_edge;
    interrupt_INTx_source INTx_src;
    uint8 INTx_priority;
}interrupt_INTx_t;
#endif
#if INTERRUPT_EXTERNAL_OnChange_FEATURE==INTERRUPT_FEATURE_ENABLE
typedef struct {
    void (*RBx_EXT_InterruptHandler)(uint8);
    pin_config_t mcu_pin;
    uint8 priority;
}interrupt_RBx_t;
#endif
/*-------------------- Software Interfaces Declarations -------------------- */
#if INTERRUPT_EXTERNAL_INTx_FEATURE==INTERRUPT_FEATURE_ENABLE
Std_ReturnType Interrupt_INTx_Init(const interrupt_INTx_t* int_obj);
Std_ReturnType Interrupt_INTx_Deinit(const interrupt_INTx_t* int_obj);

#endif

#if INTERRUPT_EXTERNAL_OnChange_FEATURE==INTERRUPT_FEATURE_ENABLE
Std_ReturnType Interrupt_RBx_Init(const interrupt_RBx_t* int_obj);
Std_ReturnType Interrupt_RBx_Deinit(const interrupt_RBx_t* int_obj);

#endif

#endif	/* MCAL_EXTERNAL_INTERRUPT_H */

