/******************************************************************************
File Name: interrupts_timers.c

Description: This file contains the Timer ISRs

Author: Michael Patel
Date: September 2016
Compiler: Built with IAR Embedded Workbench Version: V7.4.2.4369 (6.50.1)
*******************************************************************************
*/

#include  "msp430.h"
#include  "functions.h"
#include  "macros.h"

extern volatile unsigned int OF_counter;
extern volatile unsigned int interrupt_event;
extern volatile unsigned int timerA0_counter;
extern volatile unsigned int timerB1_1_count;
extern volatile unsigned int timerB2_1_count;

/******************************************************************************
TimerA0: CCR0 Interrupt handler

Description: This interrupt handles TimerA0 interrupt events.

Author: Michael Patel
Date: September 2016
Compiler: Built with IAR Embedded Workbench Version: V7.4.2.4369 (6.50.1)
*/
#pragma vector=TIMER0_A0_VECTOR
__interrupt void TimerA0_0_ISR(void){
	if(TA0CTL & CCIFG){
		timerA0_counter++;
		interrupt_event |= TimerA0_0_IE;
		TA0CTL &= ~CCIFG; // clear Interrupt Flag
	}
}


/******************************************************************************
TimerA0: CCR1, CCR2, Overflow Interrupt Vector (TAIV) handler
*/
/*
#pragma vector=TIMER0_A1_VECTOR
__interrupt void TIMERA0_1_ISR(void){
	switch(__even_in_range(TA0IV, 14)){
		case 0:				// No Interrupt
			break;

		case 2:				// CCR1 not used
			//
			// <ADD CODE>
			TA0CCR1 += TA0CCR1_INTERVAL; // add offset to TACCR1
			break;

		case 4:				// CCR2 not used
			//
			// <ADD CODE>
			TA0CCR2 += TA0CCR2_INTERVAL; // add offset to TACCR2
			break;

		case 14:			// overflow
			//
			// <ADD CODE>
			break;

		default:
			break;

	}
}
*/

/******************************************************************************
Timer A1: CCR0 Interrupt Handler

Description: This interrupt handles TimerA1 Reg0 interrupt events.

Author: Michael Patel
Date: October 2016
Compiler: Built with IAR Embedded Workbench Version: V7.4.2.4369 (6.50.1)

#pragma vector=TIMER1_A0_VECTOR
__interrupt void TimerA1_0_ISR(void){

}
*/

/******************************************************************************
Timer A1: CCR1, CCR2, OF Interrupt Handler

Description: This interrupt handles TimerA1 Reg1,2,OF interrupt events.

Author: Michael Patel
Date: October 2016
Compiler: Built with IAR Embedded Workbench Version: V7.4.2.4369 (6.50.1)

#pragma vector=TIMER1_A1_VECTOR
__interrupt void TimerA1_1_ISR(void){
	switch(__even_in_range(TA1IV, 14)){
		case 0:				// No Interrupt
			break;

		case 2:				// CCR1 not used
			//
			// <ADD CODE>
			break;

		case 4:				// CCR2 not used
			//
			// <ADD CODE>
			break;

		case 6: // reserved
			break;

		case 8: // reserved
			break;

		case 10: // reserved
			break;

		case 12: // reserved
			break;

		case 14:			// overflow
			//
			// <ADD CODE>
			break;

		default:
			break;
	}
}

*/


/******************************************************************************
Timer B0: CCR0 Interrupt Handler

Description: This interrupt handles TimerB0 Reg0 interrupt events.

Author: Michael Patel
Date: October 2016
Compiler: Built with IAR Embedded Workbench Version: V7.4.2.4369 (6.50.1)

#pragma vector=TIMER0_B0_VECTOR
__interrupt void TimerB0_0_ISR(void){

}
*/


