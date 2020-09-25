#include "lcd.h"



void write2wire (unsigned char dat, bit b_rs, bit b_en )
{
	unsigned char i2cdat = dat << 4;
	
	if(b_rs){
		i2cdat |= RS;
	}
	
	if(b_en){
		i2cdat |= EN;
	}
	
	i2cdat |= BL;
	
	I2CStart();
	I2CWrite(ADDR);
	I2CWrite(i2cdat);
	I2CStop();
	
}

void sendNibs(int d, bit isDat){
	
	write2wire(d,isDat,1);
	delay_us(2);
	write2wire(d,isDat,0);
	delay_us(37);
}

void sendcmd(int d, bit isDat)
{
	sendNibs(((d >> 4) & 0x0F), isDat);
	sendNibs((d & 0x0F), isDat);
	delay_ms(5);
	
}

void lcdInit (void)
{
	write2wire(0x00,0,0);
	delay_ms(5);
	sendNibs(0x03,0); delay_ms(20);
	sendNibs(0x03,0); delay_ms(20);
	sendNibs(0x02,0); delay_ms(20);
	sendcmd(0x28,0);
	sendcmd(0x06,0);
	sendcmd(0x0C,0);
	sendcmd(0x01,0);
}

void lcdPutc (unsigned char c)
{
	sendcmd(c,1);
}

void lcdPuts (char *str)
{
	while(*str){
		lcdPutc(*str++);
	}
}

void lcdClear (void)
{
	sendcmd(0x01,0);
}

void lcdsetCursor (unsigned char col, unsigned char row)
{
  
  if(row == 0){
    sendcmd(0x7F+col,0);
  }
  if(row == 1){
     sendcmd(0xBF+col,0);
  }
}