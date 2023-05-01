/*
 * Interrupt_gen_config.h
 *
 *  Created on: Mar 14, 2023
 *      Author: ahmed
 */


/* Section : Includes */

/* Section : MACRO Declarations */
#define INTERRUPT_FEATURE_ENABLE                (1u)
#define INTERRUPT_FEATURE_DISABLE               (0u)

#define INTERRUPT_NESTING_FEATURE               INTERRUPT_FEATURE_ENABLE
#define INTERRUPT_EXTERNAL_INTx_FEATURE         INTERRUPT_FEATURE_ENABLE

#define TIMER1_INTERRUPT_FEATURE				INTERRUPT_FEATURE_ENABLE
#define TIMER1_OV1_INTERRUPT_FEATURE            INTERRUPT_FEATURE_ENABLE
#define TIMER1_IC1_INTERRRUPT_FEATURE			INTERRUPT_FEATURE_DISABLE
#define TIMER1_OC1A_INTERRRUPT_FEATURE			INTERRUPT_FEATURE_DISABLE
#define TIMER1_OC1B_INTERRRUPT_FEATURE			INTERRUPT_FEATURE_DISABLE



/* Section : MACRO Function Declarations */


/* Section : Data Type Declarations */


/* Section : Functions Declarations */
