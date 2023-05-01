/* 
 * File:   mcal_external_interrupt.c
 * Author: ahmed
 *
 * Created on February 16, 2023, 11:18 PM
 */


#include "mcal_external_interrupt.h"

/*--------------------- Global Variables Declarations/Definitions --------------------- */
#if INTERRUPT_EXTERNAL_INTx_FEATURE==INTERRUPT_FEATURE_ENABLE
static InterruptHandler INT0_InterruptHandler = NULL;
static InterruptHandler INT1_InterruptHandler = NULL;
static InterruptHandler INT2_InterruptHandler = NULL;
#endif
#if INTERRUPT_EXTERNAL_OnChange_FEATURE==INTERRUPT_FEATURE_ENABLE
static void (*RB4_InterruptHandler)(uint8) = NULL;
static void (*RB5_InterruptHandler)(uint8) = NULL;
static void (*RB6_InterruptHandler)(uint8) = NULL;
static void (*RB7_InterruptHandler)(uint8) = NULL;
#endif

/* --------------------- Helper Functions Declarations ------------------------ */
#if INTERRUPT_EXTERNAL_INTx_FEATURE==INTERRUPT_FEATURE_ENABLE
static Std_ReturnType Interrupt_INTx_Enable(const interrupt_INTx_t* int_obj);
static Std_ReturnType Interrupt_INTx_Disable(const interrupt_INTx_t* int_obj);
static Std_ReturnType Interrupt_INTx_Priority_init(const interrupt_INTx_t* int_obj);
static Std_ReturnType Interrupt_INTx_Edge_init(const interrupt_INTx_t* int_obj);
static Std_ReturnType Interrupt_INTx_Pin_init(const interrupt_INTx_t* int_obj);
static Std_ReturnType Interrupt_INTx_Clear_Flag(const interrupt_INTx_t* int_obj);
#endif
/* --------------------- Peripheral SW Interfaces Declarations ------------------------ */
#if INTERRUPT_EXTERNAL_OnChange_FEATURE==INTERRUPT_FEATURE_ENABLE
static Std_ReturnType Interrupt_RBx_Enable(const interrupt_RBx_t* int_obj);
static Std_ReturnType Interrupt_RBx_Disable(const interrupt_RBx_t* int_obj);
static Std_ReturnType Interrupt_RBx_Priority_init(const interrupt_RBx_t* int_obj);
static Std_ReturnType Interrupt_RBx_Pin_init(const interrupt_RBx_t* int_obj);
#endif

/* --------------------- Peripheral SW Interfaces Definitions ------------------------*/
#if INTERRUPT_EXTERNAL_INTx_FEATURE==INTERRUPT_FEATURE_ENABLE 
/**
 * To enable any module there are few steps:
 * 1- Disable module   
 * 2- configure the module
 * 3- Enable the module
 */
Std_ReturnType Interrupt_INTx_Init(const interrupt_INTx_t* int_obj) {
    /** Function Document
     * 
     * @param int_obj
     * @return 
     */
    Std_ReturnType ret = E_NOT_OK;
    if (NULL == int_obj) {
        ret = E_NOT_OK;
    } else {
        /* Disable the External Interrupt */
        ret = Interrupt_INTx_Disable(int_obj);
        /* Clear Interrupt Flag: External Interrupt Didn't occur */
        ret = Interrupt_INTx_Clear_Flag(int_obj);
        /* Configure External Interrupt Edge */
        ret = Interrupt_INTx_Edge_init(int_obj);
#if (INTERRUPT_PRIORITY_FEATURE == INTERRUPT_FEATURE_ENABLE)
        /* Configure External Interrupt Priority */
        ret = Interrupt_INTx_Priority_init(int_obj);
#endif
        /* Configure External Interrupt I/O Pin */
        ret = Interrupt_INTx_Pin_init(int_obj);
        /* Enable the External Interrupt */
        ret = Interrupt_INTx_Enable(int_obj);
    }
    return ret;
}
Std_ReturnType Interrupt_INTx_Deinit(const interrupt_INTx_t* int_obj) {
    /** Function Document
     * 
     * @param int_obj
     * @return 
     */
    Std_ReturnType ret = E_NOT_OK;
    if (NULL == int_obj) {
        ret = E_NOT_OK;
    } else {
        /* Disable the intended interrupt */
        ret = Interrupt_INTx_Disable(int_obj);
    }
    return ret;
}

