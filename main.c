#include "tm4c123gh6pm.h"
#include "clock.h"
#include "gpio.h"

void initHw(){
    initSystemClockTo40Mhz();
    SYSCTL_RCGCUART_R |= SYSCTL_RCGC1_UART0; //enable the UART Module 0
    SYSCTL_RCGCGPIO_R |= 0x01; //Enable port A which consists the said pins of the UART module
    GPIO_PORTA_DEN_R |= 0x03;
    GPIO_PORTA_AFSEL_R |= 0x03; //enabled the AFSEL Function in Port A
    GPIO_PORTA_PCTL_R |= GPIO_PCTL_PA0_U0RX;
    GPIO_PORTA_PCTL_R |= GPIO_PCTL_PA1_U0TX;
    UART0_CTL_R |= 0x00000000;
    UART0_IBRD_R |= 0x104;
    UART0_FBRD_R |= 0x1B;
    UART0_LCRH_R |= 0x00000060;
    UART0_CTL_R |= 0x00000001;
}

void uartprint(){

    UART0_DR_R = 'C';

}

int main(void)
{
initHw();

}
