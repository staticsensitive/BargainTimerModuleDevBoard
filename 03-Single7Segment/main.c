/*
MCU: STC8F2K16S2
Clock: Internal RC 11.0592 MHz
Board: E-Gizmo Bargain Timer Module
       Converted to 8051 Development Board
*/
#include <STC8.H>

unsigned int pattern[10] = {0x3F,0x06,0x5B,0x4F,0x66,0x6D,0x7D,0x07,0x7F,0x6F};

#define DIGIT1    P01
#define SEGMENTS  P1


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
	unsigned char count;
	InitBoard();
	
	DIGIT1 = 1; //Turn on 1 Digit of the Seven Segment Display
	
	
	
	  while(1)
		{
					count++;
			    if(count > 9){
						count = 0;}
					
					SEGMENTS = pattern[count];

					delay_ms(500);
					
		}
}