void INT0_ISR(void) {
    /* The INT0 External Interrupt Occurred. (flag must be cleared in software) */
    EXT_INT0_InterruptFlagClear();
    /* ISR code */

    /* Application CallBack function gets called every time this ISR executes */
    if (NULL != INT0_InterruptHandler) {
        INT0_InterruptHandler();
    } else {
        /*nothing*/
    }
}

void INT1_ISR(void) {
    /* The INT1 External Interrupt Occurred. (flag must be cleared in software) */
    EXT_INT1_InterruptFlagClear();
    /* ISR code */

    /* Application CallBack function gets called every time this ISR executes */
    if (NULL != INT1_InterruptHandler) {
        INT1_InterruptHandler();
    } else {
        /*nothing*/
    }
    
}

void INT2_ISR(void) {
    /* The INT2 External Interrupt Occurred. (flag must be cleared in software) */
    EXT_INT2_InterruptFlagClear();
    /* ISR code */

    /* Application CallBack function gets called every time this ISR executes */
    if (NULL != INT2_InterruptHandler) {
        INT2_InterruptHandler();
    } else {
        /*nothing*/
    }
}
#endif

#if INTERRUPT_EXTERNAL_OnChange_FEATURE==INTERRUPT_FEATURE_ENABLE
Std_ReturnType Interrupt_RBx_Init(const interrupt_RBx_t* int_obj) {
    /** Function Document
     * 
     * @param int_obj
     * @return 
     */
    Std_ReturnType ret = E_NOT_OK;
    if (NULL == int_obj) {
        ret = E_NOT_OK;
    } else {
        /* Disable on Change Interrupt for PORTB Pins (RP4 : RB7) */
        EXT_RBx_InterruptDisable();
        /* Configure MCU PORTB PINs */
        Interrupt_RBx_Pin_init(int_obj);
        /* Configure priority feature for External on change interrupt */
#if (INTERRUPT_PRIORITY_FEATURE == INTERRUPT_FEATURE_ENABLE)
        Interrupt_RBx_Priority_init(int_obj);
#endif
        /* Clear the flag of on Change Interrupt for PORTB Pins (RP4 : RB7) */
        EXT_RBx_InterruptFlagClear();
        /* Enable on Change Interrupt for PORTB Pins (RP4 : RB7) */
        Interrupt_RBx_Enable(int_obj);
    }
    return ret;
}

Std_ReturnType Interrupt_RBx_Deinit(const interrupt_RBx_t* int_obj) {
    /** Function Document
     * 
     * @param int_obj
     * @return 
     */
    Std_ReturnType ret = E_NOT_OK;
    if (NULL == int_obj) {
        ret = E_NOT_OK;
    } else {
        EXT_RBx_InterruptDisable();
    }
    return ret;
}

void INT_RB4_ISR(uint8 pin_status)
{
    /* The On Change External Interrupt Occurred. (flag must be cleared in software) */
    EXT_RBx_InterruptFlagClear();
    /* ISR code */

    /* Application CallBack function gets called every time this ISR executes */
    if (NULL != RB4_InterruptHandler) {
        RB4_InterruptHandler(pin_status);
    }
    
}
void INT_RB5_ISR(uint8 pin_status)
{
    /* The On Change External Interrupt Occurred. (flag must be cleared in software) */
    EXT_RBx_InterruptFlagClear();
    /* ISR code */

    /* Application CallBack function gets called every time this ISR executes */
    if (NULL != RB5_InterruptHandler) {
        RB5_InterruptHandler(pin_status);
    }
}
void INT_RB6_ISR(uint8 pin_status)
{
    /* The On Change External Interrupt Occurred. (flag must be cleared in software) */
    EXT_RBx_InterruptFlagClear();
    /* ISR code */

    /* Application CallBack function gets called every time this ISR executes */
    if (NULL != RB6_InterruptHandler) {
        RB6_InterruptHandler(pin_status);
    }
}
void INT_RB7_ISR(uint8 pin_status)
{
    /* The On Change External Interrupt Occurred. (flag must be cleared in software) */
    EXT_RBx_InterruptFlagClear();
    /* ISR code */

    /* Application CallBack function gets called every time this ISR executes */
    if (NULL != RB7_InterruptHandler) {
        RB7_InterruptHandler(pin_status);
    }
}
#endif
/* ---------------------- Helper Functions Section -----------------------*/
#if INTERRUPT_EXTERNAL_INTx_FEATURE==INTERRUPT_FEATURE_ENABLE 
static Std_ReturnType Interrupt_INTx_Enable(const interrupt_INTx_t* int_obj) {
    Std_ReturnType ret = E_NOT_OK;
    if (NULL == int_obj) {
        ret = E_NOT_OK;
    } else {
        ret = E_OK;
        switch (int_obj->INTx_src) {
            case EXT_INT0:
                INTERRUPT_GlobalInterruptEnable();
                EXT_INT0_InterruptEnable();
                break;
            case EXT_INT1:
                INTERRUPT_GlobalInterruptEnable();
                EXT_INT1_InterruptEnable();
                break;
            case EXT_INT2:
                INTERRUPT_GlobalInterruptEnable();
                EXT_INT2_InterruptEnable();
                break;
            default: ret = E_NOT_OK;
                break;
        }
    }
    return ret;
}

