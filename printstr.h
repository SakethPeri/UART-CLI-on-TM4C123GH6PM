#ifndef PRINTSTR_H_
#define PRINTSTR_H_

#include <stdint.h>

// Function Prototypes
void putsuart(char* ptr);
void UART0Check();
void getsuart();
void parseData(char* ptr, int arraylen);
#endif
