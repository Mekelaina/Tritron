#include "trit.h"
#include <stdio.h>
#include <stdbool.h>
#include <math.h>
#include <stdlib.h>


uint16_t TRIT_MASKS_IN_TRYTE[] = {
    //False
    0b0000000000000011, //L_LST
    0b0000000000001100,
    0b0000000000110000, //L_MST
    0b0000001100000000, //H_LST
    0b0000110000000000,
    0b0011000000000000, //H_MST
    //True
    0b0000000000000001, 
    0b0000000000000100,
    0b0000000000010000, 
    0b0000000100000000, 
    0b0000010000000000,
    0b0001000000000000
};

// ========= Packed Tryte ===========
Trit_t getTritInTryte(Tryte_t *T, uint8_t index) {
    Trit_t rtn = TRIT_UNKNOWN;

    if(index < 6){
        uint8_t buff = 0;

        switch(index){
            case 0:
                buff = (T->tribble_L & 0b00000011) >> 0;
                break; 
            case 1:
                buff = (T->tribble_L & 0b00001100) >> 2;
                break; 
            case 2:
                buff = (T->tribble_L & 0b00110000) >> 4;
                break; 
            case 3:
                buff = (T->tribble_H & 0b00000011) >> 0;
                break; 
            case 4:
                buff = (T->tribble_H & 0b00001100) >> 2;
                break; 
            case 5:
                buff = (T->tribble_H & 0b00110000) >> 4;
                break; 
        }
        rtn = buff;
    }
    
    return rtn;
}

void setTritInTryte(Tryte_t *T, Trit_t t, uint8_t index){
    if(index < 6){
        uint16_t temp = 0;
        temp = T->tryte;
    
        
        //printf("[%d, %d]", t, index);
        switch (t) {
            case TRIT_FALSE:
                //printf(" False\n");
                temp = temp | TRIT_MASKS_IN_TRYTE[index];
                break;
            case TRIT_UNKNOWN:
                //printf(" Unknown\n");
                temp &= ~(TRIT_MASKS_IN_TRYTE[index]);
                break;
            case TRIT_TRUE:
                //printf(" True\n");
                temp &= ~(TRIT_MASKS_IN_TRYTE[index]);
                temp = temp | TRIT_MASKS_IN_TRYTE[index+6];
                break;
        }
        
        T->tryte = temp;    
    }
}

// ========= Unpacked Tryte ==========
void unpackTryte(Tryte_t *T, UnpackedTryte_t *__U){
    for(int i = 0; i < 6; i++){
        __U->trits[i] = getTritInTryte(T, i);
    }
}

void packTryte(UnpackedTryte_t *U, Tryte_t *__T) {
    for(int i = 0; i < 6; i++){
        setTritInTryte(__T, U->trits[5-i], 5-i);
    }
}

int16_t tryte2Int(Tryte_t *T){
    int16_t sum = 0;
    UnpackedTryte_t u;

    unpackTryte(T, &u);
    for(int i = 5; i >= 0; i--){
        Trit_t x = u.trits[i];
        printf("[%d, %d]\n", i, x);
        if(x == TRIT_FALSE){
            sum += (int)(-1 * pow(3, i));
        } else {
            sum += (int)(x * pow(3, i));
        }
    }
    return sum;
}

void int2Tryte(Tryte_t *__T, int16_t val){
    if(val != 0){
        if(val > TRYTE_MIN-1 && val < TRYTE_MAX+1){
            bool neg = false;
            if(val < 0){
                neg = 1;
                val = abs(val);
            }

            UnpackedTryte_t temp;
            int buff[6] = {0};
            int bx = 0;
            while(val > 0){
                int rem = val % 3;
                val /= 3;
                if(rem == 2) {
                    rem = TRIT_FALSE;
                    val++;
                }
                //printf("[%d, %d]\n", val, rem);
                buff[bx++] = rem;
            }
            for(int i = 0; i < 6; i++){
                temp.trits[5-i] = buff[5-i];
            }

            packTryte(&temp, __T);
            
            if(neg){
                notTryte(__T);
            }
            return;
        }
    }
    __T->tryte = 0;
}

void notTryte(Tryte_t *__T){
    UnpackedTryte_t temp;
    unpackTryte(__T, &temp);
    for(int i = 0; i < 6; i++){
        Trit_t x = temp.trits[i];
        switch(x){
            case TRIT_TRUE:
                temp.trits[i] = TRIT_FALSE;
            case TRIT_UNKNOWN:
                break;
            case TRIT_FALSE:
                temp.trits[i] = TRIT_TRUE;
                break;
        }
    }
    packTryte(&temp, __T);
}


