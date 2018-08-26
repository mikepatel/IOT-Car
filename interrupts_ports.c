/******************************************************************************
File Name: interrupts_ports.c

Description: This file contains the switch_interrupts for SW1 and SW2

Author: Michael Patel
Date: September 2016
Compiler: Built with IAR Embedded Workbench Version: V7.4.2.4369 (6.50.1)
*******************************************************************************
*/

#include  "msp430.h"
#include  "functions.h"
#include  "macros.h"

extern volatile unsigned int interrupt_event;


/******************************************************************************
Port4 Interrupt. For Switches, they are disabled for the duration of the debounce
timer. Flag is set that user can check.

Description: This interrupt handles SW1 and SW2 interrupt events

Author: Michael Patel
Date: September 2016
Compiler: Built with IAR Embedded Workbench Version: V7.4.2.4369 (6.50.1)
*/

#pragma vector=PORT4_VECTOR
__interrupt void switch_interrupt(void){

	// SW1
	if(P4IFG & SW1){
		interrupt_event |= SW1_IE;
		P4IE &= ~SW1;
		P4IFG &= ~SW1; // clear SW1 Interrupt Flag
	}

	// SW2
	if(P4IFG & SW2){
		interrupt_event |= SW2_IE;
		P4IE &= ~SW2;
		P4IFG &= ~SW2; // clear SW2 Interrupt Flag
	}
	
}