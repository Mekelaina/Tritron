#ifndef TRITRON_TRIT
#define TRITRON_TRIT

#include <stdint.h>
#include <stdbool.h>

/*
    ========== Definitions ==========
    Trit - TRinary digIT, three state analogue of bit
        can be -1 (false), 0 (unknown), or 1(true)
    Tribble - collection of 3 Trits, three state analogue of Nibble
        27 possible values from -13 to +13 (incudes 0)
    Tryte - 2 tribbles / 6 Trits, three state analogue of Byte
        729 possible values from -364 to + 364 (incudes 0)

    a Trit is repersented as two bits where:
        11 = -1
        01 =  1
        00 =  0
        *10 is never used/is invalid 

        a Tribble is represented as a byte where:
        trit a, b, c
        *00  00 00 00
        bits 7,6 are unused. 5,4 are MST; 1,0 are LST

    Trytes are stored as union of uint16_t and 2x uint8_t (two tribbles)

    use api functions to get specific trit status or shift tryte to avoid
        accounting for unused top two bits of tribble byte

    Base 27 as a hex analogue
        positve: 0-9, 10 A, 11 B, 12 C, 13 D
        negative: -1 Z, -2 Y, X -3, W -4, V -5, U -6, 
            T -7, S -8, R -9, Q -10, P -11, O -12, N -13
        
        one Tribble can be repersented as one base 27 number listed above
        refering to this as "tricunal" or "tric" for this api

    =========== CODE CONVENTIONS ===========
    When writing numbers in base 3. T = -1
    named Tribble/Trite values are prefixed with a single underscore
        when written in base 3. ex T01100 > _T01100
    function arguments that are modified are prefixed with a double underscore 
        
*/
#define MASK_TRIT_0 0b00000011
#define MASK_TRIT_1 0b00001100
#define MASK_TRIT_2 0b00110000

#define SHIFT_TRIT_0 0
#define SHIFT_TRIT_1 2
#define SHIFT_TRIT_2 4

//Maximum base 10 value repersented in one Tryte
#define TRYTE_MAX  364
//Minimum base 10 value repersented in one Tryte
#define TRYTE_MIN -364



extern uint16_t TRIT_MASKS_IN_TRYTE[];
// uint16_t TRIT_MASKS_IN_TRYTE[] = {
//     //False/Unknown
//     0b0000000000000011, //L_LST
//     0b0000000000001100,
//     0b0000000000110000, //L_MST
//     0b0000001100000000, //H_LST
//     0b0000110000000000,
//     0b0011000000000000, //H_MST
//     //True
//     0b0000000000000001, 
//     0b0000000000000100,
//     0b0000000000010000, 
//     0b0000000100000000, 
//     0b0000010000000000,
//     0b0001000000000000
// };

//Trit states. one byte
typedef enum __attribute__((packed)) Trit {
    TRIT_FALSE   = 0b11,
    TRIT_UNKNOWN = 0b00,
    TRIT_TRUE    = 0b01
} Trit_t ;

//tryte repersentation. 2 bytes in size.
//both tribbles accessible as well
typedef union {
    uint16_t tryte;
    struct {
        uint8_t tribble_L;
        uint8_t tribble_H;
    };
} Tryte_t;

//An alternate tryte repersentation where each Trit is stored
//as an individual element in an array
//its a union to allow iteration or direct element access
typedef union unpacked_tryte {
    Trit_t trits[5];
    struct {
        Trit_t t0, t1, t2, t3, t4, t5;
    };

} UnpackedTryte_t ;

// returns the value of trit t (0-5) from tryte T
//if t > 5 or t < 0, returns unknown
Trit_t getTritInTryte(Tryte_t *T, uint8_t index);

//sets index'th trit in tryte T (if index is 0-5. else does nothing) 
void setTritInTryte(Tryte_t *_T, Trit_t t, uint8_t index);

//unpacks given tryte T into unpacked tryte U
void unpackTryte(Tryte_t *T, UnpackedTryte_t *__U);

//packs given unpacked tryte U into tryte T
void packTryte(UnpackedTryte_t *U, Tryte_t *__T);

//negates Trits in tryte, convirting between negative and positve val
//flipping trits if not zero
//T -> 1; 1 -> T; 0 -> 0
void notTryte(Tryte_t *__T);

//returns the base 10 integer value of tryte T
// as a signed 16bit int.
// will be between -364 to +364
int16_t tryte2Int(Tryte_t *T);

//returns a Tryte equal to val
//must be between -364 to +364
//if not, Tryte is unknown / 0
void int2Tryte(Tryte_t *__T, int16_t val);



//TODO shift left and right functions



#endif


