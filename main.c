  //------------------------------------------------------------------------------
  //  File Name: main.c
  //
  //  Description: This file contains the Main Routine - "While" Operating System
  //
  //
  //  Jim Carlson, Michael Patel
  //  September 2016
  //  Built with IAR Embedded Workbench Version: V7.4.2.4369 (6.50.1)
  //------------------------------------------------------------------------------

  //------------------------------------------------------------------------------


  #include  "msp430.h"
  #include  "functions.h"
  #include  "macros.h"
  #include <string.h>

  // Global Variables
volatile unsigned char control_state[CNTL_STATE_INDEX];
volatile unsigned int Time_Sequence;
char led_smclk;
volatile char one_time;
volatile unsigned int five_msec_count;
extern char display_line_1[LCD_display_line_size];
extern char display_line_2[LCD_display_line_size];
extern char display_line_3[LCD_display_line_size];
extern char display_line_4[LCD_display_line_size];
extern char *display_1;
extern char *display_2;
extern char *display_3;
extern char *display_4;
char posL1;
char posL2;
char posL3;
char posL4;
char size_count;
char big;

  //volatile unsigned int OF_counter;
volatile unsigned int interrupt_event = _0u;

unsigned int is_R_FORWARD_ON;
unsigned int is_L_FORWARD_ON;
unsigned int is_R_REVERSE_ON;
unsigned int is_L_REVERSE_ON;
char adc_char[_4u];
volatile unsigned int ADC_THUMB;
volatile unsigned int ADC_Right_Detector;
volatile unsigned int ADC_Left_Detector;
unsigned int rightHexReg;
unsigned int leftHexReg;
char rightASCIIReg[_5u];
char leftASCIIReg[_5u];
unsigned int rightState;
unsigned int leftState;
char *direction;
volatile unsigned int ADC_CHANNEL_COUNT;

unsigned int stateOfIR_LED;
volatile unsigned int timerA0_counter;
volatile unsigned int timerB1_1_count;
  //volatile unsigned int timerB2_1_count;
unsigned int BB_state_counter;
unsigned int BW_state_counter;
unsigned int WB_state_counter;
unsigned int WW_state_counter;
unsigned int j;
  //unsigned int state_flag;
unsigned int current_state;
unsigned int next_state;
unsigned int detected_BB;
volatile unsigned int USCI_A0_RX_counter;
volatile unsigned int USCI_A0_TX_counter;
volatile unsigned int USCI_A1_RX_counter;
volatile unsigned int USCI_A1_TX_counter;
volatile unsigned int temp_serial_A0;
volatile unsigned int temp_serial_A1;
//volatile char tx_char[8] = {0x31, 0x32, 0x33, 0x31, 0x32, 0x33, 0x31, 0x32};
//volatile char USB_RX[8];
//volatile char IOT_RX[5];
//char USB_RX_string[9];
unsigned int baud_rate;
unsigned int baud_rate_remainder;
char IOT_RX_string[_6u];
volatile char RX_ASCII_information[_6u];
char copyRX[_6u];
char TX_ASCII_1[_9u];
char RX_ASCII_1[_6u];
char TX_ASCII_2[_9u];
char RX_ASCII_2[_6u];
//char TX_ASCII_3[9];
//char RX_ASCII_3[6];
unsigned int num_sequences;
unsigned int SW1_in_debounce;
unsigned int ready_to_TX;
unsigned int ready_to_RX;
unsigned int hold_sequence_count;
unsigned int current_sequence;
char *AT9600 = "AT+S.SCFG=console1_speed,9600\r";
char *AT = "AT\r";
char *ATflash = "AT&W\r";
char *ATcomMode = "AT+CFUN=1\r";
char *ATmacAddr = "AT+S.GCFG=nv_wifi_macaddr\r";
char *ATsetSSIDncsu = "AT+S.SSIDTXT=ncsu\r";
char *ATgetSSID = "AT+S.SSIDTXT\r";
char *ATsetHostname = "AT+S.SCFG=ip_hostname,ECE-306_17_C\r";
char *ATgetHostname = "AT+S.GCFG=ip_hostname\r";
char *ATsetNetworkPrivacy = "AT+S.SCFG=wifi_priv_mode,0\r";
char *ATgetNetworkPrivacy = "AT+S.GCFG=wifi_priv_mode\r";
char *ATsetNetworkMode = "AT+S.SCFG=wifi_mode,1\r";
char *ATgetNetworkMode = "AT+S.GCFG=wifi_mode\r";
char *ATcheckStatus = "AT+S.STS\r";
char *ATgetIPaddress = "AT+S.GCFG=ip_ipaddr\r";
char *ATfactory = "AT&F\r";
char *DISASSOCIATION = "+WIND:41";
char *IPADDRESS = "+WIND:24";
unsigned int vehicle_move_count=COUNT_EQUALS_ZERO;
unsigned int init_IOT_count=COUNT_EQUALS_ZERO;
unsigned int connect_IOT_count=COUNT_EQUALS_ZERO;
unsigned int vehicle_move_count_flag = FALSE;
unsigned int init_IOT_count_flag = FALSE;
unsigned int connect_IOT_count_flag = FALSE;
volatile char command[COMMAND_LENGTH];
volatile char commandIOT[COMMAND_LENGTH];
volatile char FRAMcommand;
volatile char webcommand;
volatile int IOTcode;
volatile char ipAddrArray[_50u];
unsigned int follow_Black_Line_Flag;
unsigned int ADC_average_count;
unsigned int dissasociat_Flag;
unsigned int lap_count;
int lap_count_intArray[_5u];
char lap_count_ASCIIarray[_5u];
char lap_count_String[_6u];
char copyIParray[_10u];
char ipString[_11u];
// ==============================================================================================
//------------------------------------------------------------------------------
// Function: Main Program
// 
// Description: This is the main routine for the program. Execution of code starts here.
//              The operating system is Back Ground Fore Ground.
/*
   Passed: none
   Locals: none
   Returned: none
   Globals: control_state, Time_Sequence, led_smclk, one_time, five_msec_count,
            display_line_1, display_line_2, display_line_3, display_line_4,
            display_1, display_2, display_3, display_4, posL1, posL2, posL3, posL4,
            size_count, big

  Author: Michael Patel
  Date: September 2016
  Compiler: Built with IAR Embedded Workbench Version: V7.4.2.4369 (6.50.1)
  // ==============================================================================================
*/

