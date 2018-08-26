/******************************************************************************
File Name: macros.h99999

Description: This file contains the macros used by all the other files

Author: Michael Patel
Date: September 2016
Compiler: Built with IAR Embedded Workbench Version: V7.4.2.4369 (6.50.1)
*******************************************************************************
*/

#include "msp430.h"
#include "functions.h"

// Required defines
// In the event the universe no longer exists, this bit will reset
#define ALWAYS                  (1)
#define CNTL_STATE_INDEX        (3) // Control States
#define LED1                 (0x01) // LED 1
#define LED2                 (0x02) // LED 2
#define LED3                 (0x04) // LED 3
#define LED4                 (0x08) // LED 4
#define LED5                 (0x10) // LED 5
#define LED6                 (0x20) // LED 6
#define LED7                 (0x40) // LED 7
#define LED8                 (0x80) // LED 8
#define SW1                  (0x01) // Switch 1
#define SW2                  (0x02) // Switch 2
#define CNTL_STATE_INDEX        (3)
// LCD
#define LCD_HOME_L1	        0x80
#define LCD_HOME_L2         	0xA0
#define LCD_HOME_L3         	0xC0
#define LCD_HOME_L4         	0xE0

//=============================================================================
// Ports
#define initial_00              (0x00)

// SIGNAL NAMES

// Port 1
#define V_DETECT_R				        (0x01) // Voltage from Right Detector, P1.0
#define	V_DETECT_L				        (0x02) // Voltage from Left Detector, P1.1
#define	LCD_BACKLITE			                (0x04) // LCD Backlite, P1.2
#define	V_THUMB					        (0x08) // Voltage from Thumb Wheel, P1.3
#define	SPI_CS_LCD				        (0x10) // LCD Chip Select, P1.4
#define	RESET_LCD				        (0x20) // LCD Reset, P1.5
#define	SIMO_B					        (0x40) // SPI mode - Slave In/Master Out of USCI_B0, P1.6
#define	SOMI_B					        (0x80) // SPI mode - Slave Out/Master In of USCI_B0, P1.7

// Port 2
#define	USB_TXD						(0x01) // USB Transmit, P2.0
#define	USB_RXD						(0x02) // USB Receive, P2.1
#define	SPI_SCK						(0x04) // SPI mode - Clock, P2.2
#define	UNKNOWN_2_3					(0x08) // UNKNOWN, P2.3
#define	UNKNOWN_2_4					(0x10) // UNKNOWN, P2.4
#define	CPU_TXD						(0x20) // CPU Transmit, P2.5
#define	CPU_RXD						(0x40) // CPU Receive, P2.6
#define	UNKNOWN_2_7					(0x80) // UNKNOWN, P2.7

// Port 3
#define	X 						(0x01) // P3.0
#define	Y						(0x02) // P3.1
#define	Z_3_2						(0x04) // P3.2
#define	IR_LED						(0x08) // Infrared LED, P3.3
#define	R_FORWARD					(0x10) // Right Forward, P3.4
#define	L_FORWARD					(0x20) // Left Forward, P3.5
#define	R_REVERSE					(0x40) // Right Reverse, P3.6
#define	L_REVERSE					(0x80) // Left Reverse, P3.7

// Port 4
#define	SW1						(0x01) // Switch 1, P4.0
#define	SW2						(0x02) // Switch 2, P4.1

// Port J
#define	IOT_WAKEUP					(0x01) // , PJ.0
#define	IOT_FACTORY					(0x02) // , PJ.1
#define	IOT_STA_MINIAP				        (0x04) // , PJ.2
#define	IOT_RESET					(0x08) // , PJ.3

//==============================================================================
// LCD
#define LCD_display_line_size           (11)
#define LCD_IDX_0                       (0)
#define INDENT_1SPACE                   (1)
#define INDENT_2SPACE                   (2)
#define INDENT_3SPACE                   (3)
#define INDENT_4SPACE                   (4)

//==============================================================================
// Timers
#define WAIT_0                  (0)
#define WAIT_1 					(1)
#define WAIT_2					(2)
#define WAIT_3					(3)
#define WAIT_4					(4)
#define WAIT_5 					(5)
#define WAIT_6					(6)
#define WAIT_7					(7)
#define WAIT_8					(8)
#define WAIT_9					(9)
#define WAIT_10                 (10)
#define WAIT_11					(11)
#define WAIT_12					(12)
#define WAIT_13					(13)
#define WAIT_14					(14)
#define WAIT_15					(15)
#define WAIT_16					(16)
#define WAIT_17					(17)
#define WAIT_18					(18)
#define WAIT_19					(19)
#define WAIT_20					(20)
#define WAIT_23					(23)
#define WAIT_25					(25)
#define WAIT_26					(26)
#define WAIT_28					(28)
#define WAIT_29					(29)
#define WAIT_30					(30)
#define WAIT_33					(33)
#define WAIT_34					(34)
#define WAIT_35					(35)
#define WAIT_37					(37)
#define WAIT_40					(40)
#define WAIT_50                 (50)
#define WAIT_60					(60)
#define WAIT_70					(70)
#define WAIT_75					(75)
#define WAIT_80					(80)
#define WAIT_90					(90)
#define WAIT_100                (100)
#define WAIT_150                (150)
#define WAIT_200                (200)
#define WAIT_250                (250)
#define WAIT_400				(400)
#define WAIT_500				(500)

