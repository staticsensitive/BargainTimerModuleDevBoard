/*
MCU: STC8F2K16S2
Clock: Internal RC 11.0592 MHz
Board: E-Gizmo Bargain Timer Module
       Converted to 8051 Development Board
*/
#include <STC8.H>


#define SERVO     P27
#define tPWM      0xB7FE //Reload value 

#define S1 P20
#define S2 P21
#define S3 P22

unsigned int tHigh, tLow, Duty;


/*Timer 0 Interrupt Service Routine*/
void timer0Isr (void) interrupt 1
{
	SERVO = !SERVO;
	
	if(SERVO){
		TH0 = (tHigh >>8);
		TL0 = tHigh;
	}else{
		TH0 = (tLow >> 8);
		TL0 = tLow;
	}
	
}

void initTimer0 (void)
{
	EA = 1;
	ET0 = 1;
	
	TMOD = 0x01; //Timer 0 Mode 1
	TH0 = (tPWM >> 8);
	TL0 = tPWM;
	TR0 = 1;
	

}

/*Calculate On Time & Off Time*/
void setDuty (float duty)
{
	float t = 65535 - tPWM;
	tHigh = ((t/100.0) * duty);
	tLow = (t - tHigh);
	tHigh = 65535 - tHigh;
	tLow = 65535 - tLow;
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
	unsigned int d = 0;
	
	InitBoard();
	
	initTimer0();
	S1 = 1;
	S2 = 1;
	S3 = 1;
	
	
	
	  while(1)
		{
				if(S1 == 0){
					delay_ms(200);
					setDuty(2.7);	//1ms duty 0 degree
				}
				
				if(S2 == 0){
					delay_ms(200);
					setDuty(7); //1.5ms 90 degrees
				}
				
				if(S3 == 0){
					delay_ms(200);
					setDuty(12); //2ms 180 degrees
				}
									
					
			
		}
}
