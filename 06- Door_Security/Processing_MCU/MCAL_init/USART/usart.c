/*
 * usart.c
 *
 *  Created on: Apr 5, 2023
 *      Author: ahmed
 */


/* ------------------------------ Global Variables Declarations ------------------------------ */
#if USART_MODULE == MODULE_ENABLE
#include "usart.h"

#if USART_INTERRUPT_FEATURE == INTERRUPT_FEATURE_ENABLE
static void (*TX_interruptHandler)(void) = NULL;
static void (*RX_interruptHandler)(void) = NULL;
#endif

static void set_baudRate(uint32 baudRate, uint8 usart_mode);
static void set_frame_size(uint8 char_size, uint8 parity);
/* ------------------------------ SW Functions Definitions ------------------------------ */
Std_ReturnType USART_Init(const usart_t* _obj)
{
	Std_ReturnType ret = E_OK;
	if(NULL == _obj)
	{
		ret = E_NOT_OK;
	}
	else
	{
		// Disable RX and TX
		UCSRB = 0;
		// UASRT Interrupt Configurations
#if USART_INTERRUPT_FEATURE == INTERRUPT_FEATURE_ENABLE
		INTERRUPT_GLOBAL_ENABLE();
		if(_obj->usart_rx_interrupt_enable == RX_INTERUPT_ENABLE)
		{
			USART_RX_INTERUPT_ENABLE();
			RX_interruptHandler = _obj->USART_RxInterruptHandler;
		}
		if(_obj->usart_tx_interrupt_enable == TX_INTERUPT_ENABLE)
		{
			USART_TX_INTERUPT_ENABLE();
			TX_interruptHandler = _obj->USART_TxInterruptHandler;
		}
#endif
		// BaudRate Configuration
		set_baudRate(_obj->baudrate, _obj->usart_mode);
		// Construct Frame Size
		set_frame_size(_obj->usart_character_size, _obj->usart_parity);
		// Enable USART Module
		if (_obj->usart_rx_enable == USART_RX_ENABLE)
		{
			SET_BIT(UCSRB, RXEN);
		}
		if(_obj->usart_tx_enable == USART_TX_ENABLE)
		{
			SET_BIT(UCSRB, TXEN);
		}
	}
	return ret;
}
Std_ReturnType USART_Send_Byte_Blocking(const uint8 _data_byte)
{
	Std_ReturnType ret = E_OK;
	/* wait until TX buffer (UDR) is empty */
	while(!READ_BIT(UCSRA, UDRE));
	UDR = _data_byte;
	/* wait until TX shift register is empty (Transmission complete) */
	while(!READ_BIT(UCSRA, TXC));
	/* Clear USART Transmit Complete flag */
	SET_BIT(UCSRA, TXC);
	return ret;
}
Std_ReturnType USART_Receive_Byte_Blocking(usart_t* _obj, uint8* _data_byte)
{
	Std_ReturnType ret = E_OK;
	if(NULL == _obj || NULL == _data_byte)
	{
		ret = E_NOT_OK;
	}
	else
	{
		/* wait until received byte loaded in RX buffer (UDR) */
		while(!READ_BIT(UCSRA, RXC));
		/* Reading flags for error checking */
		_obj->error_status.flag_status = UCSRA;
		if(_obj->error_status.usart_dov || _obj->error_status.usart_ferr || _obj->error_status.usart_pe)
		{	// some error occur
			ret = E_NOT_OK;
		}
		else
		{	// no error detected.
			*_data_byte = UDR;
		}
	}
	return ret;
}
Std_ReturnType USART_sendString_Blocking(const uint8 *Str)
{
	Std_ReturnType ret = E_OK;
	uint8 str_index = 0;
	while('\0' != Str[str_index])
	{
		USART_Send_Byte_Blocking(Str[str_index]);
		str_index++;
	}
	return ret;
}
Std_ReturnType USART_receiveString_Blocking(usart_t* _obj, uint8 *Str)
{
	Std_ReturnType ret = E_OK;
	uint8 str_index = 0;
	if(NULL == _obj || NULL == Str)
	{
		ret = E_NOT_OK;
	}
	else
	{
		ret = USART_Receive_Byte_Blocking(_obj, &Str[str_index]);
		while('#' != Str[str_index])
		{
			str_index++;
			ret = USART_Receive_Byte_Blocking(_obj, &Str[str_index]);
			if(E_NOT_OK == ret)
			{
				break;
			}
		}
		Str[str_index] = '\0';
	}
	return ret;
}

