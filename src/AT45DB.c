
//---------------------------------------------------------------------------//
//                                                                           //
//      Процедури за рабора с чип FLASH тип AT45DB161D от MSP430F149         //
//                                                                           //
//  V2.10   15.11.2008                                                       //
//---------------------------------------------------------------------------//

//#include "io430.h"
//#include "Intrinsics.H"
//
//#include "Global.H"
//#include "Archive.H"
//#include "FlashInterface.H"
//#include "IO.H"

#include "AT45DB.h"

unsigned short FlashPageSize;
unsigned short FlashMaxPage;


//static void wait_flash_rdy( void );
//static unsigned char flash_read_sector_lockdown( unsigned char* buff );

//static void flash_write_1page(long start_addr, int len, char *buff, char erase);

//===========================================================================//
void AT45DB_Init_Flash(void)
{
    MRES    = 0;
    DF_CS   = 1;
    WaitMs(1);
    MRES    = 1;
}
//===========================================================================//
// Gets Flash chip type and current configuration
void AT45DB_GetFlashType(void)
{
   unsigned char stat;

   stat = AT45DB_ReadStatusReg();
   switch (stat & 0x3D)
   {
   case 0x1C:                                 // AT45DB041D, 264 B page size
      FlashPageSize = 264;
      FlashMaxPage = 2047;
      break;
   case 0x1D:                                 // AT45DB041D, 256 B page size
      FlashPageSize = 256;
      FlashMaxPage = 2047;
      break;
   case 0x2C:                                 // AT45DB161D, 528 B page size
      FlashPageSize = 528;
      FlashMaxPage = 4095;
      break;
   case 0x25:                                 // AT45DB081D, 256 B page size
      FlashPageSize = 256;
      FlashMaxPage = 4095;
      break;
   case 0x24:                                 // AT45DB081D, 264 B page size
      FlashPageSize = 264;
      FlashMaxPage = 4095;
      break;
   case 0x34:
   case 0x35:                                 // AT45DB321D, 528 B page size
      FlashPageSize = 528;
      FlashMaxPage = 8191;
      break;
   default:
      FlashPageSize = 1;
   }
}

//===========================================================================//
// Wait for Flash chip to get ready
//static void wait_flash_rdy( void ) {
//  set_spi(2, 0);
//  spi_io(0xFF); spi_io(0xFF);
//  while ((AT45DB_ReadStatusReg() & BIT7) == 0) { __no_operation(); }
//}

