#include "tm4c123gh6pm.h"
#include "clock.h"
#include "gpio.h"

#define MAX_CHAR 100


void initHw(){
    initSystemClockTo40Mhz();
    SYSCTL_RCGCUART_R |= 0x01;
    SYSCTL_RCGCGPIO_R |= 0x01;
    waitMicrosecond(1);

    GPIO_PORTA_DEN_R   |= 0x03;
    GPIO_PORTA_AFSEL_R |= 0x03;
    GPIO_PORTA_PCTL_R  |= 0x11; // PA0=U0RX, PA1=U0TX

    UART0_CTL_R  = 0;
    UART0_IBRD_R = 21;         // Set to 21 for 115200
    UART0_FBRD_R = 45;         // Set to 45 for 115200
    UART0_LCRH_R = 0x60;       // 8-bit, no parity (FIFO off for now to test)
    UART0_CTL_R  = 0x301;
}

void putsuart(char *ptr){
    if(sizeof(array) > MAX_CHAR){
        return; // Exit function if string is too long
    }

    while(*ptr != '\0'){
        while(UART0_FR_R & 0x20); // Wait while TX FIFO is full
        UART0_DR_R = *ptr;        // Send character
        ptr++;                    // Move to next char
    }
}

int main(void)
{
    initHw();
    //putsuart(array);
    //This will be the syntax for putsuart().
    while(1);
}