void main(void){

  //------------------------------------------------------------------------------
    Init_Ports();                             // Initialize Ports
    Init_Clocks();                            // Initialize Clock System
    Init_Conditions();                        // enables Interrupts
    Init_LCD();                               // Initialize LCD
    Init_ADC();                       
    Init_Timers();

    turnAllWheelsOFF(); // begin car in stop position

    ready_to_TX = FALSE; // 
    ready_to_RX = TRUE; // 

    P3OUT &= ~IR_LED; // turn off IR LED
    //P3OUT |= IR_LED; // turn on IR LED
    PJOUT |= IOT_RESET; // IOT_RESET is Active Low

    setBaudRate(BAUD_RATE_9600, BAUD_RATE_REMAINDER_9600); // initialize pin Baud Rate for UCA0 and UCA1
    /*
    baud_rate = BAUD_RATE_9600;
    baud_rate_remainder = BAUD_RATE_REMAINDER_9600;
    Init_Serial_UCA0();

    //baud_rate = BAUD_RATE_115200;
    //baud_rate_remainder = BAUD_RATE_REMAINDER_115200;
    Init_Serial_UCA1();
    */

    clearFRAMcommand();
    clearWEBcommand();
    clearIOTcode();
    lap_count = COUNT_EQUALS_ZERO; // keep track of time on track
    //initializeIOT();
    //PJOUT |= IOT_FACTORY;
    //out_character(ATfactory, strlen(ATfactory));
    
    
        
  //------------------------------------------------------------------------------
  // Begining of the "While" Operating System
  //------------------------------------------------------------------------------
  while(ALWAYS) {				// Can the Operating system run 


    // BLACK LINE FOLLOWING
    if(follow_Black_Line_Flag){
      // execute Black Line functionality
      if(detected_BB){
        fsm(); // run fsm if have already detected BB once
      }  
      else{
        detectBlackLine(); // detect black line 1st time
      }
    }

    
    // USCI A0 IE
    // COMMAND FROM TERMINAL
    if(interrupt_event & USCI_A0_IE){
      switch(FRAMcommand){
        case 'F': // Forward
          display_2 = "F";
          prepVehicleMoveIOT();
          Forward();
        break;

        case 'B': // Backward
          display_2 = "B";
          prepVehicleMoveIOT();
          Backward();
        break;

        case 'L': // Left
          display_2 = "L";
          prepVehicleMoveIOT();
          Left();
        break;

        case 'R': // Right
          display_2 = "R";
          prepVehicleMoveIOT();
          Right();
        break;

        case 'M': // change to Black Line mode
          // switch from IOT to Black Line
        break;

        case 'I': // Initialize IOT
          initializeIOT(); // initialize IOT module
        break;

        case 'C': // Connect
          reconnectIOT();
        break;

        case 'Q': // Get Status
          getStatusIOT(); // returns MAC address and IP address
        break;

        default:break;
      }      

      interrupt_event &= ~USCI_A0_IE;
    }


    // USCI A1 IE
    // COMMAND FROM WEB / OVER WI-FI
    if(interrupt_event & USCI_A1_IE){
      switch(webcommand){
        case 'F': // Forward
          display_2 = "F";
          prepVehicleMoveIOT();
          Forward();
        break;

        case 'B': // Backward
          display_2 = "B";
          prepVehicleMoveIOT();
          Backward();
          
        break;

        case 'L': // Left
          display_2 = "L";
          prepVehicleMoveIOT();
          Left();
        break;

        case 'R': // Right
          display_2 = "R";
          prepVehicleMoveIOT();
          Right();
        break;

        case 'M': // IOT -> Black Line
          prepIOTtoBlackLine();
        break;

        case 'N': // Black Line -> IOT
          prepBlackLineToIOT();
        break;

        case 'I': // Initialize IOT  
          initializeIOT();
        break;

        case 'C': // Connect
          reconnectIOT();          
        break;

        case 'Q': // Get Status
          getStatusIOT();
        break;

        default:break;
      }


      // MESSAGES FROM IOT (+WIND)
      switch(IOTcode){
        int i;
        case _24u: // IP Address
          for(i=_0u; i<sizeof(ipAddrArray); i++){ // parse for IP address
            copyIParray[i] = ipAddrArray[i+_12u];
          }
          display_3 = toString(copyIParray, sizeof(copyIParray), ipString); // display IP Address
          clearIOTcode();
        break;

        case _41u: // Disassociation -> Reconnect
          reconnectIOT();
          clearFRAMcommand();
          clearWEBcommand();
          clearIOTcode();
        break;

        default:break;
      }

      interrupt_event &= ~USCI_A1_IE;
    }
    
    // SW1 IE
    /*
    if(interrupt_event & SW1_IE){
      SW1_Pressed();
      P4IE |= SW1;
      interrupt_event &= ~SW1_IE;
    }
    */

    // SW2 IE
    /*
    if(interrupt_event & SW2_IE){
      SW2_Pressed();
      P4IE |= SW2;
      interrupt_event &= ~SW2_IE;
    }
    */

    // ADC IE
    if(interrupt_event & ADC_IE){

      ADC_average_count++;
      if(ADC_average_count<_16u){
        rightHexReg += ADC_Right_Detector; // summing past ADC_Right_Detector values
        leftHexReg += ADC_Left_Detector; // summing past ADC_Left_Detector values
      }

      if(ADC_average_count == _16u){ // use an average of 16 ADC values
        ADC_average_count=COUNT_EQUALS_ZERO;

        ADC_Right(); // find state of Right detector
        ADC_Left(); // find state of Left detector

        // Direction
        current_state = DetermineState(); // determine L-R combination to find state
        //direction = DetermineDirection(current_state); // determine direction veering as a char* (string)
        //display_4 = direction;
      }

      interrupt_event &= ~ADC_IE;
    }


    // TIMER A0_0 IE
    if(interrupt_event & TimerA0_0_IE){
      Display_Process();      

      if(vehicle_move_count_flag){
        vehicle_move_count++;
      }      

      if(init_IOT_count_flag){
        init_IOT_count++;
      }

      if(connect_IOT_count_flag){
        connect_IOT_count++;
      }

      // Vehicle Moving -> Stop
      if(vehicle_move_count == _2u){
        turnAllWheelsOFF();
        display_2 = ""; // display IP address
        //vehicle_move_count_flag = FALSE;
      }


      // Initialize IOT
      switch(init_IOT_count){
        case _1u:
          out_character(AT9600, strlen(AT9600)); // set IOT module for 9600 Baud
        break;

        case _3u:
          out_character(ATflash, strlen(ATflash)); // save settings of IOT module
        break;

        case _5u: // change pin Baud Rate to 9600, Software reset, Hardware reset
          baud_rate = BAUD_RATE_9600;
          baud_rate_remainder = BAUD_RATE_REMAINDER_9600;
          Init_Serial_UCA0();
          Init_Serial_UCA1();
          out_character(ATcomMode, strlen(ATcomMode));
          PJOUT &= ~IOT_RESET;
        break;

        case _7u:
          PJOUT |= IOT_RESET; // come out of IOT Reset
          init_IOT_count_flag = FALSE;
          display_2 = "";
        break;

        default:break;
      }

      // Connect IOT
      switch(connect_IOT_count){
        case _1u:
          out_character(ATsetSSIDncsu, strlen(ATsetSSIDncsu)); // set SSID
          out_character(ATgetSSID, strlen(ATgetSSID));
        break;

        case _3u:
          out_character(ATsetHostname, strlen(ATgetHostname)); // set Hostname
          out_character(ATgetHostname, strlen(ATgetHostname));
        break;

        case _5u:
          out_character(ATsetNetworkPrivacy, strlen(ATsetNetworkPrivacy)); // set Network privacy settings
          out_character(ATgetNetworkPrivacy, strlen(ATgetNetworkPrivacy));
        break;

        case _7u:
          out_character(ATsetNetworkMode, strlen(ATsetNetworkMode)); // set Network mode
          out_character(ATgetNetworkMode, strlen(ATgetNetworkMode));
        break;

        case _9u:
          out_character(ATflash, strlen(ATflash)); // save settings
        break;

        case _11u:
          out_character(ATcomMode, strlen(ATcomMode)); // Software Reset
          PJOUT &= ~IOT_RESET; // Hardware Reset
        break;

        case _13u:
          PJOUT |= IOT_RESET; // come out of reset
          //out_character(ATgetIPaddress, strlen(ATgetIPaddress));
          connect_IOT_count_flag = FALSE;
          display_2 = "";
        break;

        default:break;
      }

      // display lap time every 1s in seconds
      if(!(timerA0_counter % _2u)){
        lap_count++;
        IntToIntArray(lap_count, lap_count_intArray);
        IntArrayToASCIIarray(lap_count_intArray, lap_count_ASCIIarray);
        display_1 = toString(lap_count_ASCIIarray, sizeof(lap_count_ASCIIarray), lap_count_String);
      }
      


      /*
      if(!(timerA0_counter % _4u)){
        // SW 1 debounce
        if(SW1_in_debounce){
          P4IFG &= ~SW1;
          P4IE |= SW1;
          SW1_in_debounce = FALSE;
        }       
      }
      */
      
      /*
      // TX to BUF
      if(ready_to_TX){
        switch(current_sequence){
          case _1u:
            out_character(TX_ASCII_1);
            ready_to_TX = FALSE;
          break;

          case _2u:
            out_character(TX_ASCII_2);
            ready_to_TX = FALSE;
          break;

          case _3u:
            out_character(TX_ASCII_3);
            ready_to_TX = FALSE;
          break;

          default:break;
        }
      }
    
      // if received from RX BUF, then want to process received data
      if(!ready_to_RX){
        int i=_0u;
        int RX_intArray[_6u] = {_0u};

        ready_to_RX = TRUE;

        // create temp copyRX b/c RX_ASCII_information is declared volatile
        for(i=_0u; i<_6u; i++){
          copyRX[i] = RX_ASCII_information[i];
        }
        ASCIIarrayToIntArray(copyRX, RX_intArray); // convert temp copyRX ASCII[] to RX Int[] to check [0] 
        // index[0] is the position for the current_sequence head

        switch(RX_intArray[_0u]){
          case _1u:
            copyCharArray(copyRX, sizeof(copyRX), RX_ASCII_1);
            ProcessData(RX_ASCII_1);
          break;

          case _2u:
            copyCharArray(copyRX, sizeof(copyRX), RX_ASCII_2);
            ProcessData(RX_ASCII_2);
          break;

          case _3u:
            copyCharArray(copyRX, sizeof(copyRX), RX_ASCII_3);
            ProcessData(RX_ASCII_3);
          break;

          default:break;
        }
      }   
    */

      interrupt_event &= ~TimerA0_0_IE;
    }

    /*
    // TIMER B1_1 IE
    if(interrupt_event & TimerB1_1_IE){
      interrupt_event &= ~TimerB1_1_IE;    
    }
    */
      

     // THINK ABOUT DISABLING TIMER B1_1 INTERRUPT BEFORE ENABLING TIMER B2_1 INTERRUPT!!!!!!!!!!

   } // end of while()

  //------------------------------------------------------------------------------

  } // end of Main()



  /*
================================================================================
Function Name: Display_Process

Description: This function displays a message to each line of the LCD

Passed: none
Locals: none
Returned: none
Globals: display_1, display_2, display_3, display_4, posL1, posL2, posL3, posL4

Author: Michael Patel
Date: September 2016
Compiler: Built with IAR Embedded Workbench Version: V7.4.2.4369 (6.50.1)
================================================================================
*/
void Display_Process(void){
  ClrDisplay();
  lcd_out(display_1, LCD_HOME_L1, posL1);
  lcd_out(display_2, LCD_HOME_L2, posL2);
  lcd_out(display_3, LCD_HOME_L3, posL3);
  lcd_out(display_4, LCD_HOME_L4, posL4);
}


 /*
  ================================================================================
  Function Name: *toString()

  Description: This function converts a char[] to a char* (string)

  Passed: char[], int, char[]
  Locals: int
  Returned: char* (string) 
  Globals: none

  Author: Michael Patel
  Date: October 2016
  Compiler: Built with IAR Embedded Workbench Version: V7.4.2.4369 (6.50.1)
  ================================================================================
  */
  char *toString(char in[], int size, char out[]){
    int i;
    for(i=_0u; i<size; i++){
      out[i] = in[i];
    }
    out[size] = '\0'; // char[] => string

    return out;
  }

 /*
  ================================================================================
  Function Name: copyCharArray()

  Description: This function copies a char array to another char array

  Passed: char[], int, char[]
  Locals: int
  Returned: none
  Globals: none

  Author: Michael Patel
  Date: November 2016
  Compiler: Built with IAR Embedded Workbench Version: V7.4.2.4369 (6.50.1)
  ================================================================================
  */
