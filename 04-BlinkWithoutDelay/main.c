/*
MCU: STC8F2K16S2
Clock: Internal RC 11.0592 MHz
Board: E-Gizmo Bargain Timer Module
       Converted to 8051 Development Board
*/
#include <STC8.H>


#define LED     P27

volatile unsigned long millis = 0;

/*Timer 0 Interrupt Service Routine*/
void timer0Isr (void) interrupt 1
{
	millis++;
	
}

void initTimer0 (void)
{
	/*T0x12 by default is SYSclk/12
	To Find the Values of TL0 and TH0:
		  TH0TL0 = (65536 - (FOSC/12))/1000
	
	if T0x12 is SYSClk/1
	To Find the Values of TL0 and TH0:
		  TH0TL0 = (65536 - (FOSC))/1000
	
	SYSClk can be set at the Auxiliary Register 1 Bit 7
	
	*/
	TMOD = 0x00; //Timer 0 Mode 0
	TL0 = 0x66;  //T0 Values for 1ms
	TH0 = 0xFC;  //interrupt
	
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



void main (void)
{
	unsigned long prevMillis = 0;
	unsigned int interval = 500;
	
	InitBoard();
	
	initTimer0();
	
	
	
	  while(1)
		{
					if(millis - prevMillis > interval){
						prevMillis = millis;
						
						LED = !LED;
					}
			 
		}
}
