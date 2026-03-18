#include "tm4c123gh6pm.h"
#include "printstr.h"
#include <string.h>

#define MAX_CHAR 100
// Sends a full string
void putsuart(char *ptr){
    while(*ptr != '\0'){
        while(UART0_FR_R & 0x20); // Wait while TX FIFO is full
        UART0_DR_R = *ptr;        // Send character
        ptr++;                    // Move to next char
    }
}

void parseData(char* ptr, int arraylen){
int i = 0;
int pointind = 0;
static char* pointarray[MAX_CHAR];
if (*ptr != ' ' && *ptr != '\0') {
        pointarray[pointind++] = ptr;
    }//We note the first word's address

    for(i = 0; i < arraylen; i++){
         if((* ptr) == ' ' ){
         *ptr = '\0';
         pointarray[pointind] = ptr + 1;
         pointind++;
          }
         ptr++;
    } // this replaces the spaces with \0 creating smaller arrays from the big array produced by the getsuart
    for(i = 0; i < pointind; i++) {
        if(strcmp(pointarray[i], "print") == 0) {
                while (i + 1 < pointind) {
                 putsuart(pointarray[i+1]);
                 i++;
                //Making sure there actually is a next word before printing it
                putsuart("\n\r");
            }
        }
    }
}

void UART0Check(){

    if(UART0_RSR_R & 0x1){
        putsuart("UART Overrun Error \n \r");
    }

   if((UART0_RSR_R >> 1)& 0x1){
        putsuart("UART Break Error \n \r");
    }

    if((UART0_RSR_R >> 2)& 0x1){
            putsuart("UART Parity Error \n \r");
        }

   if((UART0_RSR_R >> 3)& 0x1){
            putsuart("UART Framing Error \n \r");
        }
    if((UART0_RSR_R & 0x0F) == 0){
        putsuart("No UART Error \n \r");
    }
}

void getsuart(){
    static char array[MAX_CHAR];
    static int index = 0;

    if(!((UART0_FR_R >> 4)& 0x1)){ //this means that data is being received by the Board
        char input = (char)(UART0_DR_R & 0xFF);
        if(input != 0x0D){
            if(index < (MAX_CHAR -1)){

            array[index++] = input;
            UART0_DR_R = input;
           }
        }
        else{
                array[index] = '\0';
                putsuart(" \n \r");
                parseData(array, index);
                putsuart("\n \r");
                index = 0;
            }
    }

}


