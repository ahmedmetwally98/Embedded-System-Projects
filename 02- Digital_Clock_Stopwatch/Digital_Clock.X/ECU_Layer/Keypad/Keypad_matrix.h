/* 
 * File:   Keypad_matrix.h
 * Author: ahmed
 *
 * Created on March 1, 2023, 2:33 PM
 */

#ifndef KEYPAD_MATRIX_H
#define	KEYPAD_MATRIX_H

/* ---------------- Includes ---------------- */
#include "../../MCAL_Layer/GPIO/hal_gpio.h"

/* ---------------- MACRO Declarations ---------------- */
#define KEYPAD_MATRIX_ROWS          4
#define KEYPAD_MATRIX_COLS          4

/* ---------------- MACRO Function Declarations ---------------- */

/* ---------------- Data Type Declarations ---------------- */
typedef struct{
    pin_config_t keypad_rows_pins[KEYPAD_MATRIX_ROWS];
    pin_config_t keypad_cols_pins[KEYPAD_MATRIX_COLS];
}keypad_matrix_t;

/* ---------------- Functions Declarations ---------------- */
Std_ReturnType Keypad_init(const keypad_matrix_t* key_obj);
Std_ReturnType Keypad_getValue(const keypad_matrix_t* key_obj, uint8* value);

#endif	/* KEYPAD_MATRIX_H */

