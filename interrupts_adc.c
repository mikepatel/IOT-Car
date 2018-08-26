/******************************************************************************
File Name: interrupts_adc.c

Description: This file contains the ADC ISRs

Author: Michael Patel
Date: October 2016
Compiler: Built with IAR Embedded Workbench Version: V7.4.2.4369 (6.50.1)
*******************************************************************************
*/

#include "msp430.h"
#include "functions.h"
#include "macros.h"

extern volatile unsigned int ADC_THUMB;
extern volatile unsigned int ADC_Right_Detector;
extern volatile unsigned int ADC_Left_Detector;
extern volatile unsigned int ADC_CHANNEL_COUNT;
extern volatile unsigned int interrupt_event;


/******************************************************************************
ADC ISR
ADC_Right_Detector						A00	ADCINCH_0	P1.0
ADC_Left_Detector						A01 ADCINCH_1	P1.1
ADC_THUMB								A03	ADCINCH_3	P1.3
ADC_TEMP								A10 ADCINCH_10	Temperature REF module
ADC_BAT									A11 ADCINCH_11 	Internal
*/
#pragma vector=ADC10_VECTOR
__interrupt void ADC10_ISR(void){
	switch(__even_in_range(ADC10IV, _12u)){
		case _0u: // No interrupt
			break;

		case _2u: // conversion result OF
			break;

		case _4u: // conversion time OF
			break;

		case _6u: // ADC10HI
			break;

		case _8u: // ADC10LO
			break;

		case _10u: // ADC10IN
			break;

		case _12u:
			interrupt_event |= ADC_IE;
			
			ADC10CTL0 &= ~ADC10ENC; // turn OFF ENC bit of ADC10CTL0; when ENC=0, can modify ADC10_B
			switch(ADC_CHANNEL_COUNT++){

				case _0u: // channel A0
					ADC_Right_Detector = ADC10MEM0;
					ADC10MCTL0 = ADC10INCH_1; // next channel is A1
					break;

				case _1u: // channel A1
					ADC_Left_Detector = ADC10MEM0;
					ADC10MCTL0 = ADC10INCH_3; // next channel is A3
					break;

				case _2u: // channel A3
					ADC_THUMB = ADC10MEM0;
					ADC10MCTL0 = ADC10INCH_0; // next channel is A0
					ADC_CHANNEL_COUNT = _0u;
					break;

				default:break;
			}

			//ADC10CTL0 |= ADC10ENC; // ENC=1 in order to start any conversion
			//ADC10CTL0 |= ADC10SC; // start next sample
			ADC10CTL0 |= ADC10ENC + ADC10SC;
			break;

		default: break;

	}
}