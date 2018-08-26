/******************************************************************************
File Name: init.c

Description: This file contains the initialization for several functions 
             (interrupts, Timers, ADC). 

Author: Michael Patel
Date: October 2016
Compiler: Built with IAR Embedded Workbench Version: V7.4.2.4369 (6.50.1)
*******************************************************************************
*/

#include "msp430.h"
#include "functions.h"
#include "macros.h"

extern char display_line_1[LCD_display_line_size];
extern char display_line_2[LCD_display_line_size];
extern char display_line_3[LCD_display_line_size];
extern char display_line_4[LCD_display_line_size];
extern char *display_1;
extern char *display_2;
extern char *display_3;
extern char *display_4;
extern volatile char USB_RX[_8u];
extern volatile char IOT_RX[_5u];
extern unsigned int baud_rate;
extern unsigned int baud_rate_remainder;
extern volatile char RX_ASCII_information[_6u];
extern volatile char command[_3u];
extern volatile char FRAMcommand;


/*
================================================================================
Function Name: Init_Conditions

Description: This function enables interrupts

Passed: none
Locals: none
Returned: none
Globals: display_line_1, display_line_2, display_line_3, display_line_4, display_1, display_2, display_3, display_4

Author: Michael Patel
Date: September 2016
Compiler: Built with IAR Embedded Workbench Version: V7.4.2.4369 (6.50.1)
================================================================================
*/
void Init_Conditions(void){
//------------------------------------------------------------------------------
// Initializations Configurations
//------------------------------------------------------------------------------
// Interrupts are disabled by default, enable them.
  enable_interrupts();
  display_1 = &display_line_1[LCD_IDX_0];
  display_2 = &display_line_2[LCD_IDX_0];
  display_3 = &display_line_3[LCD_IDX_0];
  display_4 = &display_line_4[LCD_IDX_0];

}



/*
================================================================================
Function Name: Init_ADC()

Description: This function configures the ADC (ADC10_B)

Passed: none
Locals: none
Returned: none
Globals: none

Author: Michael Patel
Date: October 2016
Compiler: Built with IAR Embedded Workbench Version: V7.4.2.4369 (6.50.1)
================================================================================
*/
// Configure ADC10_B
void Init_ADC(void){
  ADC10CTL0 = RESET_STATE; // Clear ADC10CTL0
  ADC10CTL0 |= ADC10SHT_2; // 16 ADC clocks
  ADC10CTL0 &= ~ADC10MSC; // Single Sequence
  ADC10CTL0 |= ADC10ON; // ADC ON - Core Enabled

  ADC10CTL1 = RESET_STATE; // Clear ADC10CTL1
  ADC10CTL1 |= ADC10SHS_0; // ADC10SC bit
  ADC10CTL1 |= ADC10SHP; // SAMPCON signal sourced from sampling timer
  ADC10CTL1 &= ~ADC10ISSH; // The sample-input signal is not inverted.
  ADC10CTL1 |= ADC10DIV_0; // ADC10_B clock divider – Divide by 1.
  ADC10CTL1 |= ADC10SSEL_0; // MODCLK
  ADC10CTL1 |= ADC10CONSEQ_0; // Single-channel, single-conversion

  ADC10CTL2 = RESET_STATE; // Clear ADC10CTL2
  ADC10CTL2 |= ADC10DIV_0; // Pre-divide by 1
  ADC10CTL2 |= ADC10RES; // 10-bit resolution
  ADC10CTL2 &= ~ADC10DF; // Binary unsigned
  ADC10CTL2 &= ~ADC10SR; // supports up to approximately 200 ksps
  
  ADC10MCTL0 = RESET_STATE; // Clear ADC10MCTL0
  ADC10MCTL0 |= ADC10SREF_0; // V(R+) = AVCC and V(R-) = AVSS
  ADC10MCTL0 |= ADC10INCH_0; // Channel A0 Right Detect
  //ADC10MCTL0 |= ADC10INCH_1; // Channel A1 Left Detect  
  //ADC10MCTL0 |= ADC10INCH_3; // Channel A3 Thumb Wheel
  ADC10IE |= ADC10IE0; // Enable ADC conversion complete interrupt
}



/*
================================================================================
Function Name: Init_Serial_UCA0()

Description: This function initializes serial UCA0

Passed: none
Locals: none
Returned: none
Globals: none

Author: Michael Patel
Date: November 2016
Compiler: Built with IAR Embedded Workbench Version: V7.4.2.4369 (6.50.1)
================================================================================
*/
void Init_Serial_UCA0(void){
  //int i;

  clearFRAMcommand();

  // clear USB_RX[]
  /*
  for(i=_0u; i<_16u; i++){
    USB_RX[i] = _0u;
  }
  */

  // Configure UART A0
  UCA0CTLW0 = _0u; // use word register
  UCA0CTLW0 |= UCSSEL__SMCLK; // select SMCLK
  UCA0CTLW0 |= UCSWRST; // set software Reset enable
  UCA0BRW = baud_rate;
  UCA0MCTLW = baud_rate_remainder; 
  UCA0CTLW0 &= ~UCSWRST; // release from Reset
  UCA0IE |= UCRXIE; // Enable RX Interrupt
}


/*
================================================================================
Function Name: Init_Serial_UCA1()

Description: This function initializes serial UCA1

Passed: none
Locals: none
Returned: none
Globals: none

Author: Michael Patel
Date: November 2016
Compiler: Built with IAR Embedded Workbench Version: V7.4.2.4369 (6.50.1)
================================================================================
*/
void Init_Serial_UCA1(void){
  //int i;

  clearWEBcommand();
  // clear IOT_RX[]
  /*
  for(i=_0u; i<sizeof(RX_ASCII_information); i++){
    RX_ASCII_information[i] = _0u;
  }
  */

  // Configure UART A1
  UCA1CTLW0 = _0u; //use word register
  UCA1CTLW0 |= UCSSEL__SMCLK; // select SMCLK
  UCA1CTLW0 |= UCSWRST; // set Reset enable
  UCA1BRW = baud_rate; //
  UCA1MCTLW = baud_rate_remainder;
  UCA1CTLW0 &= ~UCSWRST; // release from Reset
  UCA1IE |= UCRXIE; // Enable RX Interrupt
}