void copyCharArray(char in[], int size, char out[]){
  int i;
  for(i=_0u; i<size; i++){
    out[i] = in[i];
  }
}

  /*
  ================================================================================
  Function Name: DetermineState()

  Description: This function determines the state (BB, BW, WB, WW)

  Passed: none
  Locals: none
  Returned: int
  Globals: leftState, rightState, BB_state_counter, BW_state_counter,
           WB_state_counter, WW_state_counter

  Author: Michael Patel
  Date: October 2016
  Compiler: Built with IAR Embedded Workbench Version: V7.4.2.4369 (6.50.1)
  ================================================================================
  */
  int DetermineState(void){
    if((leftState == BLACK) && (rightState == BLACK)){
      // count consecutive BB states
      BB_state_counter++;
      BW_state_counter=COUNT_EQUALS_ZERO;
      WB_state_counter=COUNT_EQUALS_ZERO;
      WW_state_counter=COUNT_EQUALS_ZERO;
      return ON_BB;
    }
    else if((leftState == BLACK) && (rightState == WHITE)){
      // count consecutive BW states
      BW_state_counter++;
      BB_state_counter=COUNT_EQUALS_ZERO;
      WB_state_counter=COUNT_EQUALS_ZERO;
      WW_state_counter=COUNT_EQUALS_ZERO;
      return ON_BW;
    }
    else if((leftState == WHITE) && (rightState == BLACK)){
      // count consecutive WB states
      WB_state_counter++;
      BB_state_counter=COUNT_EQUALS_ZERO;
      BW_state_counter=COUNT_EQUALS_ZERO;
      WW_state_counter=COUNT_EQUALS_ZERO;
      return ON_WB;
    }
    else{
      // count consecutive WW states
      WW_state_counter++;
      BB_state_counter=COUNT_EQUALS_ZERO;
      BW_state_counter=COUNT_EQUALS_ZERO;
      WB_state_counter=COUNT_EQUALS_ZERO;
      return ON_WW;
    }
  }


  /*
  ================================================================================
  Function Name: DetermineDirection()

  Description: This function determines which direction the car is veering

  Passed: int
  Locals: none
  Returned: char *
  Globals: state_flag

  Author: Michael Patel
  Date: October 2016
  Compiler: Built with IAR Embedded Workbench Version: V7.4.2.4369 (6.50.1)
  ================================================================================
  */
  /*
  char *DetermineDirection(unsigned int state){
    if(state & ON_BB){
      return "FORWARD";
    }
    else if(state & ON_WB){
      return "LEFT";
    }
    else if(state & ON_BW){
      return "RIGHT";
    }
    else{
      return "Ken Boned";
    }
  }
  */

  /*
  ================================================================================
  Function Name: BlackOrWhite()

  Description: This function determines whether the ADC value corresponds to Black
         or White

  Passed: int
  Locals: none
  Returned: int
  Globals: none

  Author: Michael Patel
  Date: October 2016
  Compiler: Built with IAR Embedded Workbench Version: V7.4.2.4369 (6.50.1)
  ================================================================================
  */
  int BlackOrWhite(unsigned int HexReg){
    if((BLACK_BASE - BLACK_OFFSET) < HexReg){
      return BLACK;
    }

    else{
      return WHITE;
    }
  }


    /*
  ================================================================================
  Function Name: fsm()

  Description: This function runs the fsm for following a black line

  Passed: none
  Locals: none
  Returned: none
  Globals: detected_BB, current_state

  Author: Michael Patel
  Date: October 2016
  Compiler: Built with IAR Embedded Workbench Version: V7.4.2.4369 (6.50.1)
  ================================================================================
  */
  void fsm(void){
    if(detected_BB){ // detected black line once
      switch(current_state){
        case ON_BB:
          Forward();
        break;

        case ON_BW:
          Left();
        break;

        case ON_WB:
          Right();
        break;

        default:
          // ON_WW
          /*
          if(WW_state_counter > _5000u){
            turnAllWheelsOFF();
            detected_BB=FALSE;
            WW_state_counter=_0u;
          }
          else{
            // don't change PWM
          }  
          */
        break;
      }
    } // end of fsm
  }


  /*
  ================================================================================
  Function Name: detectBlackLine()

  Description: This function detects the black line

  Passed: none
  Locals: none
  Returned: none
  Globals: BB_state_counter, detected_BB

  Author: Michael Patel
  Date: October 2016
  Compiler: Built with IAR Embedded Workbench Version: V7.4.2.4369 (6.50.1)
  ================================================================================
  */
  void detectBlackLine(void){
    if(BB_state_counter == _1u){
      //turnAllWheelsOFF();
      detected_BB=TRUE;
    }
  }



 /*
  ================================================================================
  Function Name: ASCIIarrayToIntArray()

  Description: This function converts a char[] to an int array

  Passed: char[], int[]
  Locals: int
  Returned: none
  Globals: none

  Author: Michael Patel
  Date: November 2016
  Compiler: Built with IAR Embedded Workbench Version: V7.4.2.4369 (6.50.1)
  ================================================================================
  */
