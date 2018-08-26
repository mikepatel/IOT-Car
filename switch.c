/******************************************************************************
File Name: switch.c

Description: This file contains the functions for the switch inputs

Author: Michael Patel
Date: September 2016
Compiler: Built with IAR Embedded Workbench Version: V7.4.2.4369 (6.50.1)
*******************************************************************************
*/

#include "msp430.h"
#include "functions.h"
#include "macros.h"
#include <string.h>

extern char *display_1;
extern char *display_2;
extern char *display_3;
extern char *display_4;
extern char posL1;
extern char posL2;
extern char posL3;
extern char posL4;
extern volatile unsigned int timerA0_counter;
extern volatile unsigned int timerB1_1_count;
extern unsigned int baud_rate;
extern unsigned int baud_rate_remainder;
extern unsigned int num_sequences;
extern int TX_int_information[6];
extern unsigned int current_sequence;
extern char *AT9600;
extern char *ATflash;
extern char *ATcomMode;

/*
================================================================================
Function Name: SW1_Pressed()

Description: This function handles for when SW1 is pressed.

Passed: none
Locals: none
Returned: none
Globals: display_1, posL1

Author: Michael Patel
Date: September 2016
Compiler: Built with IAR Embedded Workbench Version: V7.4.2.4369 (6.50.1)
================================================================================
*/

void SW1_Pressed(void){
    //display_1 = "9600";
    //setBaudRate(BAUD_RATE_9600, BAUD_RATE_REMAINDER_9600);
    //send = "AT+S.SCFG=console1_speed,9600\r";
    
    /*
    out_character(AT9600, strlen(AT9600)); // send to IOT
    out_character(ATflash, strlen(ATflash));
    baud_rate = BAUD_RATE_9600;
    baud_rate_remainder = BAUD_RATE_REMAINDER_9600;
    Init_Serial_UCA1();
    out_character(ATcomMode, strlen(ATcomMode));
    PJOUT &= ~IOT_RESET;
    PJOUT |= IOT_RESET; // come out of IOT Reset
    */
    //TA0CCTL0 |= CCIE; // CCR0 Enable Interrupt
    //baud_rate = BAUD_RATE_9600;
    //baud_rate_remainder = BAUD_RATE_REMAINDER_9600;
    //Init_Serial_UCA1();
    /*
    int intArray[_6u];

    current_sequence++;

    intArray[_0u] = current_sequence;
    intArray[_4u] = intArray[_3u] = intArray[_2u] = intArray[_1u] = _0u;
    intArray[_5u] = _1u;

    PrepForTXandDisplay(intArray);
    */


    // turn ON the IR_LED
    // and then begin sampling
    /*
    P3OUT |= IR_LED;
    display_1 = "ON";
    posL1 = INDENT_2SPACE;
    */

    // SW 1 - will kick off ADC Interrupt and Timer Interrupts
    //ADC10CTL0 |= ADC10ENC + ADC10SC; // Enable and start ADC conversion

    //timerA0_counter = _0u; // set TimerA0.0 user counter to 0
    //TA0CCTL0 |= CCIE; // Enable TimerA0.0 Interrupt

    //timerB1_1_count = _0u; // set TimerB1.1 user counter to 0
    //TB1CCTL1 |= CCIE; // Enable TimerB1.1 Interrupt

    //Forward(); // travel forward indefinitely upon SW 1 press
    

    // Homework 8
    //baud_rate = BAUD_RATE_115200; // Baud Rate: 115,200
    //baud_rate_remainder = BAUD_RATE_REMAINDER_115200;
    //Init_Serial_UCA0();

    //baud_rate = BAUD_RATE_9600; // Baud Rate: 9,600
    //baud_rate_remainder = BAUD_RATE_REMAINDER_9600;
    //Init_Serial_UCA1();

    /*
    display_1 = "";
    display_2 = "";
    display_3 = "Baud";
    display_4 = "115200";
    Display_Process();
    // transmit "NCSU  #1"
    */

}



/*
================================================================================
Function Name: SW2_Pressed()

Description: This function handles for when SW2 is pressed.

Passed: none
Locals: none
Returned: none
Globals: display_1, posL1

Author: Michael Patel
Date: September 2016
Compiler: Built with IAR Embedded Workbench Version: V7.4.2.4369 (6.50.1)
================================================================================
*/
void SW2_Pressed(void){
    //display_1 = "115200";
    //baud_rate = BAUD_RATE_115200; // Baud Rate: 
    //baud_rate_remainder = BAUD_RATE_REMAINDER_115200;
    //Init_Serial_UCA1();
    //PJOUT |= IOT_RESET;

    // turn OFF the IR_LED
    // and then begin sampling
    /*
    P3OUT &= ~IR_LED;
    display_1 = "OFF";
    ADC10CTL0 |= ADC10ENC + ADC10SC;
    posL1 = INDENT_2SPACE;
    */

    // Homework 8
    //baud_rate = BAUD_RATE_9600; // Baud Rate: 9,600
    //baud_rate_remainder = BAUD_RATE_REMAINDER_9600;
    //Init_Serial_UCA0();
    //Init_Serial_UCA1();

    /*
    display_1 = "";
    display_2 = "";
    display_3 = "Baud";
    display_4 = "9600";
    Display_Process();
    */
}


