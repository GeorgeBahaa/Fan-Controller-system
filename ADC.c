/*
 * ADC.c
 *
 *  Created on: Oct 6, 2022
 *      Author: georg
 */
#include "avr/io.h" /* To use the ADC Registers */
#include "ADC.h"
#include "common_macros.h" /* To use the macros like SET_BIT */

/*******************************************************************************
 *                      Functions Definitions                                  *
 *******************************************************************************/

/*
 * Description:
 * Function responsible for initialize the ADC driver:
 * 1) Setup the ADC reference voltage
 * 2) Setup the ADC prescaler
 */
void ADC_init(const ADC_ConfigType * Config_Ptr){
	/* ADMUX Register Bits Description:
	 * REFS1:0 = 00 to choose to connect external reference voltage by input this voltage through AREF pin
	 * ADLAR   = 0 right adjusted
	 * MUX4:0  = 00000 to choose channel 0 as initialization
	 */
	ADMUX = 0;

	/* Setup up the reference voltage value in REFS1 and REFS0 bits*/
	ADMUX |= (Config_Ptr->ref_volt <<6);

	/* ADCSRA Register Bits Description:
	 * ADEN    = 1 Enable ADC
	 * ADIE    = 0 Disable ADC Interrupt
	 * ADATE   = 0 Disable Auto Trigger
	 * ADPS2:0 = 000 clear these three bits before setup the required prescaler value
	 */
	ADCSRA = (1<<ADEN);

	/* Setup up the reference prescaler value in ADPS0 and ADPS1 and ADPS2 bits*/
	ADCSRA |= (Config_Ptr->prescaler);
}

/*
 * Description :
 * Function responsible for read analog data from a certain ADC channel
 * and convert it to digital using the ADC driver.
 */
uint16 ADC_readChannel(uint8 channel_num){
	channel_num &= 0x07; /* Input channel number must be from 0 --> 7 */
	ADMUX &= 0xE0; /* Clear first 5 bits in the ADMUX (channel number MUX4:0 bits) before set the required channel */
	ADMUX = ADMUX | channel_num; /* Choose the correct channel by setting the channel number in MUX4:0 bits */
	SET_BIT(ADCSRA,ADSC); /* Start conversion write '1' to ADSC */
	while(BIT_IS_CLEAR(ADCSRA,ADIF)); /* Wait for conversion to complete, ADIF becomes '1' */
	SET_BIT(ADCSRA,ADIF); /* Clear ADIF by write '1' to it :) */
	return ADC; /* Read the digital value from the data register */
}