void ASCIIarrayToIntArray(char ASCIIarray[], int intArray[]){
  int i=_0u;

  for(i=_0u; i<_5u; i++){
    if((_48u <= ASCIIarray[i]) && (ASCIIarray[i] <= _57u)){
      intArray[i] = ASCIIarray[i] - _48u;
    }
  }
}


 /*
  ================================================================================
  Function Name: IntArrayToInt()

  Description: This function converts an int[] to an int

  Passed: int[], int
  Locals: int
  Returned: none
  Globals: none

  Author: Michael Patel
  Date: November 2016
  Compiler: Built with IAR Embedded Workbench Version: V7.4.2.4369 (6.50.1)
  ================================================================================
  */
int IntArrayToInt(int intArray[]){
  int i=_0u;
  int integer=_0u;

  for(i=_0u; i<_5u; i++){
    integer = (_10u*integer) + intArray[i];    
  }
  hold_sequence_count = intArray[_0u];
  return integer;
}


 /*
  ================================================================================
  Function Name: IntToIntArray()

  Description: This function converts an int to int[]

  Passed: int, int[]
  Locals: int
  Returned: none
  Globals: none

  Author: Michael Patel
  Date: November 2016
  Compiler: Built with IAR Embedded Workbench Version: V7.4.2.4369 (6.50.1)
  ================================================================================
  */
