#include "strtrit.h"
#include <string.h>
#include <stdio.h>

//maps (-13, 13) to coresponding string repersentation
//invalid number returns INVALID_TRIC_DIGIT
char int2Digit27(int x) {
    switch(x){
        case -13:
            return 'N';
            break;
        case -12:
            return 'O';
            break;
        case -11:
            return 'P';
            break;
        case -10:
            return 'Q';
            break;
        case -9:
            return 'R';
            break;
        case -8:
            return 'S';
            break;
        case -7:
            return 'T';
            break;
        case -6:
            return 'U';
            break;
        case -5:
            return 'V';
            break;
        case -4:
            return 'W';
            break;
        case -3:
            return 'X';
            break;
        case -2:
            return 'Y';
            break;
        case -1:
            return 'Z';
            break;
        case 0:
            return '0';
            break;
        case 1:
            return '1';
            break;
        case 2:
            return '2';
            break;
        case 3:
            return '3';
            break;
        case 4:
            return '4';
            break;
        case 5:
            return '5';
            break;
        case 6:
            return '6';
            break;
        case 7:
            return '7';
            break;
        case 8:
            return '8';
            break;
        case 9:
            return '9';
            break;
        case 10:
            return 'A';
            break;
        case 11:
            return 'B';
            break;
        case 12:
            return 'C';
            break;
        case 13:
            return 'D';
            break;
        default:
            return INVALID_TRIC_DIGIT;
            break;
    }
}

//maps (-1, 1) to string repersentation
//invalid number returns INVALID_TRIC_DIGIT
// char int2Digit3(int x){
//     switch (x) {
//         case -1
//     }
// }

//convert a base 3 string repersentation of a tryte
//into its usable form. Assumes S is at least size of TRYTE_STR_LEN
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
                break;
        }
    }
    packTryte(&u, __T);
}

//convert a tryte into its base 3 string repersentation
//assumes S is at least size of TRYTE_STR_LEN
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

    // char ht, lt;
    // int x = 0;
    // x += (u.t0 == TRIT_FALSE) ? -1 : u.t0;
    // x += ((u.t1 == TRIT_FALSE) ? -1 : u.t1)*3;
    // x += ((u.t2 == TRIT_FALSE) ? -1 : u.t2)*9;
    // lt = int2Digit27(x);
}

//convert a base 27 (tric) string repersentation of a tryte
//into its usable form. Assumes S is at least size of TRYTE_STR_LEN
//if S is invalid or too large, __T is set to 0 
void str2Tryte_27(char *S, Tryte_t *__T);

//convert a tryte into its base 27 string repersentation
//assumes S is at least size of TRYTE_STR_LEN
void tryte2Str_27(Tryte_t *T, char *__S);