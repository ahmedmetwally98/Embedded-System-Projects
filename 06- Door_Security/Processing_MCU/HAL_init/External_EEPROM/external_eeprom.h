/*
 * external_eeprom.h
 *
 *  Created on: Apr 17, 2023
 *      Author: ahmed
 *      Description: this module implements External EEPROM model m24C16 by STMicroElectronics
 *      it is 2kbytes EEPROM with address value range [0x0000 : 0x07FF]
 *      user can write byte or read byte
 *      and also write sequential bytes or read sequential bytes
 */

#ifndef EXTERNAL_EEPROM_EXTERNAL_EEPROM_H_
#define EXTERNAL_EEPROM_EXTERNAL_EEPROM_H_



/* -------------------- Includes -------------------- */
#include "../../common_macros.h"
#include "../../std_types.h"
#include "../../micro_config.h"
#include "../../MCAL_init/I2C_Driver/I2C.h"

#if EXTERNAL_EEPROM_MODULE == MODULE_ENABLE
/* -------------------- MACRO Definitions -------------------- */

/* -------------------- MACRO Functions Definitions -------------------- */

/* -------------------- Data Type Declarations -------------------- */

/* -------------------- Software Interfaces -------------------- */

Std_ReturnType EEPROM24C16_writeByte(uint16 address, uint8 data);
Std_ReturnType EEPROM24C16_readByte(uint16 address, uint8 *data);

// maximum Length = page size = 16-bytes
Std_ReturnType EEPROM24C16_writeBlock(uint16 address, uint8* Array, uint8 length);
Std_ReturnType EEPROM24C16_readBlock(uint16 address, uint8* Array, uint8 length);
#endif

#endif /* EXTERNAL_EEPROM_EXTERNAL_EEPROM_H_ */