void IntToIntArray(int integer, int intArray[]){
  int i=_0u;

  for(i=_4u; i>=_0u; i--){
    intArray[i] = integer % _10u;
    integer = integer - intArray[i];
    integer = integer / _10u;
  }
  intArray[_0u] = hold_sequence_count;
}


 /*
  ================================================================================
  Function Name: IntArrayToASCIIarray()

  Description: This function converts an int[] to char[]

  Passed: int[], char[]
  Locals: int
  Returned: none
  Globals: none

  Author: Michael Patel
  Date: November 2016
  Compiler: Built with IAR Embedded Workbench Version: V7.4.2.4369 (6.50.1)
  ================================================================================
  */
void IntArrayToASCIIarray(int intArray[],char ASCIIarray[]){
  int i=_0u;

  for(i=_0u; i<_5u; i++){
    if((_0u <= intArray[i]) && (intArray[i] <= _9u)){
      ASCIIarray[i] = intArray[i] + _48u;
    }
  }
}


 /*
  ================================================================================
  Function Name: PrepForTXandDisplay()

  Description: This function prepares a char[] for TX and prepares a char[] 
               for the LCD

  Passed: int[]
  Locals: int, char
  Returned: none
  Globals: none

  Author: Michael Patel
  Date: November 2016
  Compiler: Built with IAR Embedded Workbench Version: V7.4.2.4369 (6.50.1)
  ================================================================================
  */
