/******************************************************************************
File Name: interrupts_serial.c

Description: This file contains the serial ISRs

Author: Michael Patel
Date: October 2016
Compiler: Built with IAR Embedded Workbench Version: V7.4.2.4369 (6.50.1)
*******************************************************************************
*/

#include "msp430.h"
#include "functions.h"
#include "macros.h"
#include <string.h>

extern volatile unsigned int interrupt_event;
extern volatile unsigned int USCI_A0_RX_counter;
extern volatile unsigned int USCI_A0_TX_counter;
extern volatile unsigned int USCI_A1_RX_counter;
extern volatile unsigned int USCI_A1_TX_counter;
extern volatile char tx_char[_8u];
extern volatile char USB_RX[_8u];
//extern volatile char IOT_RX[5];
extern volatile unsigned int temp_serial_A0;
extern volatile unsigned int temp_serial_A1;

//extern volatile char RX_ASCII_information[6];
char receive[_8u];
extern unsigned int ready_to_RX;
extern unsigned int ready_to_TX;
extern char *display_2;
extern char *display_3;
extern char *display_4;
extern volatile char command[_3u];
extern volatile char FRAMcommand;
extern volatile char webcommand;
extern volatile int IOTcode;
extern char *DISASSOCIATION;
extern char *IPADDRESS;
extern volatile char commandIOT[_3u];
char windIOT[_8u];
unsigned int commandIOT_count;
unsigned int windIOT_count;
extern volatile char ipAddrArray[_50u];
unsigned int ipAddrWindFlag;
unsigned int wind24 = COUNT_EQUALS_ZERO;


#pragma vector=USCI_A0_VECTOR
__interrupt void USCI_A0_ISR(void){

	switch(__even_in_range(UCA0IV, _8u)){
		unsigned int temp;

		case _0u: // no interrupt
		break;

		case _2u: // Receive, RXIFG
			// PC / Terminal -> FRAM
			if(UCRXIFG){
				interrupt_event |= USCI_A0_IE;
				ready_to_TX = TRUE; // received char from PC, so set flag to transmit from FRAM to PC
				temp = temp_serial_A0;
				command[temp] = UCA0RXBUF;

				if(command[_0u] == '.'){ // user commands begin with '.'
					temp_serial_A0++;

					if(command[temp] == '\r'){ // parse for carriage return to end command
						FRAMcommand = command[_1u]; // give FRAMcommand the specific char command
						temp_serial_A0 = COUNT_EQUALS_ZERO;
					}
				}						
	
				UCA1TXBUF = UCA0RXBUF; // send to IOT
				//UCA0TXBUF = UCA0RXBUF; // send to terminal
			}
		break;

		case _4u: // Transmit, TXIFG
		break;

		case _6u:
		break;

		case _8u:
		break;

		default:
		break;
	}
}


#pragma vector=USCI_A1_VECTOR
__interrupt void USCI_A1_ISR(void){

	switch(__even_in_range(UCA1IV, _8u)){
		unsigned int temp;
		//int i;
		//unsigned int tempFlag;

		case _0u:
		break;

		case _2u: // Receive
			// IOT
			if(UCRXIFG){
				interrupt_event |= USCI_A1_IE;
				temp = temp_serial_A1;
				commandIOT[temp] = windIOT[windIOT_count] = UCA1RXBUF;

				// .FRAM
				if(commandIOT[_0u] == '.'){ // user commands begin with '.'
					temp_serial_A1++;

					if(commandIOT[temp] == '\r'){ // parse for carriage return to end Wi-Fi command
						webcommand = commandIOT[_1u]; // give webcommand the specific received command
						temp_serial_A1 = COUNT_EQUALS_ZERO;
					}
				}

				// Looking for IP Address, collect next 'x' chars that are the IP address
				if(ipAddrWindFlag){
					ipAddrArray[wind24] = UCA1RXBUF;
					wind24++;

					if(wind24 == _25u){ // arbitrary size to fit IP address string length
						IOTcode = _24u; // received +WIND:24 
						wind24 = COUNT_EQUALS_ZERO;
						ipAddrWindFlag = FALSE;
					}
				}

				// +WIND 
				if(windIOT[_0u] == '+'){
					windIOT_count++;

					if(windIOT_count == _8u){
						// IP Address (+WIND:24)
						if(!strcmp(windIOT, IPADDRESS)){
							ipAddrWindFlag = TRUE;
							//IOTcode = _24u;							
						}


						// Disassociation (+WIND:41)
						if(!strcmp(windIOT, DISASSOCIATION)){
							IOTcode = _41u;
						}	
						
						windIOT_count = COUNT_EQUALS_ZERO;					
					}
				}
				
				//temp_serial_A1++;
				//if(temp > 4){
				/*
					if((receive[0] == 'W') && (receive[1] == 'I') && (receive[2] == 'N') && (receive[3] == 'D') && (receive[4] == ':')){
						IOT_message[temp-5] = receive[temp];
						tempFlag = TRUE;
					}

					if(temp == 6){
						temp_serial_A1 = 0;
						if(tempFlag){
							haveIOTmessage = TRUE;
						}
					}
					*/
				//}

				if(ready_to_TX){
					UCA0TXBUF = UCA1RXBUF; // send to terminal
				}
				
/*
				interrupt_event |= USCI_A1_IE;
				USCI_A1_RX_counter++;

				dummyTemp = temp = temp_serial_A1; // i
				receive[temp] = UCA1RXBUF;
				temp_serial_A1++;
				
				if(temp > _2u){
					
					if((receive[_0u] == 'C') && (receive[_1u] == 'H') && (receive[_2u] == 'K')){
						RX_ASCII_information[temp-_3u] = receive[temp];
						display_2 = display_3 = display_4 = "";
						if(temp == _8u){
							ready_to_RX = FALSE;
							temp_serial_A1 = _0u;	
							for(i=_0u; i<sizeof(receive); i++){
								receive[i] = _0u;
							}
						}
					}
						
					else{
						if(!(receive[_0u] == 'C')){
							display_2 = "E1";
						}
						if(!(receive[_1u] == 'H')){
							display_3 = "E2";
						}
						if(!(receive[_2u] == 'K')){
							display_4 = "E3";
						}
					}					
				}
				*/
				
			}
		break;

		case _4u: // Transmit
		break;

		case _6u:
		break;

		case _8u:
		break;

		default:break;
	}
}