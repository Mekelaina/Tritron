#include "strtrit.h"
#include <string.h>
#include <stdio.h>

//maps (-13, 13) to coresponding string repersentation
//invalid number returns INVALID_TRIC_DIGIT
//felt cleaner to seperate this from the rest of str2Tryte_27
char int2Digit27(int x) {
    switch(x){
        case -13:
            return 'N';
        case -12:
            return 'O';
        case -11:
            return 'P';
        case -10:
            return 'Q';
        case -9:
            return 'R';
        case -8:
            return 'S';
        case -7:
            return 'T';
        case -6:
            return 'U';
        case -5:
            return 'V';
        case -4:
            return 'W';
        case -3:
            return 'X';
        case -2:
            return 'Y';
        case -1:
            return 'Z';
        case 0:
            return '0';
        case 1:
            return '1';
        case 2:
            return '2';
        case 3:
            return '3';
        case 4:
            return '4';
        case 5:
            return '5';
        case 6:
            return '6';
        case 7:
            return '7';
        case 8:
            return '8';
        case 9:
            return '9';
        case 10:
            return 'A';
        case 11:
            return 'B';
        case 12:
            return 'C';
        case 13:
            return 'D';
        default:
            return INVALID_TRIC_DIGIT;
    }
}

//maps tric digits to their coresponding tribble binary repersentation
//an invalid diget retruns 0
char digit2Bin27(char x){
        switch(x){
        case 'N':
            return 0b00111111; // TTT
        case 'O':
            return 0b00111100; // TT0
        case 'P':
            return 0b00111101; // TT1
        case 'Q':
            return 0b00110011; // T0T
        case 'R':
            return 0b00110000; // T00
        case 'S':
            return 0b00110001; // T01
        case 'T':
            return 0b00110111; // T1T
        case 'U':
            return 0b00110100; // T10
        case 'V':
            return 0b00110101; // T11
        case 'W':
            return 0b00001111; // 0TT
        case 'X':
            return 0b00001100; // 0T0
        case 'Y':
            return 0b00001101; // 0T1
        case 'Z':
            return 0b00000011; // 00T
        case '0':
            return 0b00000000; // 000
        case '1':
            return 0b00000001; // 001
        case '2':
            return 0b00000111; // 01T
        case '3':
            return 0b00000100; // 010
        case '4':
            return 0b00000101; // 011
        case '5':
            return 0b00011111; // 1TT
        case '6':
            return 0b00011100; // 1T0
        case '7':
            return 0b00011101; // 1T1
        case '8':
            return 0b00010011; // 10T
        case '9':
            return 0b00010000; // 100
        case 'A':
            return 0b00010001; // 101
        case 'B':
            return 0b00010111; // 11T
        case 'C':
            return 0b00010100; // 110
        case 'D':
            return 0b00010101; // 111
        default:
            return 0b00000000; // 000
    }
}

/*
    TODO: Make string code scale for multiple trytes
*/


//convert a base 3 string repersentation of a tryte
//into its usable form. Assumes S is at least size of TRYTE_STR_LEN_3 + '\0'
//if S is invalid or too small, __T is set to 0 
void str2Tryte_3(char *S, Tryte_t *__T) {
    __T->tryte = 0;
    UnpackedTryte_t u;
    for(int i = 0; i < TRYTE_STR_LEN_3; i++){
        //printf("%d\n", S[i]);
        switch(S[i]){
            case 'T':
                u.trits[(TRYTE_STR_LEN_3-1)-i] = TRIT_FALSE;
                break;
                
            case '0':
                u.trits[(TRYTE_STR_LEN_3-1)-i] = TRIT_UNKNOWN;
                break;
            case '1':
                u.trits[(TRYTE_STR_LEN_3-1)-i] = TRIT_TRUE;
                break;
            default:
                __T->tryte = 0;
                return;
                
        }
    }
    packTryte(&u, __T);
}

//convert a tryte into its base 3 string repersentation
//assumes S is at least size of TRYTE_STR_LEN_3 + '\0'
void tryte2Str_3(Tryte_t *T, char *__S) {
    UnpackedTryte_t u;
    unpackTryte(T, &u);

    for(int i = 0; i < TRYTE_STR_LEN_3; i++){
        //printf("%d\n", i);
        //printf("a\n");
        Trit_t x = u.trits[i];
        switch(x){
            case TRIT_FALSE:
                __S[(TRYTE_STR_LEN_3-1)-i] = TERNERY_DIGIT_T;
                break;
            case TRIT_UNKNOWN:
                __S[(TRYTE_STR_LEN_3-1)-i] = TERNERY_DIGIT_0;
                break;
            case TRIT_TRUE:
                __S[(TRYTE_STR_LEN_3-1)-i] = TERNERY_DIGIT_1;
                break;
        }
    }
}

//convert a base 27 (tric) string repersentation of a tryte
//into its usable form. Assumes S is at least size of TRYTE_STR_LEN_27 + '\0'
//if S is invalid or too large, __T is set to 0 
void str2Tryte_27(char *S, Tryte_t *__T) {
    //UnpackedTryte_t u;
    char x;
    x = S[0];
    __T->tribble_H = digit2Bin27(x);

    x = S[1];
    __T->tribble_L = digit2Bin27(x);

};

//convert a tryte into its base 27 string repersentation
//assumes S is at least size of TRYTE_STR_LEN_27 + '\0'
void tryte2Str_27(Tryte_t *T, char *__S){
    UnpackedTryte_t u;
    unpackTryte(T, &u);

    char ht, lt;
    int x = 0;
    x += (u.t0 == TRIT_FALSE) ? -1 : u.t0;
    x += ((u.t1 == TRIT_FALSE) ? -1 : u.t1)*3;
    x += ((u.t2 == TRIT_FALSE) ? -1 : u.t2)*9;
    lt = int2Digit27(x);
    
    x = 0;
    x += (u.t3 == TRIT_FALSE) ? -1 : u.t3;
    x += ((u.t4 == TRIT_FALSE) ? -1 : u.t4)*3;
    x += ((u.t5 == TRIT_FALSE) ? -1 : u.t5)*9;
    ht = int2Digit27(x);

    __S[0] = ht;
    __S[1] = lt;
}