/*
void PrepForTXandDisplay(int TX_intArray[]){
  int i;
  char TX_ASCII_string_1[_6u];
  char TX_ASCII_string_2[_6u];
  char TX_ASCII_string_3[_6u];
  char *displayString_1;
  char *displayString_2;
  char *displayString_3;
  char copyTX_1[_6u];
  char copyTX_2[_6u];
  char copyTX_3[_6u];

  current_sequence = TX_intArray[_0u];

  switch(current_sequence){
    case _1u:
      IntArrayToASCIIarray(TX_intArray, copyTX_1); // convert TX Int[] to copyTX ASCII[]

      // convert copyTX ASCII[] to string for LCD
      for(i=_1u; i<sizeof(copyTX_1); i++){
        TX_ASCII_string_1[i-_1u] = copyTX_1[i];
      }
      TX_ASCII_string_1[_5u] = '\0';
      displayString_1 = TX_ASCII_string_1;
      DetermineDisplayLine(displayString_1, current_sequence); // determine where to place each sequence count on LCD

      // prep TX_ASCII[] with "CHK" start sequence
      for(i=_0u; i<sizeof(copyTX_1); i++){
        TX_ASCII_1[i+_3u] = copyTX_1[i];
      }
      TX_ASCII_1[_0u] = 'C';
      TX_ASCII_1[_1u] = 'H';
      TX_ASCII_1[_2u] = 'K';

      ready_to_TX = TRUE;
    break;

    case _2u:
      IntArrayToASCIIarray(TX_intArray, copyTX_2); // convert TX Int[] to copyTX ASCII[]

      // convert copyTX ASCII[] to string for LCD
      for(i=_1u; i<sizeof(copyTX_2); i++){
        TX_ASCII_string_2[i-_1u] = copyTX_2[i];
      }
      TX_ASCII_string_2[_5u] = '\0';
      displayString_2 = TX_ASCII_string_2;
      DetermineDisplayLine(displayString_2, current_sequence); // determine where to place each sequence count on LCD

      // prep TX_ASCII[] with "CHK" start sequence
      for(i=_0u; i<sizeof(copyTX_2); i++){
        TX_ASCII_2[i+_3u] = copyTX_2[i];
      }
      TX_ASCII_2[_0u] = 'C';
      TX_ASCII_2[_1u] = 'H';
      TX_ASCII_2[_2u] = 'K';
  
      ready_to_TX = TRUE;
    break;

    case _3u:
      IntArrayToASCIIarray(TX_intArray, copyTX_3); // convert TX Int[] to copyTX ASCII[]

      // convert copyTX ASCII[] to string for LCD
      for(i=_1u; i<sizeof(copyTX_3); i++){
        TX_ASCII_string_3[i-_1u] = copyTX_3[i];
      }
      TX_ASCII_string_3[_5u] = '\0';
      displayString_3 = TX_ASCII_string_3;
      DetermineDisplayLine(displayString_3, current_sequence); // determine where to place each sequence count on LCD

      // prep TX_ASCII[] with "CHK" start sequence
      for(i=_0u; i<sizeof(copyTX_3); i++){
        TX_ASCII_3[i+_3u] = copyTX_3[i];
      }
      TX_ASCII_3[_0u] = 'C';
      TX_ASCII_3[_1u] = 'H';
      TX_ASCII_3[_2u] = 'K';
  
      ready_to_TX = TRUE;
    break;

    default:break;
  }
}
*/

 /*
  ================================================================================
  Function Name: DetermineDisplayLine()

  Description: This function writes a string to a specific display line

  Passed: char*, int
  Locals: int
  Returned: none
  Globals: none

  Author: Michael Patel
  Date: November 2016
  Compiler: Built with IAR Embedded Workbench Version: V7.4.2.4369 (6.50.1)
  ================================================================================
  */
