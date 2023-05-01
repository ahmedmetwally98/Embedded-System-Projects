 /******************************************************************************
 *
 * Module: Common - Platform Types Abstraction
 *
 * File Name: std_types.h
 *
 * Description: types for AVR
 *
 * Author: Mohamed Tarek
 *
 *******************************************************************************/

#ifndef STD_TYPES_H_
#define STD_TYPES_H_


#ifndef NULL
#define NULL ((void *)0)
#endif

/* Boolean Values */
#ifndef FALSE
#define FALSE       (0u)
#endif

#ifndef TRUE
#define TRUE        (1u)
#endif

#define HIGH        (1u)
#define LOW         (0u)
#define BIT_MASK	(1u)

#define E_OK		(0x01U)
#define E_NOT_OK	(0x00)


/* ---------------- redefine Data Types ---------------- */
typedef unsigned char         uint8;          /*           0 .. 255             */
typedef signed char           sint8;          /*        -128 .. +127            */
typedef unsigned short        uint16;         /*           0 .. 65535           */
typedef signed short          sint16;         /*      -32768 .. +32767          */
typedef unsigned long         uint32;         /*           0 .. 4294967295      */
typedef signed long           sint32;         /* -2147483648 .. +2147483647     */
typedef unsigned long long    uint64;         /*       0..18446744073709551615  */
typedef signed long long      sint64;
typedef float                 float32;
typedef double                float64;

typedef uint8 Std_ReturnType;	/* standard return type from any SW interfaces */
typedef unsigned char bool;		/* Boolean Data Type */

#endif /* STD_TYPE_H_ */
