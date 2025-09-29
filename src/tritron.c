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
void intPrintBinary(uint32_t num) {
    for (int i = sizeof(uint32_t) * 8 - 1; i >= 0; i--) {
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

    
    //00010011001100000011000100010011
    //a.tryte_L.tryte = 0b0011000100010011; //T0110T
    //a.tryte_H.tryte = 0b0001001100110000; //10TT00
  
    Tryte_t a; 
    UnpackedTryte_t b;
    // a.tryte = 0b0001001100110000;
    // unpackTryte(&a, &b);
    // for(int i = 0; i < TRYTE_TRIT_SIZE; i++){
    //     printf("%d", b.trits[i]);
    // }
    // printf("\n");
    // shortPrintBinary(a.tryte);
    b.t5 = 1;
    b.t4 = 0;
    b.t3 = 3;
    b.t2 = 3;
    b.t1 = 0;
    b.t0 = 0;

    
    return 0;
}