/*
void DetermineDisplayLine(char *displayString, int num_of_seq){
  switch(num_of_seq){
    case _1u:
      display_1 = displayString;
      display_2 = display_3 = "";
    break;

    case _2u:
      display_2 = displayString;
      display_1 =  display_3 = "";
    break;

    case _3u:
      display_3 = displayString;
      display_1 = display_2 = "";
    break;

    default:break;
  }
  Display_Process();
}
*/

 /*
  ================================================================================
  Function Name: ProcessData()

  Description: This function converts the RX char[] to the TX char[]

  Passed: char[]
  Locals: int
  Returned: none
  Globals: none

  Author: Michael Patel
  Date: November 2016
  Compiler: Built with IAR Embedded Workbench Version: V7.4.2.4369 (6.50.1)
  ================================================================================
  */
/*
void ProcessData(char RX_ASCII[]){
  int RX_intArray[_6u];
  int TX_intArray[_6u];
  int integer;

  ASCIIarrayToIntArray(RX_ASCII, RX_intArray);
  integer = IntArrayToInt(RX_intArray);
  if(integer < MAX_FFFF){
    integer++;
  }
  else{
    integer = COUNT_EQUALS_ZERO;
  }
  IntToIntArray(integer, TX_intArray);
  PrepForTXandDisplay(TX_intArray);
}
*/

 /*
  ================================================================================
  Function Name: out_character()

  Description: This function sends a char[] to the A1 TX BUF

  Passed: char[], int
  Locals: int
  Returned: none
  Globals: none

  Author: Michael Patel
  Date: November 2016
  Compiler: Built with IAR Embedded Workbench Version: V7.4.2.4369 (6.50.1)
  ================================================================================
  */
void out_character(char TX[], int size){
  int i=_0u;
  while(i < size){
    if(UCA1IFG & UCTXIFG){
      UCA1TXBUF = TX[i];
      i++;
    }        
  }
}


 /*
  ================================================================================
  Function Name: setBaudRate()

  Description: This function sets the Baud rate

  Passed: int, int
  Locals: none
  Returned: none
  Globals: baud_rate, baud_rate_remainder

  Author: Michael Patel
  Date: November 2016
  Compiler: Built with IAR Embedded Workbench Version: V7.4.2.4369 (6.50.1)
  ================================================================================
  */

void setBaudRate(int rate, int rateRemainder){
  baud_rate = rate;
  baud_rate_remainder = rateRemainder;
  Init_Serial_UCA0();
  Init_Serial_UCA1();
}


 /*
  ================================================================================
  Function Name: prepVehicleMoveIOT()

  Description: This function preps the vehicle for IOT move commands

  Passed: none
  Locals: none
  Returned: none
  Globals: vehicle_move_count, vehicle_move_count_flag

  Author: Michael Patel
  Date: November 2016
  Compiler: Built with IAR Embedded Workbench Version: V7.4.2.4369 (6.50.1)
  ================================================================================
  */
void prepVehicleMoveIOT(void){
  vehicle_move_count = COUNT_EQUALS_ZERO;
  vehicle_move_count_flag = TRUE;
  clearFRAMcommand();
  clearWEBcommand();
}

 /*
  ================================================================================
  Function Name: clearFRAMcommand()

  Description: This function clears the terminal side of IOT

  Passed: none
  Locals: int
  Returned: none
  Globals: command, FRAMcommand

  Author: Michael Patel
  Date: November 2016
  Compiler: Built with IAR Embedded Workbench Version: V7.4.2.4369 (6.50.1)
  ================================================================================
  */
void clearFRAMcommand(void){
  int i;
  for(i=_0u; i<sizeof(command); i++){
    command[i] = _0u;
  }
  FRAMcommand = NONE;
}


 /*
  ================================================================================
  Function Name: clearWEBcommand()

  Description: This function clears the WEB interface side of IOT

  Passed: none
  Locals: int
  Returned: none
  Globals: commandIOT, webcommand

  Author: Michael Patel
  Date: November 2016
  Compiler: Built with IAR Embedded Workbench Version: V7.4.2.4369 (6.50.1)
  ================================================================================
  */
void clearWEBcommand(void){
  int i;
  for(i=_0u; i<sizeof(commandIOT); i++){
    commandIOT[i] = _0u;
  }
  webcommand = NONE;
}


 /*
  ================================================================================
  Function Name: clearIOTcode()

  Description: This function clears the received IOT code from module

  Passed: none
  Locals: none
  Returned: none
  Globals: IOTcode

  Author: Michael Patel
  Date: November 2016
  Compiler: Built with IAR Embedded Workbench Version: V7.4.2.4369 (6.50.1)
  ================================================================================
  */
void clearIOTcode(void){
  IOTcode = NONE;
}

 /*
  ================================================================================
  Function Name: initializeIOT()

  Description: This function initializes the IOT

  Passed: none
  Locals: none
  Returned: none
  Globals: init_IOT_count_flag, init_IOT_count

  Author: Michael Patel
  Date: November 2016
  Compiler: Built with IAR Embedded Workbench Version: V7.4.2.4369 (6.50.1)
  ================================================================================
  */
