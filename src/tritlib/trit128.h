#ifndef TRITRON_TRIT128
#define TRITRON_TRIT128

#include <stdint.h>
//TODO: Define datatype and interface here for 128bit numbers

typedef struct uint128 {
    uint64_t h, l;
} uint128_t;


typedef struct int128 {
    int64_t h, l;
} int128_t;





#endif