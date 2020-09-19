/*
MCU: STC8F2K16S2
Clock: Internal RC 11.0592 MHz
Board: E-Gizmo Bargain Timer Module
       Converted to 8051 Development Board
*/
#include <STC8.H>


#define SWITCH  P20
#define LED     P27

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
	
	SWITCH = 1; //enable weak pull-up
	
	  while(1)
		{
			 if(SWITCH == 0){
				 delay_ms(200); //debounce delay
				 
				 LED ^= 1; //XOR State of LED 
			 }
			 
		}
}