#if USART_INTERRUPT_FEATURE == INTERRUPT_FEATURE_ENABLE
Std_ReturnType USART_Send_Byte(const uint8 _data_byte)
{
	Std_ReturnType ret = E_OK;
	UDR = _data_byte;
	return ret;
}

/* Implemeting the USART ISRs*/
ISR(USART_RXC_vect)
{
	uint8 corrupted_byte;

	/*Check error flags*/
	if(UCSRA & ((1<<FE)|(1<<DOR)|(1<<PE))){
		corrupted_byte = UDR;
	}
	else if(RX_interruptHandler){
		// RXC Flag is automatically cleared by reading the UDR buffer
		// UDR buffer must be read in the call back function for avoiding nested interrupt
		RX_interruptHandler();
	}
}
ISR(USART_TXC_vect)
{
	// TXC Flag is automatically cleared at the end of interrupt routine
	if(TX_interruptHandler)
		TX_interruptHandler();
}
#endif	//

static void set_baudRate(uint32 baudRate, uint8 usart_mode)
{
	uint16 baud_reg = 0;
	switch(usart_mode)
	{
	case USART_SYNC_MODE:	UCSRC |= ((1 << URSEL) | (1 << UMSEL));
		baud_reg = (uint16)(F_CPU / (2.0*baudRate)) -1;
		break;
	case USART_ASYNC_DOUBLE_SPEED_MODE:	UCSRC |= ((1 << URSEL) & ~(1 << UMSEL));
		SET_BIT(UCSRA, U2X);						// ASYNC in Double Speed
		baud_reg = (uint16)(F_CPU / (8.0*baudRate)) -1;
		break;
	default:	UCSRC |= ((1 << URSEL) & ~(1 << UMSEL));
		CLEAR_BIT(UCSRA, U2X);						// ASYNC Normal Mode
		baud_reg = (uint16)(F_CPU / (16.0*baudRate)) -1;
		break;
	}

	UBRRL = (uint8)baud_reg;
	UBRRH = (baud_reg >> 8) & 0x0F;	// lowest 4-bits only to be masked.
}
static void set_frame_size(uint8 char_size, uint8 parity)
{
	// use 1-stop bit
	UCSRC |= (1<<URSEL) & ~(1<<USBS);
	// configure parity bit
	switch(parity)
	{
	case EVEN_PARITY:	UCSRC |= ((1<<URSEL) & ~(1<<UPM0)) | (1<<UPM1);
		break;
	case ODD_PARITY:	UCSRC |= (1<<URSEL) | (1<<UPM0) | (1<<UPM1);
		break;
	default:	UCSRC |= (1<<URSEL) & ~(1<<UPM0) & ~(1<<UPM1);		// No Parity
	break;
	}
	// configure data size
	switch(char_size)
	{
	case 5:	UCSRC |= ((1<<URSEL) & ~(1<<UCSZ0)) & ~(1<<UCSZ1);			// # of data bits = 5
			UCSRB &= ~(1<<UCSZ2);
		break;
	case 6:	UCSRC |= ((1<<URSEL) | (1<<UCSZ0)) & (~(1<<UCSZ1));			// # of data bits = 6
			UCSRB &= ~(1<<UCSZ2);
		break;
	case 7:	UCSRC |= ((1<<URSEL) & ~(1<<UCSZ0)) | (1<<UCSZ1);			// # of data bits = 7
			UCSRB &= ~(1<<UCSZ2);
		break;
	case 9:	UCSRC |= (1<<URSEL) | (1<<UCSZ0) | (1<<UCSZ1);				// # of data bits = 9
			UCSRB |= (1<<UCSZ2);
		break;
	default:UCSRC |= (1<<URSEL) | (1<<UCSZ0) | (1<<UCSZ1);				// # of data bits = 8
			UCSRB &= ~(1<<UCSZ2);
	}
}

#endif