static Std_ReturnType Interrupt_INTx_Disable(const interrupt_INTx_t* int_obj) {
    Std_ReturnType ret = E_NOT_OK;
    if (NULL == int_obj) {
        ret = E_NOT_OK;
    } else {
        ret = E_OK;
        switch (int_obj->INTx_src) {
            case EXT_INT0:
                EXT_INT0_InterruptDisable();
                break;
            case EXT_INT1:
                EXT_INT1_InterruptDisable();
                break;
            case EXT_INT2:
                EXT_INT2_InterruptDisable();
                break;
            default: ret = E_NOT_OK;
                break;
        }
    }
    return ret;
}

#if (INTERRUPT_PRIORITY_FEATURE == INTERRUPT_FEATURE_ENABLE)
static Std_ReturnType Interrupt_INTx_Priority_init(const interrupt_INTx_t* int_obj) {
    Std_ReturnType ret = E_NOT_OK;
    if (NULL == int_obj) {
        ret = E_NOT_OK;
    } else {
        ret = E_OK;
        switch (int_obj->INTx_src) {
                // INT0 has High Priority by default and can't be changed
            case EXT_INT1:
                INTERRUPT_PriorityLevelsEnable();
                if (LOW_PRIORITY == int_obj->INTx_priority) {
                    INTERRUPT_GlobalInterruptLowEnable();
                    EXT_INT1_LowPrioritySet();
                } else if (HIGH_PRIORITY == int_obj->INTx_priority) {
                    INTERRUPT_GlobalInterruptHighEnable();
                    EXT_INT1_HighPrioritySet();
                } else {
                    ret = E_NOT_OK;
                }
                break;
            case EXT_INT2:
                INTERRUPT_PriorityLevelsEnable();
                if (LOW_PRIORITY == int_obj->INTx_priority) {
                    INTERRUPT_GlobalInterruptLowEnable();
                    EXT_INT2_LowPrioritySet();
                } else if (HIGH_PRIORITY == int_obj->INTx_priority) {
                    INTERRUPT_GlobalInterruptHighEnable();
                    EXT_INT2_HighPrioritySet();
                } else {
                    ret = E_NOT_OK;
                }
                break;
            default: ret = E_NOT_OK;
                break;
        }
    }
    return ret;
}
#endif

static Std_ReturnType Interrupt_INTx_Edge_init(const interrupt_INTx_t* int_obj) {
    Std_ReturnType ret = E_NOT_OK;
    if (NULL == int_obj) {
        ret = E_NOT_OK;
    } else {
        ret = E_OK;
        switch (int_obj->INTx_src) {
            case EXT_INT0:
                if (INTERRUPT_INTx_RISING_EDGE == int_obj->INTx_edge) {
                    EXT_INT0_RisingEdgeSet();
                } else if (INTERRUPT_INTx_FALLING_EDGE == int_obj->INTx_edge) {
                    EXT_INT0_FallingEdgeSet();
                } else {
                    ret = E_NOT_OK;
                }
                break;
            case EXT_INT1:
                if (INTERRUPT_INTx_RISING_EDGE == int_obj->INTx_edge) {
                    EXT_INT1_RisingEdgeSet();
                } else if (INTERRUPT_INTx_FALLING_EDGE == int_obj->INTx_edge) {
                    EXT_INT1_FallingEdgeSet();
                } else {
                    ret = E_NOT_OK;
                }
                break;
            case EXT_INT2:
                if (INTERRUPT_INTx_RISING_EDGE == int_obj->INTx_edge) {
                    EXT_INT2_RisingEdgeSet();
                } else if (INTERRUPT_INTx_FALLING_EDGE == int_obj->INTx_edge) {
                    EXT_INT2_FallingEdgeSet();
                } else {
                    ret = E_NOT_OK;
                }
                break;
            default:
                break;
        }
    }
    return ret;
}

