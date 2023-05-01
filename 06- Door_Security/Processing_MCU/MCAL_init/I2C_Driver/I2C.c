/*
 * I2C.c
 *
 *  Created on: Apr 5, 2023
 *      Author: ahmed
 */

#include "I2C.h"
/* ------------------------------ Global Variables Declarations ------------------------------ */
#if I2C_MODULE == MODULE_ENABLE

#if TWI_INTERRUPT_FEATURE == INTERRUPT_FEATURE_ENABLE
static void (*TWI_callBackNotify)(void) = NULL;
#endif
/* ------------------------------ SW Functions Definitions ------------------------------ */
void TWI_init(void)
{
/* initialize the TWi module with pre-scaler = 0 and SCL frequency (for master) = 100KHz */
	TWBR = F_CPU/(2.0*100000);		// Pre-scaler bits = 0,0 and SCL Frequency = 100KHz
	TWSR = 0x00;
	/* Two Wire Bus address my address if any master device want to call me: 0x01 (used in case this MC is a slave device)
	   General Call Recognition: Off */
	TWAR = 0b00000010;
	TWCR = (1<<TWEN); /* enable TWI */
}
void TWI_deInit(void)
{
	// Clear all TWI module registers
	TWCR = 0x00;
	TWBR = 0x00;
	TWSR = 0x00;
}


void TWI_start(void)
{
	/*
	 * Clear the TWINT flag before sending the start bit TWINT=1
	 * send the start bit by TWSTA=1
	 * Enable TWI Module TWEN=1
	 */
	TWCR |= (1<<TWINT) | (1<<TWSTA) | (1<<TWEN);
	// wait for Start condition occurs on the TWI BUS
	while(!READ_BIT(TWCR, TWINT));
}
void TWI_stop(void)
{
	/*
	 * Clear the TWINT flag before sending the stop bit TWINT=1
	 * send the stop bit by TWSTO=1
	 * Enable TWI Module TWEN=1
	 */
	TWCR |= (1<<TWINT) | (1<<TWSTO) | (1<<TWEN);
	// TWSTO is cleared by HW automatically when Stop condition occurs on the TWI bus
}
void TWI_write(uint8 AddressData)
{
	/* Put data On TWI data Register */
	TWDR = AddressData;
	/*
	 * Clear the TWINT flag before sending the data TWINT=1
	 * Enable TWI Module TWEN=1
	 */
	TWCR = (1 << TWINT) | (1 << TWEN);
	/* Wait for TWINT flag set in TWCR Register(data is send successfully) */
	while(!READ_BIT(TWCR,TWINT));
}
uint8 TWI_readWithACK(void)
{
	/*
	 * Clear the TWINT flag before reading the data TWINT=1
	 * Enable sending ACK after reading or receiving data TWEA=1
	 * Enable TWI Module TWEN=1
	 */
	TWCR = (1 << TWINT) | (1 << TWEN) | (1 << TWEA);
	/* Wait for TWINT flag set in TWCR Register (data received successfully) */
	while(!READ_BIT(TWCR,TWINT));
	/* Read Data */
	return TWDR;
}
uint8 TWI_readWithNACK(void)
{
	/*
	 * Clear the TWINT flag before reading the data TWINT=1
	 * Enable sending NACK after reading or receiving data TWEA=1
	 * Enable TWI Module TWEN=1
	 */
	TWCR = (1 << TWINT) | (1 << TWEN);
	CLEAR_BIT(TWCR, TWEA);
	/* Wait for TWINT flag set in TWCR Register (data received successfully) */
	while(!READ_BIT(TWCR,TWINT));
	/* Read Data */
	return TWDR;
}
uint8 TWI_getStatus(void)
{
	uint8 status;
	/* masking to eliminate first 3 bits (pre-scaler and unused bits) and get the last 5 bits (status bits) */
	status = TWSR & 0xF8;
	return status;
}

#if TWI_INTERRUPT_FEATURE == INTERRUPT_FEATURE_ENABLE
Std_ReturnType TWI_setCallBack(void (*ptr_func)(void))
{
	Std_ReturnType ret = E_OK;
	if(ptr_func)
	{
		TWI_callBackNotify = ptr_func;
		// enable TWI interrupt
		SET_BIT(TWCR, TWIE);
	}
	else if(NULL == ptr_func)
	{
		ret = E_NOT_OK;
	}
	return ret;
}
#endif
// ISR code
#if TWI_INTERRUPT_FEATURE == INTERRUPT_FEATURE_ENABLE
ISR(TWI_vect)
{
	if(TWI_callBackNotify)
		TWI_callBackNotify();
	// TWI interrupt flag must be Cleared at end of ISR
	SET_BIT(TWCR, TWINT);
}
#endif


#endif

