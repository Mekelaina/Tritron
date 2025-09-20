#! /usr/bin/bash

#gcc src/tritron.c src/trit.c src/trit.h -o tritron -Wall -Wextra --verbose --pedantic
#gcc src/tritron.c src/trit.c src/trit.h -o tritron -Wall -Wextra 
gcc src/tritlib/*.c src/tritlib/*.h src/*.c -o tritron -Wall -Wextra -lm