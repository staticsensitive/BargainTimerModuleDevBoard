#ifndef _LCD_H
#define _LCD_H

#include <STC8.H>
#include "i2c.h"
#include "board.h"

//base address 0x3F
#define ADDR 0x7E

#define RS 0x01
#define RW 0x02
#define EN 0x04
#define BL 0x08

void write2wire (unsigned char dat, bit b_rs, bit b_en );
void sendNibs(int d, bit isDat);
void sendcmd(int d, bit isDat);
void lcdInit (void);
void lcdPutc (unsigned char c);
void lcdPuts (char *str);
void lcdClear (void);
void lcdsetCursor (unsigned char col, unsigned char row);

#endif