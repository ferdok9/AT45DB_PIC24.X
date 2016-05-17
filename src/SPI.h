
#ifndef SPI_H
#define	SPI_H
#include <xc.h>
#include "DataTypes.h"

#define     DF_CS_Dir    TRISFbits.TRISF4        //DF_CS
#define     MRES_Dir     TRISDbits.TRISD14       //MRES
    
#define     DF_CS        LATFbits.LATF4          //
#define     MRES         LATDbits.LATD14         //


#define     KLEN_PWR_Dir    TRISFbits.TRISF3     //DF_CS
#define     KLEN_CS_Dir     TRISDbits.TRISD5     //

#define     KLEN_PWR	 PORTFbits.RF3           //         
#define     KLEN_CS		 TRISDbits.TRISD5        //
       

extern void SPI_Iinit(void);
extern uint8 SPI_TX(uint8 u8TxBiteP);
extern void SPI_RX(uint8 u8RxBiteP);

#endif	/* SPI_H */

