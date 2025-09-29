#ifndef TRITRON_TRIT
#define TRITRON_TRIT

#include <stdint.h>
#include "trit128.h"

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

//array of bit masks for each trit, depending on the value
extern uint16_t TRIT_MASKS_IN_TRYTE[];

/* =========== Trit primitive constants =========== */

//Maximum base 10 value repersented in one tribble
extern const int8_t  TRIBBLE_MAX;
//Minimum base 10 value repersented in one tribble
extern const int8_t  TRIBBLE_MIN;
//Number of trits in a tribble
#define TRIBBLE_TRIT_SIZE 3
//Number of bytes a tribble takes up
#define TRIBBLE_BYTE_SIZE 1

//Maximum base 10 value repersented in one tryte (2x tribble)
extern const int16_t TRYTE_MAX;
//Minimum base 10 value repersented in one tryte (2x tribble)
extern const int16_t TRYTE_MIN;
//Number of Trits in a Tryte
#define TRYTE_TRIT_SIZE 6
//Number of bytes a Tryte takes up
#define TRYTE_BYTE_SIZE 2

//Maximum base 10 value represented in one tshort (2x trytes)
extern const int32_t TSHORT_MAX;
//Minimum base 10 value represented in one tshort (2x trytes)
extern const int32_t TSHORT_MIN;
//Number of trits in a tshort
#define TSHORT_TRIT_SIZE 12
//Number of bytes a tshort takes up
#define TSHORT_BYTE_SIZE 4

//Maximum base 10 value represented in one tint (4x trytes)
extern const int64_t TINT_MAX;
//Minimum base 10 value represented in one tint (4x trytes)
extern const int64_t TINT_MIN;
//Number of trits in a tint
#define TINT_TRIT_SIZE 24
//Number of bytes a tint takes up
#define TINT_BYTE_SIZE 8

//Maximum base 10 value repersented in one tlong (8x trytes)
extern const int128_t TLONG_MAX;
//Minimum base 10 value repersented in one tlong (8x trytes)
extern const int128_t TLONG_MIN;
//Number of trits in a tlong
#define TLONG_TRIT_SIZE 48
//Number of bytes a tlong takes up
#define TLONG_BYTE_SIZE 16



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

typedef union {
    uint32_t tshort;
    struct {
        Tryte_t tryte_L;
        Tryte_t tryte_H;
    };
} Tshort_t;

typedef union {
    uint64_t tint;
    struct {
        Tshort_t tshort_L;
        Tshort_t tshort_H;
    };
} Tint_t;

typedef union {
    int128_t tlong;
    struct {
        Tint_t tint_L;
        Tint_t tint_H;
    };
} Tlong_t;


//TODO: refactor unpacked types to store MST-LST
//TODO: refactor names of Trytes in larger types

//An alternate tryte repersentation where each Trit is stored
//as an individual element in an array
//its a union to allow iteration or direct element access
typedef union  {
    Trit_t trits[TRYTE_TRIT_SIZE];
    struct {
        Trit_t t0, t1, t2, t3, t4, t5;
    };

} UnpackedTryte_t ;

typedef union {
    Trit_t trits[TSHORT_TRIT_SIZE];
    struct {
        UnpackedTryte_t tryte_H;
        UnpackedTryte_t tryte_L;
    };
} UnpackedTshort_t;

typedef union  {
    Trit_t trits[TINT_TRIT_SIZE];
    struct {
        UnpackedTryte_t a_L;
        UnpackedTryte_t a_H;
        UnpackedTryte_t b_L;
        UnpackedTryte_t b_H;
    };
} UnpackedTint_t;


typedef union {
    Trit_t trits[TLONG_TRIT_SIZE];
    struct {
        UnpackedTryte_t a_L;
        UnpackedTryte_t a_H;
        UnpackedTryte_t b_L;
        UnpackedTryte_t b_H;
        UnpackedTryte_t c_L;
        UnpackedTryte_t c_H;
        UnpackedTryte_t d_L;
        UnpackedTryte_t d_H;
    };
} UnpackedTlong_t;

// ========= Trit Functions ==========

// returns the value of trit t (0-5) from tryte T
//if t > 5 or t < 0, returns unknown
Trit_t getTritInTryte(Tryte_t *T, uint8_t index);

//sets index'th trit in tryte T (if index is 0-5. else does nothing) 
void setTritInTryte(Tryte_t *_T, Trit_t t, uint8_t index);

// ========= Tryte Functions ==========

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



// ========= Tshort Functions ==========
void unpackTshort(Tshort_t *T, UnpackedTshort_t *__U);
void packTshort(UnpackedTshort_t *U, Tshort_t *__T);

// ========= Tint Functions ==========
void unpackTint(Tint_t *T, UnpackedTint_t *__U);
void packTint(UnpackedTint_t *U, Tint_t *__T);

// ========= Tlong Functions ==========
void unpackTlong(Tlong_t *T, UnpackedTlong_t *__U);
void packTlong(UnpackedTlong_t *U, Tlong_t *__T);


#endif


