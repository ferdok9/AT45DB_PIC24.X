
#ifndef GPS_UTILIES_H
#define	GPS_UTILIES_H

unsigned char get_ascii_hex(char* p);
unsigned char get_ascii(char* p);
unsigned char hex_to_ascii(unsigned char ch);
unsigned char get_2ascii(char* p);
unsigned int get_3ascii(char* p);
unsigned int get_2ascii_byte(char* p);
void byte_to_2dec_ascii(char* buff, unsigned char byte);



#endif	/* GPS_UTILIES_H */

