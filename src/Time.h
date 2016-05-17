
#ifndef TIME_H
#define	TIME_H

#include <xc.h>
#include "DataTypes.h"
#include "timer.h"

extern volatile uint8 u8TimerFlag;

extern void TimerInit(void);
extern void WaitMs(uint16 u16MsP);

#endif	/* TIME_H */