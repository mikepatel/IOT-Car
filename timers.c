/******************************************************************************
File Name: timers.c

Description: This file contains the functions for timing operations.

Author: Michael Patel
Date: September 2016
Compiler: Built with IAR Embedded Workbench Version: V7.4.2.4369 (6.50.1)
*******************************************************************************
*/

#include "msp430.h"
#include "functions.h"
#include "macros.h"

extern volatile unsigned int Time_Sequence;
extern volatile char one_time;
extern volatile unsigned int five_msec_count;
extern volatile unsigned int OF_counter;
extern volatile unsigned int interrupt_event;


/*
================================================================================
Function Name: Init_Timers()

Description: This function initializes the timers.

Passed: none
Locals: none
Returned: none
Globals: none

Author: Michael Patel
Date: September 2016
Compiler: Built with IAR Embedded Workbench Version: V7.4.2.4369 (6.50.1)
================================================================================
*/
void Init_Timers(void){
//------------------------------------------------------------------------------
// Timer Configurations
//------------------------------------------------------------------------------
  Init_Timer_A0(); //
//  Init_Timer_A1(); //
//  Init_Timer_B0(); //
  Init_Timer_B1(); //
  //Init_Timer_B2();   //  Required for provided compiled code to work
//------------------------------------------------------------------------------
}


/*
================================================================================
Function Name: Init_Timer_A0()

Description: This function initializes Timer_A0 for both A0_0 and A0_1, A0_2

Passed: none
Locals: none
Returned: none
Globals: none

Author: Michael Patel
Date: September 2016
Compiler: Built with IAR Embedded Workbench Version: V7.4.2.4369 (6.50.1)
================================================================================
*/
void Init_Timer_A0(void){
  TA0CTL = TASSEL__SMCLK; // select SMCLK source
  TA0CTL |= TACLR; // Resets TA0R, Clock divider, count direction
  
  TA0CTL |= MC__UP; // Timer Mode Control: Up from 0x0000 to TAxCCR0
  
  TA0CTL |= ID__8; // Divide clock by 8
  TA0EX0 = TAIDEX_7; // Divide clock by additional 8

  // CCR0
  TA0CCR0 = TA0CCR0_INTERVAL; // CCR0: Capture Compare Register0
  TA0CCTL0 |= CCIE; // CCR0 Enable Interrupt

  // CCR1
  // TA0CCR1 = TA0CCR1_INTERVAL; // CCR1
  // TA0CCTL1 |= CCIE; // CCR1 Enable Interrupt

  // CCR2
  // TA0CCR2 = TA0CCR2_INTERVAL; // CCR2
  // TA0CCTL2 |= CCIE; // CCR2 Enable Interrupt

  // OVERFLOW
  TA0CTL &= ~TAIE; // Disable overflow interrupt
  TA0CTL &= ~TAIFG; // Clear overflow Interrupt Flag
}


/***********************************************************************************
Function Name: Init_Timer_B1()

Description: This function initializes Timer_B1 for both B1_0 and B1_1, B1_2, OF

Passed: none
Locals: none
Returned: none
Globals: 

Author: Michael Patel
Date: September 2016
Compiler: Built with IAR Embedded Workbench Version: V7.4.2.4369 (6.50.1)
*/
void Init_Timer_B1(void){
  TB1CTL = TBSSEL__SMCLK; // select SMCLK source
  TB1CTL |= TBCLR; // clear

  TB1CTL |= MC__UP; // Timer Mode Control: Up from 0x0000 to TBxCCR0

  //right_forward_rate = OFF;
  //left_forward_rate = OFF;

  // CCR0
  TB1CCR0 = WHEEL_PERIOD; // PWM Period, INTERVAL

  // CCR1
  TB1CCTL1 = OUTMOD_7; // CCR1 reset/set
  TB1CCR1 = OFF; // R_FORWARD PWM duty cycle

  // CCR2
  TB1CCTL2 = OUTMOD_7; // CCR2 reset/set
  TB1CCR2 = OFF; // L_FORWARD PWM duty cycle

  // OVERFLOW
  TB1CTL &= ~TBIE; // Disable overflow interrupt
  TB1CTL &= ~TBIFG; // Clear overflow Interrupt Flag

}



