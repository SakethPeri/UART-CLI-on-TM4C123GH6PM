#include "tm4c123gh6pm.h"
#include "clock.h"
#include "gpio.h"
#include "wait.h"     // Make sure wait.h exists and has waitMicrosecond!
#include "printstr.h"

void initHw() {
    initSystemClockTo40Mhz();
    SYSCTL_RCGCUART_R |= 0x01;
    SYSCTL_RCGCGPIO_R |= 0x01;
    waitMicrosecond(1);

    GPIO_PORTA_DEN_R   |= 0x03;
    GPIO_PORTA_AFSEL_R |= 0x03;
    // Set PA0/PA1 to UART mode
    GPIO_PORTA_PCTL_R  = (GPIO_PORTA_PCTL_R & 0xFFFFFF00) | 0x00000011;

    UART0_CTL_R  = 0;
    UART0_IBRD_R = 21;    // 115200 baud
    UART0_FBRD_R = 45;
    UART0_LCRH_R = 0x60;  // 8-bit, no parity
    UART0_CTL_R  = 0x301; //enables Tx and Rx
}

int main(void) {
initHw();
while(1){
getsuart();
}
}
