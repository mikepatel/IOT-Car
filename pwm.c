/******************************************************************************
File Name: pwm.c

Description: This file contains the functions for pwm.

Author: Michael Patel
Date: October 2016
Compiler: Built with IAR Embedded Workbench Version: V7.4.2.4369 (6.50.1)
*******************************************************************************
*/

#include  "msp430.h"
#include  "functions.h"
#include  "macros.h"


  /*
  ================================================================================
  Function Name: Forward()

  Description: This function moves the vehicle forward

  Passed: none
  Locals: none
  Returned: none
  Globals: none

  Author: Michael Patel
  Date: October 2016
  Compiler: Built with IAR Embedded Workbench Version: V7.4.2.4369 (6.50.1)
  ================================================================================
  */
void Forward(void){
	TB1CCR1 = WHEEL_PERIOD; // R_FORWARD
  TB1CCR2 = HALF*WHEEL_PERIOD; // L_FORWARD
}


  /*
  ================================================================================
  Function Name: Right()

  Description: This function moves the vehicle to the Right

  Passed: none
  Locals: none
  Returned: none
  Globals: none

  Author: Michael Patel
  Date: October 2016
  Compiler: Built with IAR Embedded Workbench Version: V7.4.2.4369 (6.50.1)
  ================================================================================
  */
void Right(void){
	TB1CCR1 = OFF;
	TB1CCR2 = WHEEL_PERIOD;
}

  /*
  ================================================================================
  Function Name: Left()

  Description: This function moves the vehicle to the Right

  Passed: none
  Locals: none
  Returned: none
  Globals: none

  Author: Michael Patel
  Date: October 2016
  Compiler: Built with IAR Embedded Workbench Version: V7.4.2.4369 (6.50.1)
  ================================================================================
  */
void Left(void){
	TB1CCR1 = WHEEL_PERIOD;
	TB1CCR2 = OFF;
}


/*
================================================================================
Function Name: turnForwardWheelsOFF()

Description: This function turns off all wheels (stopping the vehicle)

Passed: none
Locals: none
Returned: none
Globals: none

Author: Michael Patel
Date: September 2016
Compiler: Built with IAR Embedded Workbench Version: V7.4.2.4369 (6.50.1)
================================================================================
*/
void turnAllWheelsOFF(){
	turnLeftWheelOFF();
	turnRightWheelOFF();
}


/*
================================================================================
Function Name: turnLeftWheelOFF()

Description: This function turns off the Left wheel

Passed: none
Locals: none
Returned: none
Globals: none

Author: Michael Patel
Date: September 2016
Compiler: Built with IAR Embedded Workbench Version: V7.4.2.4369 (6.50.1)
================================================================================
*/
void turnLeftWheelOFF(){
    TB1CCR2 = OFF;
    P3OUT &= ~L_REVERSE;
	//is_L_FORWARD_ON = FALSE;
}

/*
================================================================================
Function Name: turnRightWheelOFF()

Description: This function turns off the Right wheel

Passed: none
Locals: none
Returned: none
Globals: none

Author: Michael Patel
Date: September 2016
Compiler: Built with IAR Embedded Workbench Version: V7.4.2.4369 (6.50.1)
================================================================================
*/
void turnRightWheelOFF(){
	TB1CCR1 = OFF;
  P3OUT &= ~R_REVERSE;
	//is_R_FORWARD_ON = FALSE;
}

/*
================================================================================
Function Name: Backward()

Description: This function moves the vehicle backwards

Passed: none
Locals: none
Returned: none
Globals: none

Author: Michael Patel
Date: September 2016
Compiler: Built with IAR Embedded Workbench Version: V7.4.2.4369 (6.50.1)
================================================================================
*/
void Backward(void){
  P3OUT |= R_REVERSE;
  P3OUT |= L_REVERSE;
}