/***********************************************************************************
Function Name: Init_Timer_B1()

Description: This function initializes Timer_B2 for both B2_0 and B2_1, B2_2, OF

Passed: none
Locals: none
Returned: none
Globals: 

Author: Michael Patel
Date: September 2016
Compiler: Built with IAR Embedded Workbench Version: V7.4.2.4369 (6.50.1)

void Init_Timer_B2(void){
  TB2CTL = TBSSEL__SMCLK; // select SMCLK source
  TB2CTL |= TBCLR; // clear

  TB2CTL |= MC__UP; // Timer Mode Control: Up from 0x0000 to TBxCCR0

  //right_forward_rate = OFF;
  //left_forward_rate = OFF;

  // CCR0
  TB2CCR0 = WHEEL_PERIOD; // PWM Period, INTERVAL

  // CCR1
  TB2CCTL1 = OUTMOD_7; // CCR1 reset/set
  TB2CCR1 = OFF; // R_FORWARD PWM duty cycle

  // CCR2
  TB2CCTL2 = OUTMOD_7; // CCR2 reset/set
  TB2CCR2 = OFF; // L_FORWARD PWM duty cycle

  // OVERFLOW
  TB2CTL &= ~TBIE; // Disable overflow interrupt
  TB2CTL &= ~TBIFG; // Clear overflow Interrupt Flag

  //TB2CCTL1 |= CCIE; // Enable TimerB2.1 Interrupt
}
*/

//------------------------------------------------------------------------------

/*
================================================================================
Function Name: Toggle_LCD_100ms()

Description: This function makes the LCD BACKLITE blink once every second for 4 seconds.

Passed: none
Locals: none
Returned: none
Globals: 

Author: Michael Patel
Date: September 2016
Compiler: Built with IAR Embedded Workbench Version: V7.4.2.4369 (6.50.1)
================================================================================
*/
/*
void Toggle_LCD_100ms(void){
  OF_counter++;
  P1OUT &= ~LCD_BACKLITE;
  interrupt_event = NONE;
  
  if(OF_counter > MAX_COUNT){
    OF_counter = INITIAL_VALUE_TO_ZERO;
    TA0CCTL0 &= ~CCIE; // disable TimerA0 interrupt
    P1OUT &= ~LCD_BACKLITE;
  }

  else if(!(OF_counter % MODULO_10)){
    P1OUT ^= LCD_BACKLITE;
  }
  
  P4IE |= SW1; // enable SW1 interrupt
  P4IE |= SW2; // enable SW2 interrupt
}
*/

/*
================================================================================
Function Name: Five_msec_Delay()

Description: This function takes in a count value and delays for 5ms times that
             count value.

Passed: unsigned int fivemsec
Locals: none
Returned: none
Globals: none

Author: Michael Patel
Date: September 2016
Compiler: Built with IAR Embedded Workbench Version: V7.4.2.4369 (6.50.1)
================================================================================
*/
/*
void Five_msec_Delay(unsigned int fivemsec){
  //Each count passed is at least x times 5 milliseconds
  five_msec_count = WAIT_0;
  while(fivemsec > (five_msec_count++));
}
*/

/*
================================================================================
Function Name: five_msec_sleep

Description: This function takes in a count value and sleeps for 5ms times
             that count value

Passed: unsigned int fivemsec
Locals: none
Returned: none
Globals: five_msec_count

Author: Michael Patel
Date: September 2016
Compiler: Built with IAR Embedded Workbench Version: V7.4.2.4369 (6.50.1)
================================================================================
*/
/*
void five_msec_sleep(unsigned int fivemsec){
//------------------------------------------------------------------------------
//Each count passed is at least x times 5 milliseconds
  five_msec_count = WAIT_0;
  while(fivemsec > (five_msec_count+1));
//------------------------------------------------------------------------------
}
*/

/*
Function Name: Timer_code()

Description: This function acts as the A0 interrupt

Passed: none
Locals: none
Returned: none
Globals: Time_Sequence, one_time, five_msec_count

Author: Michael Patel
Date: September 2016
Compiler: Built with IAR Embedded Workbench Version: V7.4.2.4369 (6.50.1)
*/
/*
void Timer_code(void){
//------------------------------------------------------------------------------
// Timer A0 interrupt code
//------------------------------------------------------------------------------
  Time_Sequence++;
  one_time = ONE_TIME_ZERO;
  if (five_msec_count < WAIT_1000){
    five_msec_count++;
  }
//------------------------------------------------------------------------------
}
*/
