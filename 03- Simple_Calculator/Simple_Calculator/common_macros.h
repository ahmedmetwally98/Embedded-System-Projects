 /******************************************************************************
 *
 * Module: Common - Macros
 *
 * File Name: Common_Macros.h
 *
 * Description: Commonly used Macros
 *
 * Author: Mohamed Tarek
 *
 *******************************************************************************/

#ifndef COMMON_MACROS
#define COMMON_MACROS

#ifndef BIT_MASK
#define BIT_MASK		(1u)
#endif

/* Clear a certain bit in any register */
#define CLEAR_BIT(REG, BIT_POS)        (REG &= ~(BIT_MASK << BIT_POS))

/* Set a certain bit in any register */
#define SET_BIT(REG, BIT_POS)          ((REG |= (BIT_MASK << BIT_POS)))

/* Toggle a certain bit in any register */
#define TOGGLE_BIT(REG, BIT_POS)       ((REG ^= (BIT_MASK << BIT_POS)))

/* Check if a specific bit is set in any register and return true if yes */
#define IS_BIT_SET(REG, BIT_POS)        ((BIT_MASK<<(BIT_POS)) & (REG))

/* Check if a specific bit is cleared in any register and return true if yes */
#define IS_BIT_CLEAR(REG, BIT_POS)      ( !((BIT_MASK<<BIT_POS) & REG))

/* Read the value, 0 or 1, of a specific bit in any register */
#define READ_BIT(REG, BIT_POS)         ((REG >> BIT_POS) & BIT_MASK)

/* Rotate right the register value with specific number of rotates */
#define ROR(REG,NUM, REG_SIZE) ( REG= (REG>>NUM) | (REG<<(REG_SIZE-NUM)) )

/* Rotate left the register value with specific number of rotates */
#define ROL(REG,NUM, REG_SIZE) ( REG= (REG<<NUM) | (REG>>(REG_SIZE-NUM)) )



#endif
