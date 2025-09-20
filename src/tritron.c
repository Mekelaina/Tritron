#include <stdio.h>
#include <stdlib.h>
#include "tritlib/trit.h"
#include "tritlib/strtrit.h"


void bytePrintBinary(uint8_t num) {
    for (int i = sizeof(uint8_t) * 8 - 1; i >= 0; i--) {
        printf("%d", (num >> i) & 1);
    }
    printf("\n");
}
void shortPrintBinary(uint16_t num) {
    for (int i = sizeof(uint16_t) * 8 - 1; i >= 0; i--) {
        printf("%d", (num >> i) & 1);
    }
    printf("\n");
}
int main() {
    // uint8_t _T01 = 0b00110001; //0x31
    // uint8_t _10T = 0b00010011; //0x13
    // uint8_t _TTT = 0b00111111; //0x3f
    // uint8_t _00T = 0b00000011; //0x03
    // uint8_t _T00 = 0b00110000; //0x30
    // uint8_t _111 = 0b00010101; //0x15

    //1 0 3 3 0 0 
    //10TT00
    //0b0001001100110000

    Tryte_t t;
    t.tryte = 0b0001001100110000;

    // printf("%lld\n", TLONG_MAX);
    // printf("%lld\n", TLONG_MIN);
    
    // char test[] = "10TT00";
    // char bad[] = "1TT00";

    // int buff_size = 6;
    // char *buff; 
    // buff = (char *)malloc(sizeof(char)*(buff_size+1));
    // buff[buff_size+1] = '\0';
    // if(buff == NULL){
    //     printf("error\n");
    //     return 1;
    // }

    str2Tryte_27("R6", &t);
    shortPrintBinary(t.tryte);

    int buff_size = 2;
    char *buff; 
    buff = (char *)malloc(sizeof(char)*(buff_size+1));
    buff[buff_size] = '\0';
    if(buff == NULL){
        printf("error\n");
        return 1;
    }
    tryte2Str_27(&t, buff);
    printf(buff);
    printf("\n");
    
    free(buff);
    return 0;
}