/*
MCU: STC8F2K16S2
Clock: Internal RC 11.0592 MHz
Board: E-Gizmo Bargain Timer Module
       Converted to 8051 Development Board

This is a sample program using the Serial Port 0 
of the MCU at 9600 Baudrate
*/
#include <STC8.H>

#define FOSC 11059200UL
#define BAUD (65536-FOSC/9600/4)


bit busy;
char wptr;
char rptr;
char buffer[16];


void UARTISR() interrupt 4
{
	
	if(TI)
	{
		TI = 0;
		busy = 0;
	}
	
	if(RI)
	{
		RI=0;
		buffer[wptr++] = SBUF;
		wptr &= 0x0F;
	}
}


void initUART (void)
{
	SCON = 0x50;
	T2L = BAUD;
	T2H = BAUD >> 8;
	AUXR = 0x15;
	wptr = 0x00;
	rptr = 0x00;
	busy = 0x00;
}

void UARTPutc (char dat)
{
	while(busy);
	busy = 1;
	SBUF = dat;
}

void UARTPuts (char *p)
{
	 while (*p)
	 {
		 UARTPutc(*p++);
	 }
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
	InitBoard();
	initUART();
	ES = 1;
	EA = 1;
	
	UARTPuts("Hello World");
	
		while(1){
			if(rptr != wptr){
				UARTPutc(buffer[rptr++]);
				rptr &= 0x0F;
			}
		}
}