static Std_ReturnType Interrupt_INTx_Pin_init(const interrupt_INTx_t* int_obj) {
    Std_ReturnType ret = E_NOT_OK;
    if (NULL == int_obj) {
        ret = E_NOT_OK;
    } else {
        // Initialize pin directions
        ret = GPIO_pin_direction_initialize(&(int_obj->INTx_mcu_pin));
        // Define interrupt handler for INTx on change interrupt 
        switch (int_obj->INTx_src) {
            case EXT_INT0:
                INT0_InterruptHandler = int_obj->EXT_InterruptHandler;
                break;
            case EXT_INT1:
                INT1_InterruptHandler = int_obj->EXT_InterruptHandler;
                break;
            case EXT_INT2:
                INT2_InterruptHandler = int_obj->EXT_InterruptHandler;
                break;
        }
    }
    return ret;
}

static Std_ReturnType Interrupt_INTx_Clear_Flag(const interrupt_INTx_t* int_obj) {
    Std_ReturnType ret = E_NOT_OK;
    if (NULL == int_obj) {
        ret = E_NOT_OK;
    } else {
        ret = E_OK;
        switch (int_obj->INTx_src) {
            case EXT_INT0:
                EXT_INT0_InterruptFlagClear();
                break;
            case EXT_INT1:
                EXT_INT1_InterruptFlagClear();
                break;
            case EXT_INT2:
                EXT_INT2_InterruptFlagClear();
                break;
            default: ret = E_NOT_OK;
                break;
        }
    }
    return ret;
}
#endif

#if INTERRUPT_EXTERNAL_OnChange_FEATURE==INTERRUPT_FEATURE_ENABLE
static Std_ReturnType Interrupt_RBx_Enable(const interrupt_RBx_t* int_obj) {
    Std_ReturnType ret = E_NOT_OK;
    if (NULL == int_obj) {
        ret = E_NOT_OK;
    } else {
        /* Enable on Change Interrupt for PORTB Pins (RP4 : RB7) */
        INTERRUPT_GlobalInterruptEnable();
        EXT_RBx_InterruptEnable();
    }
    return ret;
}

#if (INTERRUPT_PRIORITY_FEATURE == INTERRUPT_FEATURE_ENABLE)
static Std_ReturnType Interrupt_RBx_Priority_init(const interrupt_RBx_t* int_obj) {
    Std_ReturnType ret = E_NOT_OK;
    if (NULL == int_obj) {
        ret = E_NOT_OK;
    } else {
        if (int_obj->priority == HIGH_PRIORITY) {
            // Set RBx_interrupt as High Interrupt Source
            INTERRUPT_PriorityLevelsEnable();
            INTERRUPT_GlobalInterruptHighEnable();
            EXT_RBx_HighPrioritySet();
        } else if (int_obj->priority == LOW_PRIORITY) {
            // Set RBx_interrupt as Low Interrupt Source 
            INTERRUPT_PriorityLevelsEnable();
            INTERRUPT_GlobalInterruptLowEnable();
            EXT_RBx_LowPrioritySet();
        }
    }
    return ret;
}
#endif

static Std_ReturnType Interrupt_RBx_Pin_init(const interrupt_RBx_t* int_obj) {
    Std_ReturnType ret = E_NOT_OK;
    if (NULL == int_obj) {
        ret = E_NOT_OK;
    } else {
        // Initialize pin directions
        ret = GPIO_pin_direction_initialize(&(int_obj->mcu_pin));
        // Define interrupt handler for RBx on change interrupt 
        switch (int_obj->mcu_pin.pin) {
            case GPIO_PIN4:
                RB4_InterruptHandler = int_obj->RBx_EXT_InterruptHandler;               
                break;
            case GPIO_PIN5:
                RB5_InterruptHandler = int_obj->RBx_EXT_InterruptHandler;             
                break;
            case GPIO_PIN6:
                RB6_InterruptHandler = int_obj->RBx_EXT_InterruptHandler;               
                break;
            case GPIO_PIN7:
                RB7_InterruptHandler = int_obj->RBx_EXT_InterruptHandler;
                break;
            default:
                break;
        }
    }
    return ret;
}
#endif