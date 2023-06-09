# La variable CC indica el ejecutable para el compilador C (usualmente son gcc o clang)
CC=gcc
# La variable CFLAGS indica las banderas para el compilador C
CFLAGS=-Wall -Wextra -std=gnu99 -ggdb
# La variable LDLIBS indica las banderas para la parte del "loader", usualmente librerías "-lxxxx"
LDLIBS=

# Este sería el ejecutable, sus dependencias son los .o
anagramas-hash:   anagramas-hash-func.o anagramas-hash.o fgetword-normalizada.o hash.o wrappers.o

# Acá van los .o, make sabe que cada .o depende del .c correspondiente, acá se agrega la dependencia al .h
# proj.o: proj.h
anagramas-hash.o: anagramas-hash.h
wrappers.o: wrappers.h
