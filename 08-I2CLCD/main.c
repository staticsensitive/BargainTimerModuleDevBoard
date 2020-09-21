/*
MCU: STC8F2K16S2
Clock: Internal RC 11.0592 MHz
Board: E-Gizmo Bargain Timer Module
       Converted to 8051 Development Board
*/
#include <STC8.H>
#include "board.h"
#include "lcd.h"


void main (void)
{
	InitBoard();
	
	
	lcdInit();
	lcdsetCursor(1,0);
	lcdPuts("Hello World");
  delay_ms(2000);
  lcdClear();
  lcdsetCursor(1,0);
  lcdPuts("Line 1");
  lcdsetCursor(1,1);
  lcdPuts("Line 2");	


	
	  while(1)
		{
			
			 
		}
}





