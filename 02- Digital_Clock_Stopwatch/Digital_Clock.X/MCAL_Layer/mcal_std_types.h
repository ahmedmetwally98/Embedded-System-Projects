/* 
 * File:   mcal_std_types.h
 * Author: ahmed
 *
 * Created on January 8, 2023, 4:29 PM
 */

#ifndef MCAL_STD_TYPES_H
#define	MCAL_STD_TYPES_H

/* Section : Includes */
#include "compiler.h"
#include "std_libraries.h"
#include "Limits.h"

/* Section : Data Type Declarations */

typedef enum {
    False,
    True  
}boolean;

typedef unsigned char           uint8;
typedef unsigned short          uint16;
typedef unsigned long           uint32;
typedef signed char             sint8;
typedef signed short            sint16;
typedef signed long             sint32;
typedef unsigned char           Std_ReturnType;

/* Section : MACRO Declarations */
#define STD_HIGH        0x01
#define STD_LOW         0x00

#define STD_ON          0x01
#define STD_OFF         0x00

#define STD_ACTIVE      0x01
#define STD_IDLE        0x00

#define ZERO_INIT       0U

#define E_OK            (Std_ReturnType)0x01
#define E_NOT_OK        (Std_ReturnType)0x00



/* Section : MACRO Function Declarations */


/* Section : Functions Declarations */


#endif	/* MCAL_STD_TYPES_H */

