/*
 * adc.c
 *
 *  Created on: Apr 12, 2023
 *      Author: ahmed
 */


#include "adc.h"

/* ------------------------------ Global Variables Declarations ------------------------------ */
#include "ADC.h"
#if ADC_MODULE == MODULE_ENABLE

static void (*g_ADC_interrutHandlerNotify)(void) = NULL;

static inline void ADC_setVoltRef(uint8 a_voltRefOption);
static inline void ADC_setAutoTriggerevent(uint8 a_triggerEvent);
/* ----------------------------- SW Functions Definitions ------------------------------ */
Std_ReturnType ADC_init(const s_adc_t* a_adcObj)
{
	Std_ReturnType ret = E_OK;
	if(NULL == a_adcObj)
	{
		ret = E_NOT_OK;
	}
	else
	{
		/* ADC module Disable */
		ADCSRA &= ~(1<<ADEN);
		/* Set pre-scaler counter */
		ADCSRA = a_adcObj->adc_preScalerValue;
		/* ِADC Interrupt configuration */
#if ADC_INTERRUPT_FEATURE == INTERRUPT_FEATURE_ENABLE
		INTERRUPT_GLOBAL_ENABLE();
		if(1 == a_adcObj->adc_inetrruptEnable)
		{
			ADC_INTERRUPT_ENABLE();
			g_ADC_interrutHandlerNotify = a_adcObj->ADC_interruptHandlerNotify;
		}
		else{
			ADC_INTERRUPT_DISABLE();
		}
#endif
		/* set ADC input Channel */
		ADMUX = a_adcObj->adc_channel;
		/* set voltage reference option */
		ADC_setVoltRef(a_adcObj->adc_voltRef);
		/* Set right/left Data adjustment */
		if(a_adcObj->adc_resultAdjustfy == 1){
			SET_BIT(ADMUX, ADLAR);
		}
		else{	// right adjustment is the default
			CLEAR_BIT(ADMUX, ADLAR);
		}
		/* set ADC single conversion or auto Trigger */
		if(ADC_SINGLE_CONVERSION_MODE != a_adcObj->adc_mode){
			SET_BIT(ADCSRA, ADATE);
			ADC_setAutoTriggerevent(a_adcObj->adc_mode);
		}
		else{	// single conversion mode is the default mode
			CLEAR_BIT(ADCSRA, ADATE);
		}
		/* ADC module Enable */
		ADCSRA |= (1<<ADEN);
	}
	return ret;
}
Std_ReturnType ADC_deInit()
{
	Std_ReturnType ret = E_OK;
#if ADC_INTERRUPT_FEATURE == INTERRUPT_FEATURE_ENABLE
			ADC_INTERRUPT_DISABLE();
#endif
	/* ADC module Disable */
	ADCSRA &= ~(1<<ADEN);
	return ret;
}
Std_ReturnType ADC_StartConversion()
{
	Std_ReturnType ret = E_OK;
	/* start ADC conversion */
	SET_BIT(ADCSRA, ADSC);
	return ret;
}

Std_ReturnType ADC_StartConversionBlocking(uint16* a_adcData, uint8 a_dataAdjustment)
{
	Std_ReturnType ret = E_OK;
	if(NULL == a_adcData)
	{
		ret = E_NOT_OK;
	}
	else
	{
		/* start ADC conversion */
		SET_BIT(ADCSRA, ADSC);
		/* wait until conversion is done */
		while(!READ_BIT(ADCSRA, ADSC));
		/* Clear ADC interrupt Flag */
		ADC_CLEAR_INTERRUPT_FLAG();
		ADC_readData(a_adcData, a_dataAdjustment);
	}
	return ret;
}
void ADC_readData(uint16 *a_adcData, uint8 a_dataAdjustment)
{
	if(ADC_LEFT_ADJUST == a_dataAdjustment)
	{	// left adjustment reading process
		//*a_adcData = ADCL;
		*a_adcData = (((uint16)ADCH << 8) + ADCL) >> 6;
	}
	else
	{	// right adjustment reading process
		*a_adcData = ADCL;
		*a_adcData |= (uint16)(ADCH)<<8;
	}
}
/* ISR code on ADC Completion */
#if ADC_INTERRUPT_FEATURE == INTERRUPT_FEATURE_ENABLE
ISR(ADC_vect)
{
	if(NULL != g_ADC_interrutHandlerNotify)
	{
		g_ADC_interrutHandlerNotify();
	}
}
#endif

/*------------------------------ Helper Function Definitions ------------------------------*/
static inline void ADC_setVoltRef(uint8 a_voltRefOption)
{
	switch(a_voltRefOption)
	{
	case ADC_REF_VOLTAGE_AREF:		CLEAR_BIT(ADMUX, REFS0); CLEAR_BIT(ADMUX, REFS1);	// REFS0,1 = 0, 0
		break;
	case ADC_REF_VOLTAGE_AVCC:		CLEAR_BIT(ADMUX, REFS0); SET_BIT(ADMUX, REFS1);	// REFS0,1 = 0, 1
		break;
	case ADC_REF_VOLTAGE_INTERNAL:	SET_BIT(ADMUX, REFS0); SET_BIT(ADMUX, REFS1);	// REFS0,1 = 1, 1
		break;
	default:	SET_BIT(ADMUX, REFS0); SET_BIT(ADMUX, REFS1);		// Internal VREF is the default
	}
}
static inline void ADC_setAutoTriggerevent(uint8 a_triggerEvent)
{
	switch(a_triggerEvent)
	{
	case ADC_AUTO_TRIGGER_FREE_RUNNING_MODE: CLEAR_BIT(SFIOR, ADTS0); CLEAR_BIT(SFIOR, ADTS1); CLEAR_BIT(SFIOR, ADTS2);
		break;
	case ADC_AUTO_TRIGGER_INT0_MODE: CLEAR_BIT(SFIOR, ADTS0); SET_BIT(SFIOR, ADTS1); CLEAR_BIT(SFIOR, ADTS2);
		break;
	case ADC_AUTO_TRIGGER_CAP_EVENT_MODE: SET_BIT(SFIOR, ADTS0); SET_BIT(SFIOR, ADTS1); SET_BIT(SFIOR, ADTS2);
		break;
	}
}
#endif
