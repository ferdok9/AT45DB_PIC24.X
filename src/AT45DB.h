
#ifndef AT45DB_H
#define	AT45DB_H

#include <stdint.h>
#include "Time.h"
#include "SPI.h"

extern void AT45DB_Init_Flash(void);
extern void AT45DB_GetFlashType(void);
extern uint8_t AT45DB_ReadStatusReg( void );
void select_flash(void);
void deselect_flash(void);

#endif	/* AT45DB_H */

