

#include <xc.h>
//#include <PIC24FJ256GB108.h>

#include "CONFIG.h"
#include "DataTypes.h"

#include <stdio.h>
#include <uart.h>
#include "timer.h"

#include "UART.h"
#include "GPIOx.h"
#include "SPI.h"
#include "Time.h"
#include "AT45DB.h"
//volatile char cReceiveGPS = 0;

unsigned int state = 0;
unsigned char temp1;
// =============================

// =============================
int main(void)
{
    uint8 u8SpiResultL = 0;
    //Disable Watch Dog Timer
    RCONbits.SWDTEN	 = 0;

    //Set up I/O Port
    AD1PCFGL	 =	0xFFFF;             //set to all digital I/O
//    TRISB        =	0xF3FF;             //configure all PortB as input

    LedInit();
    
    UARTsInit();
    UART3PutChar(0x55);
    SPI_Iinit();
    TimerInit();
    AT45DB_GetFlashType();
    
    while(1)
    {
        WaitMs(100);
        u8SpiResultL = AT45DB_ReadStatusReg();
        if(0 != u8SpiResultL)
        {     
            PORTFbits.RF1 = ~PORTFbits.RF1;
        }
        UART3PutChar(u8SpiResultL);
    }

    return(0);
}