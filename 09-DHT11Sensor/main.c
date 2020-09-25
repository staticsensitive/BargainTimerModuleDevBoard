/*
MCU: STC8F2K16S2
Clock: Internal RC 11.0592 MHz
Board: E-Gizmo Bargain Timer Module
       Converted to 8051 Development Board
*/
#include <STC8.H>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include "board.h"
#include "lcd.h"

#define DHT P54

unsigned char DHT_DATA[5];

unsigned char getByte (void)
{
	unsigned char s = 0;
	
	unsigned char val = 0;
	
	for(s=0; s<8; s++){
		val <<= 1;
		while(DHT == 0);
		delay_us(40);
		if(DHT == 1){
			val |= 1;
		}
		while(DHT == 1);
	}
	
	return val;
}


unsigned char getData (void)
{
	
	unsigned char sum = 0;
	
	DHT = 1;			//requestdata
	DHT = 0;
	delay_ms(20);
	DHT = 1;
	delay_us(30);
	
	
	while(DHT == 1);	//wait for response
	while(DHT == 0);
	while(DHT == 1);

			
	//read data
	DHT_DATA[0] = getByte();
	DHT_DATA[1] = getByte();
	DHT_DATA[2] = getByte();
	DHT_DATA[3] = getByte();
	DHT_DATA[4] = getByte();
	
	DHT = 1;
	
	sum = DHT_DATA [0] + DHT_DATA [1] + DHT_DATA[2] + DHT_DATA[3] ;
	
	if(sum != DHT_DATA[4]){
		return 0;
	}else{
		return 1;
	}
	
}


void main (void)
{
	
	unsigned char state = 0;
	
	InitBoard();
	
	DHT = 1;
	delay_ms(1000);
	
	lcdInit();
	lcdsetCursor(1,0);
	lcdPuts("DHT11 Demo");
  delay_ms(2000);
  lcdClear();
  
	
	  while(1)
		{
					state = getData();
			
					
				  if(state){
						lcdClear();
						lcdsetCursor(1,0);
						lcdPuts("Temp: ");
						lcdPutc((DHT_DATA[2]/10) + 48);
						lcdPutc((DHT_DATA[2]%10) + 48);
						lcdPutc('.');
						lcdPutc((DHT_DATA[3]/10) + 48);
						lcdPuts(" C");
						lcdsetCursor(1,1);
						lcdPuts("RH  : ");
						lcdPutc((DHT_DATA[0]/10) + 48);
						lcdPutc((DHT_DATA[1]%10) + 48);
						lcdPutc('.');
						lcdPutc((DHT_DATA[2]/10) + 48);
						lcdPutc('%');
					}else{
						lcdClear();
						lcdsetCursor(0,1);
						lcdPuts("Checksum Error");
					}
					
									
					
					delay_ms(1000);

		}
}





