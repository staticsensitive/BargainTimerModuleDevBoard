#include "board.h"


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



void delay_us(unsigned int us_count)
 {    
    while(us_count!=0)
      {
         us_count--;
       }
 }