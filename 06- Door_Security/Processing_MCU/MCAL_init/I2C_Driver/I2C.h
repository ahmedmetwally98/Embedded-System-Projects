/*
 * I2C.h
 *
 *  Created on: Apr 5, 2023
 *      Author: ahmed
 */

#ifndef I2C_DRIVER_I2C_H_
#define I2C_DRIVER_I2C_H_

/* -------------------- Includes -------------------- */
#include "../../common_macros.h"
#include "../../micro_config.h"
#include "../../std_types.h"
#include "../Interrupt_Driver/Interrupt_gen_config.h"

#if I2C_MODULE == MODULE_ENABLE
/* -------------------- MACRO Definitions -------------------- */
#define TW_R_W_BIT		 0x00
/* I2C Status Bits in the TWSR Register */
// start has been sent
#define TW_START         0x08
// repeated start
#define TW_REP_START     0x10
// Master transmit ( slave address + Write request ) to slave + ACK received from slave
#define TW_MT_SLA_W_ACK  0x18
// Master transmit ( slave address + Write request ) to slave + NACK received from slave
#define TW_MT_SLA_W_NACK 0x20
// Master transmit ( Data Byte ) to slave + ACK received from slave
#define TW_MT_DATA_ACK	 0x28
// Master transmit ( Data Byte ) to slave + NACK received from slave
#define TW_MT_DATA_NACK	 0x30
// Master transmit ( Data/Address ) to slave + Arbitration is lost
#define TW_MT_ARBI_LOST	 0x38
// Master transmit ( slave address + read request ) to slave + ACK received from slave
#define TW_MT_SLA_R_ACK  0x40
// Master transmit ( slave address + read request ) to slave + NACK received from slave
#define TW_MT_SLA_R_NACK 0x48
// Master received data and send ACK to slave
#define TW_MR_DATA_ACK   0x50
// Master received data but doesn't send ACK to slave
#define TW_MR_DATA_NACK  0x58

// Slave received its SLA+W ( address match occurs ) + ACK returned and data byte will be received next.
#define TW_SR_SLA_ACK	 	0x60
// General call address has been received + ACK returned and data byte will be received next.
#define TW_SR_GC_ACK	 	0x70
// Previously addressed with own SLA+W + data has been received and ACK has been returned
#define TW_SR_DATA_ACK	 	0x80
// Previously addressed with own SLA+W + data has been received and NACK has been returned
#define TW_SR_DATA_NACK	 	0x88
// Previously addressed with general call + data has been received and ACK has been returned
#define TW_SR_GC_DATA_ACK	0x90
// Previously addressed with general call + data has been received and NACK has been returned
#define TW_SR_GC_DATA_NACK	0x98


// Slave received its SLA+R ( address match occurs ) + ACK returned and data byte will be transmitted next.
#define TW_ST_SLA_ACK	 0xA8
// Data byte in TWDR has been transmitted; ACK has been received
#define TW_ST_DATA_ACK	 0xB8
// Data byte in TWDR has been transmitted; NOT ACK has been received
#define TW_ST_DATA_NACK	 0xC0
// Last data byte in TWDR has been transmitted (TWEA = “0”); ACK has been received
#define TW_ST_LAST_DATA	 0xC8
/* -------------------- MACRO Functions Definitions -------------------- */

/* -------------------- Data Type Declarations -------------------- */


/* -------------------- Software Interfaces -------------------- */
void TWI_init(void);					// just enable TWI module
void TWI_deInit(void);					// just de-initialize the TWI module
void TWI_start(void);					// send start condition or Repeated start condition.
void TWI_stop(void);					// send stop condition
void TWI_write(uint8 AddressData);		// master may write address or data. slave write data only
uint8 TWI_readWithACK(void); 			// read with send ACK
uint8 TWI_readWithNACK(void);			// read without send ACK
uint8 TWI_getStatus(void);				// return the status code form TWSR
Std_ReturnType TWI_setCallBack(void (*ptr_func)(void));
#endif


#endif /* I2C_DRIVER_I2C_H_ */