void initializeIOT(void){
  clearFRAMcommand();
  clearWEBcommand();
  display_2 = "Scanning";
  init_IOT_count_flag = TRUE;
  init_IOT_count = COUNT_EQUALS_ZERO;
}


 /*
  ================================================================================
  Function Name: reconnectIOT()

  Description: This function reconnects the IOT

  Passed: none
  Locals: none
  Returned: none
  Globals: connect_IOT_count, connect_IOT_count_flag

  Author: Michael Patel
  Date: November 2016
  Compiler: Built with IAR Embedded Workbench Version: V7.4.2.4369 (6.50.1)
  ================================================================================
  */
void reconnectIOT(void){
  clearFRAMcommand();
  clearWEBcommand();
  display_2 = "Scanning";
  connect_IOT_count_flag = TRUE;
  connect_IOT_count = COUNT_EQUALS_ZERO;
}

 /*
  ================================================================================
  Function Name: getStatusIOT()

  Description: This function retrieves the status of the IOT (MAC address, IP address)

  Passed: none
  Locals: none
  Returned: none
  Globals: none

  Author: Michael Patel
  Date: November 2016
  Compiler: Built with IAR Embedded Workbench Version: V7.4.2.4369 (6.50.1)
  ================================================================================
  */
void getStatusIOT(void){
  out_character(ATcheckStatus, strlen(ATcheckStatus));
  out_character(ATmacAddr, strlen(ATmacAddr));
  out_character(ATgetIPaddress, strlen(ATgetIPaddress));
}


 /*
  ================================================================================
  Function Name: prepIOTtoBlackLine

  Description: This function preps the vehicle for Black Line following

  Passed: none
  Locals: none
  Returned: none
  Globals: follow_Black_Line_flag, detected_BB, BB_state_counter, leftState, rightState, currentState

  Author: Michael Patel
  Date: November 2016
  Compiler: Built with IAR Embedded Workbench Version: V7.4.2.4369 (6.50.1)
  ================================================================================
  */
void prepIOTtoBlackLine(void){
  clearFRAMcommand();
  clearWEBcommand();
  P3OUT |= IR_LED; // turn on IR LED
  turnAllWheelsOFF();
  Forward(); // travel forward indefinitely
  display_2 = "BL";  
  follow_Black_Line_Flag = TRUE;
  detected_BB = FALSE;
  BB_state_counter = COUNT_EQUALS_ZERO;
  leftState = rightState = current_state = NONE;
  ADC10CTL0 |= ADC10ENC + ADC10SC; // Enable and start ADC conversion  
}


 /*
  ================================================================================
  Function Name: prepBlackLineToIOT()

  Description: This function preps the vehicle for IOT

  Passed: none
  Locals: none
  Returned: none
  Globals: follow_Black_Line_Flag

  Author: Michael Patel
  Date: November 2016
  Compiler: Built with IAR Embedded Workbench Version: V7.4.2.4369 (6.50.1)
  ================================================================================
  */
void prepBlackLineToIOT(void){
  clearFRAMcommand();
  clearWEBcommand();
  turnAllWheelsOFF();
  ADC10CTL0 &= ~ADC10ENC;
  P3OUT &= ~IR_LED; // turn off IR LED
  follow_Black_Line_Flag = FALSE; // want to drive via IOT commands
  display_2 = "IOT";  
}

/*
  ================================================================================
  Function Name: ADC_Right()

  Description: This function performs an action based on the ADC_Right_Detector value

  Passed: none
  Locals: none
  Returned: none
  Globals: rightHexReg, ADC_Right_Detector, rightState

  Author: Michael Patel
  Date: November 2016
  Compiler: Built with IAR Embedded Workbench Version: V7.4.2.4369 (6.50.1)
  ================================================================================
  */
void ADC_Right(void){
  rightHexReg += ADC_Right_Detector; // summing 16th ADC_Right_Detector value
  rightHexReg = rightHexReg >> _4u; // get average right value
  //HEXtoBCD(rightHexReg); // convert it to ASCII
  //display_2 = toString(rightASCIIReg, adc_char); // convert adc_char to string
  rightState = BlackOrWhite(rightHexReg); // determine whether right is on Black or on White
}


/*
  ================================================================================
  Function Name: ADC_Left()

  Description: This function performs an action based on the ADC_Left_Detector value

  Passed: none
  Locals: none
  Returned: none
  Globals: leftHexReg, ADC_Left_Detector, leftState

  Author: Michael Patel
  Date: November 2016
  Compiler: Built with IAR Embedded Workbench Version: V7.4.2.4369 (6.50.1)
  ================================================================================
  */
void ADC_Left(void){
  leftHexReg += ADC_Left_Detector; // summing 16th ADC_Left_Detector value
  leftHexReg = leftHexReg >> _4u; // get average left value
  //HEXtoBCD(leftHexReg); // convert it to ASCII
  //display_3 = toString(leftASCIIReg, adc_char); // convert adc_char to string
  leftState = BlackOrWhite(leftHexReg); // determine whether left is on Black or on White
}