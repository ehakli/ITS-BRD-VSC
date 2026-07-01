#ifndef SEARCH_H
#define SEARCH_H

#include <stdint.h>

#define SEARCH_ROM_COMMAND 0xF0

void reset_search(void);
uint8_t search(void);
unsigned char checkcrc8(unsigned char value);

#endif // SEARCH_H