/* 
 * File:   std_libraries.h
 * Author: ahmed
 *
 * Created on January 8, 2023, 4:31 PM
 */

#ifndef STD_LIBRARIES_H
#define	STD_LIBRARIES_H

/* Section : Includes */
#include <stdlib.h>

/* Section : MACRO Declarations */
#define BIT_MASK            (uint8)1

/* Section : MACRO Function Declarations */
/* Clear Bit in Register */
#define CLEAR_BIT(REG, BIT_POSN)        (((REG) &= ~(BIT_MASK<<(BIT_POSN))))
/* Set Bit in Register */
#define SET_BIT(REG, BIT_POSN)          (((REG) |= (BIT_MASK<<(BIT_POSN))))
/* Toggle Bit in Register */
#define TOGGLE_BIT(REG, BIT_POSN)       (((REG) ^= (BIT_MASK<<(BIT_POSN))))
/* Check if bit value = 1 */
#define IS_BIT_SET(REG, BIT_POS)        (((1<<(BIT_POS)) | (REG)) != 0)
/* Check if bit value = 0 */
#define IS_BIT_CLEAR(REG, BIT_POS)      ((~(1<<(BIT_POS)) & (REG)) == 0)

#define READ_BIT(REG, BIT_POSN)         ((REG) >> (BIT_POSN) & (BIT_MASK))

#define ROR(REG, NUM, REG_SIZE)         (REG = (REG>>NUM) | (REG<<(REG_SIZE-NUM)))

#define ROL(REG, NUM, REG_SIZE)         (REG = (REG<<NUM) | (REG>>(REG_SIZE-NUM)))

#if (CPU_ARCH == ARCH_8BIT)
#define HWREG8(_X)          (*((volatile uint8 *)(_X)))
#elif (CPU_ARCH == ARCH_16BIT)
#define HWREG16(_X)         (*((volatile uint16 *)(_X)))
#elif (CPU_ARCH == ARCH_32BIT)
#define HWREG32 (_X)        (*((volatile uint32 *)(_X)))
#endif

/* Section : Data Type Declarations */

/* Section : Functions Declarations */


#endif	/* STD_LIBRARIES_H */

