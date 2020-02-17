

all: q1 q2

all_test: q1test q2test

q1: q1.c hw4_function.c lib/generic_functions.c include/generic_functions.h
	gcc -I lib/ -I include/ -o q1 q1.c hw4_function.c -lm

q1test: q1.c test/test_functions.c test/test_functions.h
	gcc -D TEST -o q1test -I include/ -I lib/ -I test/ q1.c hw4_function.c test/test_functions.c -lm

q2: q2.c
	gcc -lm -o q2 q2.c

q2test: q2.c test/test_functions.c test/test_functions.h
	gcc -D TEST -o q2test -I test/ q2.c test/test_functions.c -lm