#define WAIT_1000               (1000)

//#define five_msec               (5)

//==============================================================================
// Main.c
#define BIG_LCD_ZERO            (0)
#define BIG_LCD_ONE             (1)
#define SIZE_IS_ZERO            (0)
#define ONE_TIME_ZERO           (0)
#define ONE_TIME_ONE            (1)

#define WAIT_FIVE_INCHES        (100)

// boolean
#define TRUE	(1)
#define FALSE	(0)

//==============================================================================
// SHAPES
#define LAPS				(2)
#define SIDES				(3)

#define CLOCKWISE			(1)
#define COUNTERCLOCKWISE 	(2)

//==============================================================================
// Hw 05 for Port J
#define USE_IOT_WAKEUP		(0x00)
#define USE_SMCLK			(0x01)

//==============================================================================
// Hw 06 
//#define TA0CCR0_INTERVAL			(25000) // 8M / 4 / 8 / (1/100ms)
//#define TA0CCR1_INTERVAL
//#define TA0CCR2_INTERVAL
#define NONE						(0)
#define INITIAL_VALUE_TO_ZERO		(0)
#define in_SW1_debounce				(1)
#define in_SW2_debounce				(2)
#define in_TimerA0_debounce			(3)
#define MAX_COUNT					(40)
#define MODULO_10					(10)

//==============================================================================
// Project 4
//#define TA0CCR0_INTERVAL			(62500) // 8M / 8 / 8 / (1/500ms)
#define begin_project_4_interrupts	(1)
#define move_interrupt				(2)
#define COUNT_EQUALS_ZERO			(0)
#define _0s							(0)
#define _1s							(1)
#define _2s							(2)
#define _4s							(4)
#define _6s							(6)
#define _8s							(8)
#define _10s						(10)
#define _12s						(12)
#define _14s						(14)
#define _16s						(16)
#define _18s						(18)
#define _20s						(20)
#define _22s						(22)



//==============================================================================
// Project 5/6
#define RESET_STATE					(0)
#define TA0CCR0_INTERVAL			(62500) // 8M / 8 / 8 / (1/500ms)
#define BLACK							(1)
#define WHITE							(0)
#define BLACK_BASE						(1023)
#define BLACK_OFFSET					(700)
//#define WHITE_BASE
//#define WHITE_OFFSET

#define SW1_IE						(0x0001)
#define SW2_IE						(0x0002)
#define ADC_IE						(0x0004)
#define TimerA0_0_IE				(0x0008)
#define TimerA0_1_IE				(0x0010)
#define TimerA1_0_IE				(0x0020)
#define TimerA1_1_IE				(0x0040)
#define TimerB0_0_IE				(0x0080)
#define TimerB0_1_IE				(0x0100)
#define TimerB1_0_IE				(0x0200)
#define TimerB1_1_IE				(0x0400)
#define TimerB2_0_IE				(0x0800)
#define TimerB2_1_IE				(0x1000)
#define USCI_A0_IE					(0x2000)
#define USCI_A1_IE					(0x4000)

#define _0u 							(0)
#define _1u 							(1)
#define _2u 							(2)
#define _3u 							(3)
#define _4u 							(4)
#define _5u 							(5)
#define _6u 							(6)
#define _7u   							(7)
#define _8u 							(8)
#define _9u 							(9)
#define _10u 							(10)
#define _11u							(11)
#define _12u 							(12)
#define _13u 							(13)
#define _14u 							(14)
#define _15u 							(15)
#define _16u							(16)
#define _20u							(20)
#define _24u							(24)
#define _25u							(25)
#define _30u							(30)
#define _40u							(40)
#define _41u 							(41)
#define _48u							(48)
#define _50u							(50)
#define _57u							(57)
#define _60u							(60)
#define _70u							(70)
#define _80u							(80)
#define _90u							(90)
#define _99u							(99)
#define _100u 							(100)
#define _1000u							(1000)
#define _5000u							(5000)

#define ASCII_offset				(0x30)
#define OFF 						(0)
#define WHEEL_PERIOD				(50000)

#define ON_BB					(0x1)
#define ON_BW					(0x2)
#define ON_WB 					(0x4)
#define ON_WW					(0x8)

// Homework 8
#define BAUD_RATE_115200			(4)
#define BAUD_RATE_REMAINDER_115200	(0x5551)
#define BAUD_RATE_9600				(52)
#define BAUD_RATE_REMAINDER_9600	(0x4911)

// Project 7
#define MAX_FFFF				(65535)
#define HALF	(0.5)

// Project 8
#define NONE	(0)

// Project 9
#define COMMAND_LENGTH (3)