/*
 * external_eeprom.c
 *
 *  Created on: Apr 17, 2023
 *      Author: ahmed
 */

#include "external_eeprom.h"

#if EXTERNAL_EEPROM_MODULE == MODULE_ENABLE

Std_ReturnType EEPROM24C16_writeByte(uint16 address, uint8 data)
{
	/* Minimizing write delays by polling on ACK
	 * 1- Initial condition: a write cycle is in progress.
	 * 2- Step 1: the bus master issues a Start condition followed by a device select code (the first byte of the new instruction)
	 * 3- Step 2: if the device is busy with the internal write cycle, no ACK is returned and the bus master goes back
	 *	to step 1. If the device has terminated the internal write cycle, it responds with an ACK, indicating that the
	 *	device is ready to receive the second part of the instruction (the first byte of this instruction having been sent
	 *	during Step 1).
	 *  */
	Std_ReturnType ret = E_OK;
	/*R/W-bit = 0 for write operation.*/
	uint8 l_TxBits=0xA0;
	TWI_init();
	/* make sure device is in stand by state */
	do{
		TWI_start();
		// Send device select address
		l_TxBits |= (address >> 7);
		l_TxBits &= ~(1<<TW_R_W_BIT);
		TWI_write(l_TxBits);
	}while(TW_MT_SLA_W_NACK == TWI_getStatus());
	// sent byte address
	l_TxBits = (uint8)address;
	TWI_write(l_TxBits);
	if(TW_MT_DATA_ACK != TWI_getStatus())
	{	// WC line (write protection) is held high
		ret = E_NOT_OK;
	}
	else
	{
		TWI_write(data);
	}
	TWI_stop();
	return ret;
}
Std_ReturnType EEPROM24C16_readByte(uint16 address, uint8 *data)
{
	Std_ReturnType ret = E_OK;
	/*R/W-bit = 1 for read operation.*/
	uint8 l_TxBits=0xA0;
	TWI_init();
	/* make sure device is in stand by state and no write in operation now*/
	do{
		TWI_start();
		// Send device select address
		l_TxBits |= (address >> 7);
		TWI_write(l_TxBits);
	}while(TW_MT_SLA_W_NACK == TWI_getStatus());
	// sent byte address
	l_TxBits = (uint8)address;
	TWI_write(l_TxBits);
	// initiate Repeated start condition
	TWI_start();
	if(TW_REP_START == TWI_getStatus())
	{
		l_TxBits = 0xA1 | (address >> 7);
		TWI_write(l_TxBits);
		*data = TWI_readWithNACK();	// Master sends NACK as we read only one byte.
	}
	else
	{
		ret = E_NOT_OK;
	}
	TWI_stop();
	return ret;
}

// maximum Length = page size = 16-bytes
Std_ReturnType EEPROM24C16_writeBlock(uint16 a_address, uint8* a_array, uint8 a_blockLength)
{
	Std_ReturnType ret = E_OK;
	uint8 index = 0, l_TxBits = 0xA0;
	if(a_blockLength > 16)	// maximum page size = 16 bytes
	{
		ret = E_NOT_OK;
	}
	else
	{
		TWI_init();
		/* make sure device is in stand by state and no write in operation now*/
		do{
			TWI_start();
			// Send device select address
			l_TxBits |= (a_address >> 7);
			TWI_write(l_TxBits);
		}while(TW_MT_SLA_W_NACK == TWI_getStatus());
		// sent byte address
		l_TxBits = (uint8)a_address;
		TWI_write(l_TxBits);
		while(a_blockLength--)
		{
			TWI_write(a_array[index]);
			index++;
		}
	}
	TWI_stop();
	return ret;
}
Std_ReturnType EEPROM24C16_readBlock(uint16 a_address, uint8* a_array, uint8 a_blockLength)
{
	Std_ReturnType ret = E_OK;
	uint8 index = 0, l_TxBits = 0xA0;
	if(a_blockLength > 16)	// maximum page size = 16 bytes
	{
		ret = E_NOT_OK;
	}
	else
	{
		TWI_init();
		/* make sure device is in stand by state and no write in operation now*/
		do{
			TWI_start();
			// Send device select address
			l_TxBits |= (a_address >> 7);
			TWI_write(l_TxBits);
		}while(TW_MT_SLA_W_NACK == TWI_getStatus());
		// sent byte address
		l_TxBits = (uint8)a_address;
		TWI_write(l_TxBits);
		TWI_start();	// Master sends repeated start condition for reading required data block.
		if(TW_REP_START != TWI_getStatus())
		{
			ret = E_NOT_OK;
		}
		else
		{
			l_TxBits = 0xA1 | (a_address >> 7);
			TWI_write(l_TxBits);
			while(index < a_blockLength)
			{
				if(index < (a_blockLength - 1))
				{
					a_array[index] = TWI_readWithACK();
				}
				else
				{
					a_array[index] = TWI_readWithNACK();
				}
				index++;
			}
		}
	}
	TWI_stop();
	return ret;
}

#endif
