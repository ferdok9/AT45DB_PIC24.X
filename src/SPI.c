
#include "SPI.h"

//void SPI_Iinit(void);
//uint8 SPI_TX(uint8 u8TxBiteP);
//void SPI_RX(uint8 u8RxBiteP);


void SPI_Iinit(void)
{
    RPINR20bits.SDI1R = 29;     //MISO
    RPOR7bits.RP14R = 7;        //MOSI
    RPOR2bits.RP5R = 8;         //SCK
    
    DF_CS_Dir        = 0;       //DF_CS
    MRES_Dir         = 0;       //MRES
    
    DF_CS            = 1;
    MRES             = 1;
    
    IFS0bits.SPI1IF = 0;
    IEC0bits.SPI1IE = 0;
    IPC2bits.SPI1IP = 5;
            
//  FCY = 16 MHz  /  1:1 * 3:1 = 4 MHz
    SPI1CON1bits.PPRE   = 0x3;    //00 = Primary prescale 1:1
    SPI1CON1bits.SPRE   = 0x4;    //000 = Secondary prescale 3:1 
    
    SPI1CON1bits.CKE    = 0;    //Clock Edge Select bit(3) 
                                //0 = Serial output data changes on transition 
                                //from Idle clock state to active clock state 
                                //1 = Serial output data changes on transition  
                                //from active clock state to Idle clock state
    
    SPI1CON1bits.CKP    = 1;    //Clock Polarity Select bit
                                //0 = Idle state for clock is a low level; 
                                //    active state is a high level
                                //1 = Idle state for clock is a high level; 
                                //    active state is a low level
    
    SPI1CON1bits.SMP    = 1;    //1 = Input data sampled at end of data output time
                                //0 = Input data sampled at middle of data output time
    
    SPI1CON1bits.DISSCK = 0;    //0 = Internal SPI clock is enabled
    SPI1CON1bits.DISSDO = 0;    //0 = SDOx pin is controlled by the module
            
//SPI1CON2   
       
//SPI1STAT
    SPI1STATbits.SISEL = 1;     //Interrupt when data is available in receive buffer (SRMPT bit is set)
    
    SPI1CON1bits.MSTEN = 1;     //Master Mode Enable bit
    SPI1STATbits.SPIROV = 0;    //Receive Overflow Flag bit
    SPI1STATbits.SPIEN = 1;        
}

//config1 = ENABLE_SCK_PIN | ENABLE_SDO_PIN | SPI_MODE8_ON/SPI_MODE16_OFF
//        | SPI_SMP_OFF	   | SPI_CKE_OFF    | SLAVE_ENABLE_OFF | CLK_POL_ACTIVE_HIGH	
//        | MASTER_ENABLE_ON | SEC_PRESCAL_8_1 | PRI_PRESCAL_64_1
//config2 = 
//config3 = SPI_ENABLE	
//OpenSPI1(unsigned int config1,unsigned int config2, unsigned int config3)
//                                    


uint8 SPI_TX(uint8 u8TxBiteP)
{
    uint8 u8TempL = 0;
    u8TempL = SPI1BUF;
    
    SPI1BUF = u8TxBiteP;    
    while(0 == SPI1STATbits.SPIRBF);
    
    return SPI1BUF;
}