/******************************************************************************
Timer B0: CCR1, CCR2, OF (TBIV) Handler

Description: This interrupt handles TimerB0 Reg1,2,OF interrupt events.

Author: Michael Patel
Date: October 2016
Compiler: Built with IAR Embedded Workbench Version: V7.4.2.4369 (6.50.1)

#pragma vector=TIMER0_B1_VECTOR
__interrupt void TimerB0_1_ISR(void){
	switch(__even_in_range(TB0IV, 14)){
		case 0:				// No Interrupt
			break;

		case 2:				// CCR1 not used
			//
			// <ADD CODE>
			break;

		case 4:				// CCR2 not used
			//
			// <ADD CODE>
			break;

		case 6: // reserved
			break;

		case 8: // reserved
			break;

		case 10: // reserved
			break;

		case 12: // reserved
			break;

		case 14:			// overflow
			//
			// <ADD CODE>
			break;

		default:
			break;
	}
}
*/


/******************************************************************************
Timer B1: CCR0 Interrupt Handler

Description: This interrupt handles TimerB1 Reg0 interrupt events.

Author: Michael Patel
Date: October 2016
Compiler: Built with IAR Embedded Workbench Version: V7.4.2.4369 (6.50.1)

#pragma vector=TIMER1_B0_VECTOR
__interrupt void TimerB1_0_ISR(void){

}
*/

/******************************************************************************
Timer B1: CCR1, CCR2, OF (TBIV) Handler

Description: This interrupt handles TimerB1 Reg1,2,OF interrupt events.

Author: Michael Patel
Date: October 2016
Compiler: Built with IAR Embedded Workbench Version: V7.4.2.4369 (6.50.1)
*/
#pragma vector=TIMER1_B1_VECTOR
__interrupt void TimerB1_1_ISR(void){
	switch(__even_in_range(TB1IV, 14)){

		case 0:				// No Interrupt
			break;

		case 2:				// CCR1 not used
			// TB1.1 R_FORWARD
			if(TB1CTL & CCIFG){
				timerB1_1_count++;
				interrupt_event |= TimerB1_1_IE;
				TB1CTL &= ~CCIFG;
			}
			
			break;

		case 4:				// CCR2 not used
			// TB1.2 L_FORWARD
			if(TB1CTL & CCIFG){
				interrupt_event |= TimerB1_1_IE;;
				TB1CTL &= ~CCIFG;
			}
			break;

		case 6: // reserved
			break;

		case 8: // reserved
			break;

		case 10: // reserved
			break;

		case 12: // reserved
			break;

		case 14:			// overflow
			//
			// <ADD CODE>
			break;

		default:
			break;

	}
}


/******************************************************************************
Timer B2: CCR0 Interrupt Handler

Description: This interrupt handles TimerB2 Reg0 interrupt events.

Author: Michael Patel
Date: October 2016
Compiler: Built with IAR Embedded Workbench Version: V7.4.2.4369 (6.50.1)

#pragma vector=TIMER2_B0_VECTOR
__interrupt void TimerB2_0_ISR(void){

}
*/



/******************************************************************************
Timer B2: CCR1, CCR2, OF (TBIV) Handler

Description: This interrupt handles TimerB2 Reg1,2,OF interrupt events.

Author: Michael Patel
Date: October 2016
Compiler: Built with IAR Embedded Workbench Version: V7.4.2.4369 (6.50.1)


#pragma vector=TIMER2_B1_VECTOR
__interrupt void TimerB2_1_ISR(void){
	switch(__even_in_range(TB2IV, 14)){
		case 0:				// No Interrupt
			break;

		case 2:				// CCR1 not used
			// TB2.1 R_REVERSE
			if(TB2CTL & CCIFG){
				timerB2_1_count++;
				interrupt_event = TimerB2_1_IE;
				TB2CTL &= ~CCIFG;
			}
			break;

		case 4:				// CCR2 not used
			// TB2.2 L_REVERSE
			if(TB2CTL & CCIFG){
				interrupt_event = TimerB2_1_IE;
				TB2CTL &= ~CCIFG;
			}

			break;

		case 6: // reserved
			break;

		case 8: // reserved
			break;

		case 10: // reserved
			break;

		case 12: // reserved
			break;

		case 14:			// overflow
			//
			// <ADD CODE>
			break;

		default:
			break;
	}
}
*/