//===========================================================================//
// чете Status Reg на Flash чипа
uint8_t AT45DB_ReadStatusReg( void ) 
{
//   char res;
//   set_spi(2, 0);
//   spi_io(0xFF); spi_io(0xFF);
//   select_flash();                            // CS > Low ( active )
//   spi_io(0x57);                              // 'read_status_reg' cmd
//   res = spi_io(0xFF);
//   deselect_flash();                          // CS > High ( inactive )
//   return res;
   
   uint8_t u8ResultL;
   
   select_flash();
   u8ResultL = SPI_TX( 0xd7 );
   u8ResultL = SPI_TX( 0x00 );
   deselect_flash();
   
   return u8ResultL;
}
//===========================================================================//
void select_flash(void)
{
    DF_CS   = 0;
}
//===========================================================================//
void deselect_flash(void)
{
    DF_CS   = 1;
}
//===========================================================================//
// чете Sector LockDown Registers ( замо за AT45DBxxxD )
/*
static unsigned char flash_read_sector_lockdown( unsigned char* buff ) {
  int i;
  // wait for the chip to get ready
  wait_flash_rdy();

  select_flash();
  spi_io(0x35);
  spi_io(0xFF);
  spi_io(0xFF);
  spi_io(0xFF);
  for (i=0; i<16; i++) {
    *buff = spi_io(0xFF);
    buff++;
  }
  return 0;
} */
//
////===========================================================================//
//// Erase Flash Page ( FlashPageSize bytes )
//// Input Parameter : addr is an address of the byte in page,
////   it's not the page index
//void flash_erase_page( unsigned long addr ) {
//  // wait for the chip to get ready
//  wait_flash_rdy();
//  // perform operation
//  select_flash();                      // CS > Low ( active )
//  spi_io(0x81);                        // page erase command
//  flash_put_addr( addr );
//  deselect_flash();                    // CS > High ( inactive )
//}
//
////---------------------------------------------------------------------------//
//// конвертира линеен адрес в адрес Page_address и Byte_address.
//// така полученият адрес се изпраща към чипа. очаква CS=0
//void flash_put_addr(long addr) {
//   long pg_addr, byte_addr;
//
//   pg_addr = addr / FlashPageSize;
//   byte_addr = addr % FlashPageSize;
//   if (FlashPageSize == 256)
//   {
//      spi_io(pg_addr >> 8);
//      spi_io(pg_addr);
//      spi_io(byte_addr);
//   }
//   else if (FlashPageSize == 264)
//   {
//      spi_io(pg_addr >> 7);
//      spi_io((pg_addr << 1) | ((byte_addr >> 8) & 0x01));
//      spi_io(byte_addr);
//   }
//   else  // 528 bytes page size
//   {
//      spi_io((pg_addr >> 6) & 0x3F);
//      spi_io((pg_addr << 2) | ((byte_addr >> 8) & 0x03));
//      spi_io(byte_addr);
//   }
//}
//
////---------------------------------------------------------------------------//
//// чете в RAM на процесора отпределена област от Flash
//void flash_read(long start_addr, int len, char *buff) {
//   int i;
//   // чака чипа да се освободи
//   wait_flash_rdy();
//
//   select_flash();                            // CS > Low ( active )
//   spi_io(0x68);                              // 'continuous_array_read' cmd
//   flash_put_addr(start_addr);
//   spi_io(0xFF);
//   spi_io(0xFF);
//   spi_io(0xFF);
//   spi_io(0xFF);
//   for (i=0; i<len; i++) {
//      *buff = spi_io(0xFF);
//      buff++;
//   }
//   deselect_flash();                          // CS > High ( inactive )
//}
//
////---------------------------------------------------------------------------//
//// записва от RAM на процесора в отпределена област от Flash
//void flash_write(long start_addr, int len, char *buff, char erase) {
//   int nbytes;
//   while(len) {
//      // определя колко байта ще се направят на този пас
//      nbytes = FlashPageSize - (start_addr % FlashPageSize);
//      if (nbytes > len) nbytes = len;
//      flash_write_1page(start_addr, nbytes, buff, erase);
//      start_addr += (long)(nbytes);
//      len -= nbytes;
//      buff += nbytes;
//   } // while(len)
//}    // procedure
//
////---------------------------------------------------------------------------//
//// записва от RAM на процесора в отпределена област от Flash.
//// изисква да няма прехвърляне на страница
//void flash_write_1page(long start_addr, int len, char *buff, char erase) {
//   int i;
//   if (len == 0) return;
//   // чака чипа да се освободи
//   wait_flash_rdy();
//   // копира страницата в буфер #1
//   select_flash();                            // CS > Low ( active )
//   spi_io(0x53);                              // copy page to buff_1 cmd
//   flash_put_addr(start_addr);
//   deselect_flash();                          // CS > High ( inactive )
//   // променя данните в буфер #1
//   wait_flash_rdy();
//   select_flash();                            // CS > Low ( active )
//   spi_io(0x84);                              // write to buff_1 cmd
//   flash_put_addr(start_addr);
//   for (i=0; i<len; i++) {
//      spi_io(*buff);
//      buff++;
//   }
//   deselect_flash();                          // CS > High ( inactive )
//   // записва данните от буфер #1 в страница  ( eventualy with Erase )
//   wait_flash_rdy();
//   select_flash();                            // CS > Low ( active )
//   if (erase)
//     spi_io(0x83);                            // write_&_erase buff_1 to page
//   else
//     spi_io(0x88);                            // write w/o erase
//   flash_put_addr(start_addr);
//   deselect_flash();                          // CS > High ( inactive )
//}

// --- end ---

