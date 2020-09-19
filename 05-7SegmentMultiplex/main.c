/*
MCU: STC8F2K16S2
Clock: Internal RC 11.0592 MHz
Board: E-Gizmo Bargain Timer Module
       Converted to 8051 Development Board
*/
#include <STC8.H>


unsigned int pattern[10] = {0x3F,0x06,0x5B,0x4F,0x66,0x6D,0x7D,0x07,0x7F,0x6F};

#define SEGMENT     P1
#define DIGIT1		  P01
#define DIGIT2	    P02
#define DIGIT3      P03

volatile unsigned char mux = 0;
volatile int count = 0;

/*Timer 0 Interrupt Service Routine*/
void timer0Isr (void) interrupt 1
{
	unsigned char temp;
	
	/*Cycle Thru the digits*/
	switch(mux)
	{
		case 0: 
			temp = (count/100)%10; //Get Hundreds
		  DIGIT1 = 1; //Turn on Hundreds Digit
		  DIGIT2 = 0; //Turn off Tens Digit
		  DIGIT3 = 0; //Turn off Ones DIgit
		  SEGMENT = pattern[temp]; //Display Number
		  break;

		case 1: 
			temp = (count/10)%10; //Get Tens
		  DIGIT1 = 0; //Turn off Hundreds Digit
		  DIGIT2 = 1; //Turn on Tens Digit
		  DIGIT3 = 0; //Turn off Ones Digit
		  SEGMENT = pattern[temp]; //Display Number
		  break;

		case 2: 
			temp = count%10; //Get Ones
		  DIGIT1 = 0; //Turn off Hundreds Digit
		  DIGIT2 = 0; //Turn off Tens Digit
		  DIGIT3 = 1; //Turn on Ones Digit
		  SEGMENT = pattern[temp]; //Display Number
		  break;
	}
	
	
	mux++;
	if(mux >2){mux = 0;}
	
}

void initTimer0 (void)
{
	/*
	  Configure Timer 0 for 100Hz ISR
	*/
	TMOD = 0x00; //Timer 0 Mode 0
	TL0 = 0xFF;  //T0 Values for 10ms
	TH0 = 0xDB;  //interrupt
	
	TR0 = 1;		//Start the Timer
	ET0 = 1;		//Enable the Timer Interrupt
	EA = 1;			//Enable GlobalInterrupt
}

//Turn Off Other LEDS in the Board
void InitBoard (void)
{
	P1 = 0x00;
	P0 = 0x01;
	P55 = 0;
	P34 = 0;
	P24 = 0;
	P25 = 0;
	P26 = 1;
	P27 = 1;
}

//Approx 1ms delay for 11.0592 Internal Clock
//Compiled in Keil uVision 5.27.1 C51 Compiler
void delay_ms (int ms)
{
	int i,j;
	
	for(i=0; i<ms; i++){
		for(j=0; j<1500; j++);
	}
}


void main (void)
{
	
		
	InitBoard();
	initTimer0();
	
	
	
	  while(1)
		{
				count++;
				
				if(count > 999){count = 0;}
				
				delay_ms(100);
			 
		}
}
