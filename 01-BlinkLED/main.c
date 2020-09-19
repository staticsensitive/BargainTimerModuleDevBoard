/*
MCU: STC8F2K16S2
Clock: Internal RC 11.0592 MHz
Board: E-Gizmo Bargain Timer Module
       Converted to 8051 Development Board
*/
#include <STC8.H>


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
	
	  while(1)
		{
			 P27 = !P27;
			 delay_ms(500);
			 
		}
}
