/* 
 * File:   macl_interrupt_gen_cfg.h
 * Author: ahmed
 *
 * Created on February 19, 2023, 12:11 AM
 */

#ifndef MACL_INTERRUPT_GEN_CFG_H
#define	MACL_INTERRUPT_GEN_CFG_H

/* Section : Includes */

/* Section : MACRO Declarations */
#define INTERRUPT_FEATURE_ENABLE                0x01
#define INTERRUPT_FEATURE_DISABLE               0x00

#define INTERRUPT_PRIORITY_FEATURE              INTERRUPT_FEATURE_DISABLE
/* External Interrupts */
#define INTERRUPT_EXTERNAL_INTx_FEATURE         INTERRUPT_FEATURE_ENABLE
#define INTERRUPT_EXTERNAL_OnChange_FEATURE     INTERRUPT_FEATURE_ENABLE
/* Internal / Peripheral interrupts */
#define TIMER1_INTERRUPT_FEATURE                INTERRUPT_FEATURE_ENABLE
#define TIMER3_INTERRUPT_FEATURE                INTERRUPT_FEATURE_ENABLE

/* Section : MACRO Function Declarations */


/* Section : Data Type Declarations */


/* Section : Functions Declarations */


#endif	/* MACL_INTERRUPT_GEN_CFG_H */

