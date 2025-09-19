#ifndef TRITRON_STRTRIT
#define TRITRON_STRTRIT

#include "trit.h"

//size needed to repersent one tryte as a
//string in balanced ternary repersentation
#define TRYTE_STR_LEN_3 6
#define TRYTE_STR_lEN_27 2

#define INVALID_TRIC_DIGIT '@'
#define TERNERY_DIGIT_1 '1'
#define TERNERY_DIGIT_0 '0'
#define TERNERY_DIGIT_T 'T'

//convert a base 3 string repersentation of a tryte
//into its usable form. Assumes S is at least size of TRYTE_STR_LEN
void str2Tryte_3(char *S, Tryte_t *__T);

//convert a tryte into its base 3 string repersentation
//assumes S is at least size of TRYTE_STR_LEN
void tryte2Str_3(Tryte_t *T, char *__S);

//convert a base 27 (tric) string repersentation of a tryte
//into its usable form. Assumes S is at least size of TRYTE_STR_LEN
//if S is invalid or too large, __T is set to 0 
void str2Tryte_27(char *S, Tryte_t *__T);

//convert a tryte into its base 27 string repersentation
//assumes S is at least size of TRYTE_STR_LEN
void tryte2Str_27(Tryte_t *T, char *__S);

#endif