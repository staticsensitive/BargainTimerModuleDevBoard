#include "i2c.h"
#include "board.h"



void I2CInit (void)
{
	
}

void I2CStart (void)
{
    SCL_PIN = 0;        // Pull SCL low
    SDA_PIN = 1;        // Pull SDA High
    delay_us(1);
    SCL_PIN = 1;        //Pull SCL high
    delay_us(1);
    SDA_PIN = 0;        //Now Pull SDA LOW, to generate the Start Condition
    delay_us(1);
    SCL_PIN = 0;        //Finally Clear the SCL to complete the cycle
	
}
void I2CStop (void)
{
	  SCL_PIN = 0;            // Pull SCL low
    delay_us(1);
    SDA_PIN = 0;            // Pull SDA  low
    delay_us(1);
    SCL_PIN = 1;            // Pull SCL High
    delay_us(1);
    SDA_PIN = 1;            // Now Pull SDA High, to generate the Stop Condition
}

void I2CWrite (unsigned char dat)
{
	  unsigned char i;

    for(i=0;i<8;i++)                   // loop 8 times to send 1-byte of data
    {
        SDA_PIN = dat & 0x80;     // Send Bit by Bit on SDA line
        i2c_Clock();                   // Generate Clock at SCL
        dat = dat<<1;// Bring the next bit to be transmitted to MSB position
    }
                             
    i2c_Clock();
}

unsigned char I2CRead (unsigned char b)
{
	  unsigned char i, dat=0x00;

    SDA_PIN =1;               //Make SDA as I/P
	
    for(i=0;i<8;i++)     // loop 8times read 1-byte of data
    {
        delay_us(1);
        SCL_PIN = 1;         // Pull SCL High
        delay_us(1);

        dat = dat<<1;    //dat is Shifted each time and
        dat = dat | SDA_PIN; //ORed with the received bit to pack into byte

        SCL_PIN = 0;         // Clear SCL to complete the Clock
    }
		
    if(b==1)  /*Send the Ack/NoAck depending on the user option*/
    {
        i2c_Ack();
    }
    else
    {
        i2c_NoAck();
    }

    return dat;           // Finally return the received Byte*
}


static void i2c_Clock(void)
{
    delay_us(1);
    SCL_PIN = 1;            // Wait for Some time and Pull the SCL line High
    delay_us(1);        // Wait for Some time
    SCL_PIN = 0;            // Pull back the SCL line low to Generate a clock pulse
}

static void i2c_Ack(void)
{
    SDA_PIN = 0;        //Pull SDA low to indicate Positive ACK
    i2c_Clock();    //Generate the Clock
    SDA_PIN = 1;        // Pull SDA back to High(IDLE state)
}

static void i2c_NoAck(void)
{
    SDA_PIN = 1;         //Pull SDA high to indicate Negative/NO ACK
    i2c_Clock();     // Generate the Clock  
    SCL_PIN = 1;         // Set SCL 
}