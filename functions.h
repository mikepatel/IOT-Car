// Function prototypes main
void main(void);
void Init_Conditions(void);
void Switches_Process(void);
void Init_Timers(void);
void Init_LEDs(void);
void Display_Process(void);
//void five_msec_sleep(unsigned int fivemsec);
void Timer_code(void);

// Function prototypes clocks
void Init_Clocks(void);

// Function prototypes systems
void enable_interrupts(void);

// Function prototypes
__interrupt void Timer2_B0_ISR(void);
 __interrupt void TIMER2_B1_ISR(void);
void Init_Timer_A0(void);
void Init_Timer_B2(void);
void measure_delay(void);
void usleep10(unsigned int usec);

// Function prototypes ports
void Init_Ports(void);
void Init_Port1(void);
void Init_Port2(void);
void Init_Port3(void);
void Init_Port4(void);
void Init_PortJ(unsigned int);

// LCD
void Init_LCD(void);
void WriteIns(char instruction);
void WriteData(char data);
void ClrDisplay(void);
void SetPostion(char pos);
void DisplayOnOff(char data);
void lcd_BIG_mid(void);
void lcd_4line(void);
void lcd_out(char *s, char line, char position);

void grab_a_character(void);
int wait_for_character(void);
void menu(void);

// SPI
void Init_SPI_B0(void);
void SPI_B0_write(char byte);

// Switches
void Init_Switches(void);
void switch_control(void);
void enable_switch_SW1(void);
void enable_switch_SW2(void);
void disable_switch_SW1(void);
void disable_switch_SW2(void);
void Switches_Process(void);


// 
/*
void checkWheels(void);

int checkLeftWheels(void);
int checkRightWheels(void);

int checkForwardLeftWheel(void);
int checkForwardRightWheel(void);
int checkReverseLeftWheel(void);
int checkReverseRightWheel(void);
*/
// 
void turnForwardWheelsON(void);
//void turnReverseWheelsON(void);

void turnAllWheelsOFF(void);
void turnLeftWheelOFF(void);
void turnRightWheelOFF(void);
//void turnForwardWheelsOFF(void);
//void turnReverseWheelsOFF(void);

/*
void turnForwardLeftWheelON(void);
void turnForwardRightWheelON(void);
void turnReverseLeftWheelON(void);
void turnReverseRightWheelON(void);
*/
/*
void turnForwardLeftWheelOFF(void);
void turnForwardRightWheelOFF(void);
void turnReverseLeftWheelOFF(void);
void turnReverseRightWheelOFF(void);
*/
// 
//void forward(unsigned int);
//void reverse(unsigned int);

// shapesc
void Circle(unsigned int);
void FigureEight(void);
void Triangle(void);

// Timers
void Five_msec_Delay(unsigned int fivemsec);

// Interrupt switch-cases
void SW1_Pressed(void);
void SW2_Pressed(void);
void Toggle_LCD_100ms(void);

// Project 4
/*
void forward(void);
void reverse(void);
void pause(void);
void spin_clockwise(void);
void spin_counterclockwise(void);
void Move_Car(void);
*/

// Project 5
void Init_ADC(void);
void ADC_Process(void);
void HEXtoBCD(int);
char* DetermineDirection(unsigned int);
int BlackOrWhite(unsigned int);

// Project 6
void Init_Timer_B1(void);
void Forward(void);
void Right(void);
void Left(void);
char *toString(char[], int, char[]);
int DetermineState(void);
void detectBlackLine(void);
void fsm(void);

// Homework 8
void Init_Serial_UCA0(void);
void Init_Serial_UCA1(void);


// Project 7
void ASCIIarrayToIntArray(char*, int*);
int IntArrayToInt(int*);
void IntToIntArray(int, int*);
void IntArrayToASCIIarray(int*, char*);
void DetermineDisplayLine(char*, int);
void PrepForTXandDisplay(int*);
void ProcessData(char*);
void out_character(char*, int);
void copyCharArray(char*, int, char*);

// Project 8
void setBaudRate(int, int);
void Backward(void);
void prepVehicleMoveIOT(void);
void clearFRAMcommand(void);
void clearWEBcommand(void);

// Project 9
void initializeIOT(void);
void reconnectIOT(void);
void getStatusIOT(void);
void clearIOTcode(void);
void prepIOTtoBlackLine(void);
void prepBlackLineToIOT(void);
void ADC_Right(void);
void ADC_Left(void);