/******************************************************************************
File Name: ports.c

Description: This file contains the initialization for all port pins. The function
             Init_Ports calls five more functions to initialize each port 
             individually using Init_Port1, Init_Port2, Init_Port3, Init_Port4
             and Init_PortJ

Author: Michael Patel
Date: September 2016
Compiler: Built with IAR Embedded Workbench Version: V7.4.2.4369 (6.50.1)
*******************************************************************************
*/

#include  "msp430.h"
#include  "functions.h"
#include  "macros.h"

/*
Function Name: Init_Ports

Description: This function calls functions to initialize the individual ports 1,2,3,4,J

Passed: none
Locals: none
Returned: none
Globals: none

Author: Michael Patel
Date: September 2016
Compiler: Built with IAR Embedded Workbench Version: V7.4.2.4369 (6.50.1)
*/
void Init_Ports(void){
	Init_Port1();
	Init_Port2();
	Init_Port3();
	Init_Port4();
	Init_PortJ(USE_IOT_WAKEUP); // use IOT_WAKEUP during initialization
}

/*
================================================================================
PORT 1
================================================================================
        ---------------------------------------------------------------------------------------------
        Signal Name			Function			P1DIR.x		SEL1	SEL0
        ---------------------------------------------------------------------------------------------
P1.0	V_DETECT_R			GPIO				I:0 O:1		0	0
					TA0.CCI1A			0		0	1
					TA0.1				1		0	1
					DMAE0				0		1	0
					RTCCLK				1		1	0
					A0				x		1	1
					CD0				x		1	1
					VeREF-				x		1	1
	---------------------------------------------------------------------------------------------
P1.1	V_DETECT_L			GPIO				I:0 O:1		0	0
					TA0.CCI2A			0		0	1
					TA0.2				1		0	1
					TA1CLK				0		1	0
					CDOUT				1		1	0
					A1				x		1	1
					CD1				x		1	1
					VeREF+				x		1	1
	---------------------------------------------------------------------------------------------
P1.2	LCD_BACKLITE		        GPIO				I:0 O:1		0	0
					TA1.CCI1A			0		0	1
					TA1.1				1		0	1
					TA0CLK				0		1	0
					CDOUT				1		1	0
					A2				x		1	1
					CD2				x		1	1
	---------------------------------------------------------------------------------------------
P1.3	V_THUMB				GPIO				I:0 O:1		0	0
					TA1.CCI2A			0		0	1
					TA1.2				1		0	1
					UCB0STE				x		1	0
					A3				x		1	1
					CD3				x		1	1
	---------------------------------------------------------------------------------------------
P1.4	SPI_CS_LCD			GPIO				I:0 O:1		0	0
					TB0.CCI1A			0		0	1
					TB0.1				1		0	1
					UCA0STE				x		1	0
					A4				x		1	1
					CD4				x		1	1
	---------------------------------------------------------------------------------------------
P1.5	RESET_LCD			GPIO				I:0 O:1		0	0
					TB0.CCI2A			0		0	1
					TB0.2				1		0	1
					UCA0CLK				x		1	0
					A5				x		1	1
					CD5				x		1	1
	---------------------------------------------------------------------------------------------
P1.6	SPI_SIMO			GPIO				I:0 O:1		0	0
					TB1.CCI1A	                0	        0	1
					TB1.1		                1		0	1
					UCB0SIMO/UCB0SDA                x		1	0
					TA0.CCI0A			0		1	1
					TA0.0				1		1	1
	---------------------------------------------------------------------------------------------
P1.7	SPI_SOMI			GPIO				I:0 O:1		0	0
					TB1.CCI2A			0		0	1
					TB1.2				1		0	1
					UCB0SOMI/UCB0SCL	        x		1	0
					TA1.CCI0A			0		1	1
					TA1.0				1		1	1
	---------------------------------------------------------------------------------------------

=========================================================================
PORT 2
=========================================================================
	---------------------------------------------------------------------------------------------
	Signal Name			Function			P1DIR.x		SEL1	SEL0
	---------------------------------------------------------------------------------------------
P2.0	USB_TXD				GPIO				I:0 O:1		0	0
					TB2.CCI0A			0		0	1
					TB2.0				1		0	1
					UCA0TXD/UCA0SIMO	        x		1	0
					TB0CLK				0		1	1
					ACLK				1		1	1
	---------------------------------------------------------------------------------------------
P2.1	USB_RXD				GPIO				I:0 O:1		0	0
					TB2.CCI1A			0		0	1
					TB2.1				1		0	1
					UCA0RXD/UCA0SOMI	        x		1	0
					TB0.CCI0A			0		1	1
					TB0.0				1		1	1
	---------------------------------------------------------------------------------------------
P2.2	SPI_SCK				GPIO				I:0 O:1		0	0
					TB2.CCI2A			0		0	1
					TB2.2				1		0	1
					UCB0CLK				x		1	0
					TB1.CCI0A			0		1	0
					TB1.0				1		1	1
	---------------------------------------------------------------------------------------------
P2.3	UNKNOWN				GPIO				I:0 O:1		0	0
					TA0.CCI0B			0		0	1
					TA0.0				1		0	1
					UCA1STE				x		1	0
					A6				x		1	1
					CD10				x		1	1
	---------------------------------------------------------------------------------------------
P2.4	UNKNOWN				GPIO				I:0 O:1		0	0
					TA1.CCI0B			0		0	1
					TA1.0				1		0	1
					UCA1CLK				x		1	0
					A7				x		1	0
					CD11				x		1	1
	---------------------------------------------------------------------------------------------
P2.5	CPU_TXD				GPIO				I:0 O:1		0	0
					TB0.CCI0B			0		0       1
					TB0.0				1		0	1
					UCA1TXD/UCA1SIMO	        x		1	0
	---------------------------------------------------------------------------------------------
P2.6	CPU_RXD				GPIO				I:0 O:1		0	0
					TB1.CCI0B			0		0	1
                                        TB1.0				1		0	1
					UCA1RXD/UCA1SOMI	        x		1	0
	---------------------------------------------------------------------------------------------
P2.7	UNKNOWN				GPIO				I:0 O:1		0	0

=========================================================================
PORT 3
=========================================================================
	---------------------------------------------------------------------------------------------
        Signal Name			Function			P1DIR.x		SEL1	SEL0
	---------------------------------------------------------------------------------------------
P3.0	X 				GPIO		        	I:0 O:1		0	0
                                        A12	        		x 		1	1
					CD12	        		x 		1	1
	---------------------------------------------------------------------------------------------
P3.1	Y				GPIO	        		I:0 O:1		0	0
					A13	        		x 		1	1
					CD13	        		x 		1	1
	---------------------------------------------------------------------------------------------
P3.2	Z				GPIO	        		I:0 O:1		0	0
					A14     		        x 		1	1
					CD14    			x 		1	1
	---------------------------------------------------------------------------------------------
P3.3	IR_LED				GPIO				I:0 O:1		0	0
					A15				x 		1	1
					CD15				x 		1	1
	---------------------------------------------------------------------------------------------
P3.4	R_FORWARD			GPIO				I:0 O:1		0	0
					TB1.CCI1B			0		0	1
					TB1.1				1		0	1
					TB2CLK				0		1	1
					SMCLK				1		1	1
	---------------------------------------------------------------------------------------------
P3.5	L_FORWARD			GPIO				I:0 O:1		0	0
					TB1.CCI2B			0		0	1
					TB1.2				1		0	1
					CDOUT				1		1	1
	---------------------------------------------------------------------------------------------
P3.6	R_REVERSE			GPIO				I:0 O:1		0	0
					TB2.CCI1B			0		0	1
					TB2.1				1		0	1
					TB1CLK				0		1	1
	---------------------------------------------------------------------------------------------
P3.7	L_REVERSE			GPIO				I:0 O:1		0	0
					TB2.CCI2B			0		0	1
					TB2.2				1		0	1
	---------------------------------------------------------------------------------------------

=========================================================================
PORT 4
=========================================================================
	---------------------------------------------------------------------------------------------
	Signal Name			Function			P1DIR.x		SEL1	SEL0
	---------------------------------------------------------------------------------------------
P4.0	SW1					GPIO			I:0 O:1		0	0
						TB2.CCI0B		0		0	1
						TB2.0			1		0	1
	---------------------------------------------------------------------------------------------
P4.1	SW2					GPIO			I:0 O:1		0	0
	---------------------------------------------------------------------------------------------

=========================================================================
PORT J
=========================================================================	
	---------------------------------------------------------------------------------------------
	Signal Name			Function			P1DIR.x		SEL1	SEL0
	---------------------------------------------------------------------------------------------
PJ.0	IOT_WAKEUP			GPIO				I:0 O:1		0	0
					TDO				x 		x 	x
					TB0OUTH				0		0	1
					SMCLK				1		0	1
					CD6				x 		1	1
	---------------------------------------------------------------------------------------------
PJ.1	IOT_FACTORY			GPIO				I:0 O:1		0	0
					TDI/TCLK 			x 		x 	x
					TB1OUTH				0		0	1
					MCLK				1		0	1
					CD7				x 		1	1
	---------------------------------------------------------------------------------------------
PJ.2	IOT_STA_MINIAP		        GPIO				I:0 O:1		0	0
					TMS				x 		x 	x
					TB2OUTH				0		0	1
					ACLK				1		0	1
					CD8				x 		1	1
	---------------------------------------------------------------------------------------------
PJ.3	IOT_RESET			GPIO				I:0 O:1		0	0
					TCK 				x 		x 	x
					CD9				x 		1	1
	---------------------------------------------------------------------------------------------		
*/
/*
Function Name: Init_Port1

Description: This function initializes port 1 pins

Passed: none
Locals: none
Returned: none
Globals: none

Author: Michael Patel
Date: September 2016
Compiler: Built with IAR Embedded Workbench Version: V7.4.2.4369 (6.50.1)
*/
void Init_Port1(void){
	/*
	---------------------------------------------------------------------------------
	Configure Port 1

	V_DETECT_R				(0x01) // Voltage from Right Detector, P1.0
	V_DETECT_L				(0x02) // Voltage from Left Detector, P1.1
	LCD_BACKLITE			        (0x04) // LCD Backlite, P1.2
	V_THUMB					(0x08) // Voltage from Thumb Wheel, P1.3
	SPI_CS_LCD				(0x10) // LCD Chip Select, P1.4
	RESET_LCD				(0x20) // LCD Reset, P1.5
	SIMO_B					(0x40) // SPI mode - Slave In/Master Out of USCI_B0, P1.6
	SOMI_B					(0x80) // SPI mode - Slave Out/Master In of USCI_B0, P1.7
	---------------------------------------------------------------------------------
	*/

	P1SEL0 = initial_00;				// P1 set as I/O function
	P1SEL1 = initial_00;				// P1 set as I/O function
	P1DIR = initial_00;				// Set P1 direction to Input

	// P1.0 V_DETECT_R
	P1SEL0 |= V_DETECT_R;			// V_DETECT_R selected, bit 0 set High
	P1SEL1 |= V_DETECT_R;			// V_DETECT_R selected, bit 0 set High, Function

	// P1.1 V_DETECT_L
	P1SEL0 |= V_DETECT_L;			// V_DETECT_L selected, bit 1 set High
	P1SEL1 |= V_DETECT_L;			// V_DETECT_L selected, bit 1 set High, Function

	// P1.2 LCD_BACKLITE
	P1SEL0 &= ~LCD_BACKLITE;		// LCD_BACKLITE, bit 2 set Low
	P1SEL1 &= ~LCD_BACKLITE;		// LCD_BACKLITE, bit 2 set Low, GPIO
	P1DIR |= LCD_BACKLITE;			// LCD_BACKLITE direction set to Output
	P1OUT &= ~LCD_BACKLITE;			// LCD_BACKLITE port pin set Low

	// P1.3 V_THUMB
	P1SEL0 |= V_THUMB;			// V_THUMB selected, bit 3 set High
	P1SEL1 |= V_THUMB;			// V_THUMB selected, bit 3 set High, Function

	// P1.4 SPI_CS_LCD
	P1SEL0 &= ~SPI_CS_LCD;			// SPI_CS_LCD, bit 4 set Low
	P1SEL1 &= ~SPI_CS_LCD;			// SPI_CS_LCD, bit 4 set Low, GPIO
	P1DIR |= SPI_CS_LCD;			// SPI_CS_LCD direction set to Output
	P1OUT |= SPI_CS_LCD;			// SPI_CS_LCD port pin set High b/c Active Low

	// P1.5 RESET_LCD
	P1SEL0 &= ~RESET_LCD;			// RESET_LCD, bit 5 set Low
	P1SEL1 &= ~RESET_LCD;			// RESET_LCD, bit 5 set Low, GPIO
	P1DIR |= RESET_LCD;			// RESET_LCD direction set to Output
	P1OUT &= ~RESET_LCD;			// RESET_LCD port pin set Low

	// P1.6 SIMO_B
	P1SEL0 &= ~SIMO_B;			// SIMO_B, bit 6 set Low
	P1SEL1 |= SIMO_B;			// SIMO_B, bit 6 set High, Function
	P1DIR |= SIMO_B;			// SIMO_B direction set to Output
	P1OUT &= ~SIMO_B;			// SIMO_B port pin set Low

	// P1.7 SOMI_B
	P1SEL0 &= ~SOMI_B;			// SOMI_B, bit 7 set Low
	P1SEL1 |= SOMI_B;			// SOMI_B, bit 7 set High, Function
	P1DIR &= ~SOMI_B;			// SOMI_B direction set to Input
	P1REN |= SOMI_B;			// SOMI_B Enable pull-up resistor
	P1OUT |= SOMI_B;			// SOMI_B Set for Pull-up (Input, Enable resistor)

}
/*
Function Name: Init_Port2

Description: This function initializes port 2 pins

Passed: none
Locals: none
Returned: none
Globals: none

Author: Michael Patel
Date: September 2016
Compiler: Built with IAR Embedded Workbench Version: V7.4.2.4369 (6.50.1)
*/
void Init_Port2(void){
	/*
	------------------------------------------------------------
	Configure Port 2

	USB_TXD					(0x01) // USB Transmit, P2.0
	USB_RXD					(0x02) // USB Receive, P2.1
	SPI_SCK					(0x04) // SPI mode - Clock, P2.2
	UNKNOWN_2_3				(0x08) // UNKNOWN, P2.3
	UNKNOWN_2_4				(0x10) // UNKNOWN, P2.4
	CPU_TXD					(0x20) // CPU Transmit, P2.5
	CPU_RXD					(0x40) // CPU Receive, P2.6
	UNKNOWN_2_7				(0x80) // UNKNOWN, P2.7
	-------------------------------------------------------------
	*/

	P2SEL0 = initial_00;
	P2SEL1 = initial_00;
	P2DIR = initial_00;

	// P2.0 USB_TXD
	P2SEL0 &= ~USB_TXD;			// USB_TXD, bit 0 set Low
	P2SEL1 |= USB_TXD;			// USB_TXD, bit 0 set High, Function
	P2DIR |= USB_TXD;			// USB_TXD direction set to Output
	P2OUT &= ~USB_TXD;			// USB_TXD port pin set Low

	// P2.1 USB_RXD
	P2SEL0 &= ~USB_RXD;			// USB_RXD, bit 1 set Low
	P2SEL1 |= USB_RXD;			// USB_RXD, bit 1 set High, Function
	P2DIR &= ~USB_RXD;			// USB_RXD direction set to Input
	P2REN |= USB_RXD;			// USB_RXD Enable pull-down resistor
	P2OUT &= ~USB_RXD;			// USB_RXD Set for Pull-down

	// P2.2 SPI_SCK
	P2SEL0 &= ~SPI_SCK;			// SPI_SCK, bit 2 set Low
	P2SEL1 |= SPI_SCK;			// SPI_SCK, bit 2 set High, Function
	P2DIR |= SPI_SCK;			// SPI_SCK direction set to Output
	P2OUT |= SPI_SCK;			// SPI_SCK port pin set High b/c Active Low

	// P2.3 UNKNOWN_2_3
	P2SEL0 &= ~UNKNOWN_2_3;			// bit 0 set Low
	P2SEL1 &= ~UNKNOWN_2_3;			// bit 1 set Low, GPIO
	P2DIR &= ~UNKNOWN_2_3;			// direction set to Input
	P2REN |= UNKNOWN_2_3;			// Enable pull-down resistor
	P2OUT &= ~UNKNOWN_2_3;			// Set for Pull-down

	// P2.4 UNKNOWN_2_4
	P2SEL0 &= ~UNKNOWN_2_4;			// bit 0 set Low
	P2SEL1 &= ~UNKNOWN_2_4;			// bit 1 set Low, GPIO
	P2DIR &= ~UNKNOWN_2_4;			// direction set to Input
	P2REN |= UNKNOWN_2_4;			// Enable pull-down resistor
	P2OUT &= ~UNKNOWN_2_4;			// Set for Pull-down

	// P2.5 CPU_TXD
	P2SEL0 &= ~CPU_TXD;			// CPU_TXD, bit 0 set Low
	P2SEL1 |= CPU_TXD;			// CPU_TXD, bit 1 set High, Function
	P2DIR |= CPU_TXD;			// CPU_TXD direction set to Output
	P2OUT &= ~CPU_TXD;			// CPU_TXD port pin set Low

	// P2.6 CPU_RXD
	P2SEL0 &= ~CPU_RXD;			// CPU_RXD, bit 0 set Low
	P2SEL1 |= CPU_RXD;			// CPU_RXD, bit 1 set High, Function
	P2DIR &= ~CPU_RXD;			// CPU_RXD direction set to Input
	P2REN |= CPU_RXD;			// CPU_RXD Enable pull-down resistor
	P2OUT &= ~CPU_RXD;			// CPU_RXD set for pull-down

	// P2.7 UNKNOWN_2_7
	P2SEL0 &= ~UNKNOWN_2_7;			// bit 0 set Low
	P2SEL1 &= ~UNKNOWN_2_7;			// bit 1 set Low, GPIO
	P2DIR &= ~UNKNOWN_2_7;			// direction set to Input
	P2REN |= UNKNOWN_2_7;			// Enable pull-down resistor
	P2OUT &= ~UNKNOWN_2_7;			// Set for pull-down

}
/*
Function Name: Init_Port3

Description: This function initializes port 3 pins

Passed: none
Locals: none
Returned: none
Globals: none

Author: Michael Patel
Date: September 2016
Compiler: Built with IAR Embedded Workbench Version: V7.4.2.4369 (6.50.1)
*/
void Init_Port3(void){
	/*
	---------------------------------------------------------
	Configure Port 3

	X 					(0x01) // P3.0
	Y					(0x02) // P3.1
	Z_3_2					(0x04) // P3.2
	IR_LED					(0x08) // Infrared LED, P3.3
	R_FORWARD				(0x10) // Right Forward, P3.4
	L_FORWARD				(0x20) // Left Forward, P3.5
	R_REVERSE				(0x40) // Right Reverse, P3.6
	L_REVERSE				(0x80) // Left Reverse, P3.7
	---------------------------------------------------------
	*/

	P3SEL0 = initial_00;
	P3SEL1 = initial_00;
	P3DIR = initial_00;

	// P3.0 X
	P3SEL0 &= ~X;				// X, bit 0 set Low
	P3SEL1 &= ~X;				// X, bit 1 set Low, GPIO
	P3DIR &= ~X;				// X direction set to Input
	P3REN |= X;				// X Enable pull-down resistor
	P3OUT &= ~X;				// X Set for pull-down

	// P3.1 Y
	P3SEL0 &= ~Y;				// Y, bit 0 set Low
	P3SEL1 &= ~Y;				// Y, bit 1 set Low, GPIO
	P3DIR &= ~Y;				// Y direction set to Input
	P3REN |= Y;				// Y Enable pull-down resistor
	P3OUT &= ~Y;				// Y Set for pull-down

	// P3.2 Z_3_2
	P3SEL0 &= ~Z_3_2;			// Z, bit 0 set Low
	P3SEL1 &= ~Z_3_2;			// Z, bit 1 set Low, GPIO
	P3DIR &= ~Z_3_2;			// Z direction set to Input
	P3REN |= Z_3_2;				// Z Enable pull-down resistor
	P3OUT &= ~Z_3_2;			// Z Set for pull-down

	// P3.3 IR_LED
	P3SEL0 &= ~IR_LED;			// IR_LED, bit 0 set Low
	P3SEL1 &= ~IR_LED;			// IR_LED, bit 1 set Low, GPIO
	P3DIR |= IR_LED;			// IR_LED direction set to Output
	P3OUT &= ~IR_LED;			// IR_LED port pin set Low
	//P3OUT |= IR_LED;

	// P3.4 R_FORWARD
	P3SEL0 |= R_FORWARD;			// R_FORWARD, bit 0 set High
	P3SEL1 &= ~R_FORWARD;			// R_FORWARD, bit 1 set Low, TB1.1
	P3DIR |= R_FORWARD;			// R_FORWARD direction set to Output
	//P3OUT &= ~R_FORWARD;			// R_FORWARD port pin set Low

	// P3.5 L_FORWARD
	P3SEL0 |= L_FORWARD;			// L_FORWARD, bit 0 set High
	P3SEL1 &= ~L_FORWARD;			// L_FORWARD, bit 1 set Low, TB1.2
	P3DIR |= L_FORWARD;			// L_FORWARD direction set to Output
	//P3OUT &= ~L_FORWARD;			// L_FORWARD port pin set Low

	// P3.6 R_REVERSE
	P3SEL0 &= ~R_REVERSE;			// R_REVERSE, bit 0 set Low
	P3SEL1 &= ~R_REVERSE;			// R_REVERSE, bit 1 set Low, GPIO
	P3DIR |= R_REVERSE;			// R_REVERSE direction set to Output
	P3OUT &= ~R_REVERSE;			// R_REVERSE port pin set Low

	// P3.7 L_REVERSE
	P3SEL0 &= ~L_REVERSE;			// L_REVERSE, bit 0 set Low
	P3SEL1 &= ~L_REVERSE;			// L_REVERSE, bit 1 set Low, GPIO
	P3DIR |= L_REVERSE;			// L_REVERSE direction set to Output
	P3OUT &= ~L_REVERSE;			// L_REVERSE port pin set Low
}
/*
Function Name: Init_Port4

Description: This function initializes port 4 pins

Passed: none
Locals: none
Returned: none
Globals: none

Author: Michael Patel
Date: September 2016
Compiler: Built with IAR Embedded Workbench Version: V7.4.2.4369 (6.50.1)
*/
void Init_Port4(void){
	/*
	--------------------------------------------------
	Configure Port 4

	SW1					(0x01) // Switch 1, P4.0
	SW2					(0x02) // Switch 2, P4.1
	--------------------------------------------------
	*/

	P4SEL0 = initial_00;
	P4SEL1 = initial_00;
	P4DIR = initial_00;
	P4OUT = initial_00;

	// P4.0 SW1
	P4SEL0 &= ~SW1;				// SW1, bit 0 set Low
	P4SEL1 &= ~SW1; 			// SW1, bit 1 set Low, GPIO
	P4DIR &= ~SW1;				// SW1 direction set to Input
	P4REN |= SW1;				// SW1 Enable pull-up resistor
	P4OUT |= SW1;				// SW1 Set for pull-up
	P4IES |= SW1;				// SW1 select for Hi/Lo edge interrupt
	P4IFG &= ~SW1;				// SW1 IFG cleared
	P4IE |= SW1;				// SW1 Enable interrupt

	// P4.1 SW2
	P4SEL0 &= ~SW2;				// SW2, bit 0 set Low
	P4SEL1 &= ~SW2;				// SW2, bit 1 set Low, GPIO
	P4DIR &= ~SW2;				// SW2 direction set to Input
	P4REN |= SW2;				// SW2 Enable pull-up resistor
	P4OUT |= SW2;				// SW2 Set for pull-up
	P4IES |= SW2;				// SW2 select for Hi/Lo edge interrupt
	P4IFG &= ~SW2;				// SW2 IFG cleared
	P4IE |= SW2;				// SW2 Enable interrupt
}
/*
Function Name: Init_PortJ

Description: This function initializes port J pins

Passed: none
Locals: none
Returned: none
Globals: none

Author: Michael Patel
Date: September 2016
Compiler: Built with IAR Embedded Workbench Version: V7.4.2.4369 (6.50.1)
*/
void Init_PortJ(unsigned int mode){
	/*
	--------------------------------------------------
	Configure Port J 

	IOT_WAKEUP				(0x01) // , PJ.0
	IOT_FACTORY				(0x02) // , PJ.1
	IOT_STA_MINIAP				(0x04) // , PJ.2
	IOT_RESET				(0x08) // , PJ.3
	--------------------------------------------------
	*/

	PJSEL0 = initial_00;
	PJSEL1 = initial_00;
	PJDIR = initial_00;

	// PJ.0 IOT_WAKEUP
	switch(mode){
		case USE_IOT_WAKEUP:
			PJSEL0 &= ~IOT_WAKEUP;			// IOT_WAKEUP, bit 0 set Low
			PJSEL1 &= ~IOT_WAKEUP;			// IOT_WAKEUP, bit 1 set Low, GPIO
			PJDIR |= IOT_WAKEUP;			// IOT_WAKEUP direction set to Output
			PJOUT &= ~IOT_WAKEUP;			// IOT_WAKEUP port pin set Low
			break;

		case USE_SMCLK:
			PJSEL0 |= IOT_WAKEUP;			// IOT_WAKEUP, bit 0 set High
			PJSEL1 &= ~IOT_WAKEUP;			// IOT_WAKEUP, bit 1 set Low, SMCLK
			PJDIR |= IOT_WAKEUP;			// IOT_WAKEUP direction set to Output
			PJOUT &= ~IOT_WAKEUP;			// IOT_WAKEUP port pin set Low
			break;

		default:
			// USE_IOT_WAKEUP
			PJSEL0 &= ~IOT_WAKEUP;			// IOT_WAKEUP, bit 0 set Low
			PJSEL1 &= ~IOT_WAKEUP;			// IOT_WAKEUP, bit 1 set Low, GPIO
			PJDIR |= IOT_WAKEUP;			// IOT_WAKEUP direction set to Output
			PJOUT &= ~IOT_WAKEUP;			// IOT_WAKEUP port pin set Low
			break;
	}

	// PJ.1 IOT_FACTORY
	PJSEL0 &= ~IOT_FACTORY;			// IOT_FACTORY, bit 0 set Low
	PJSEL1 &= ~IOT_FACTORY;			// IOT_FACTORY, bit 1 set Low, GPIO
	PJDIR |= IOT_FACTORY;			// IOT_FACTORY direction set to Output
	PJOUT &= ~IOT_FACTORY;			// IOT_FACTORY port pin set Low

	// PJ.2 IOT_STA_MINIAP
	PJSEL0 &= ~IOT_STA_MINIAP;		// IOT_STA_MINIAP, bit 0 set Low
	PJSEL1 &= ~IOT_STA_MINIAP;		// IOT_STA_MINIAP, bit 1 set Low, GPIO
	PJDIR |= IOT_STA_MINIAP;		// IOT_STA_MINIAP direction set to Output
	PJOUT |= IOT_STA_MINIAP;		// IOT_STA_MINIAP port pin set 

	// PJ.3 IOT_RESET
	PJSEL0 &= ~IOT_RESET;			// IOT_RESET, bit 0 set Low
	PJSEL1 &= ~IOT_RESET;			// IOT_RESET, bit 1 set Low, GPIO
	PJDIR |= IOT_RESET;			// IOT_RESET direction set to Output
	PJOUT &= ~IOT_RESET;			// IOT_RESET port pin set Low
}

