#ifndef _I2C_H
#define _I2C_H

#include <STC8.H>

#define SCL_PIN  P26
#define SDA_PIN  P27


void I2CInit (void);
void I2CStart (void);
void I2CStop (void);
void I2CWrite (unsigned char b);
unsigned char I2CRead (unsigned char b);

static void I2CClock(void);
static void I2CACK(void);
static void I2CNACK(void);

#endif