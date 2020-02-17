

q1: q1.c
	gcc -lm -o q1 q1.c

q1test: q1.c test/test_functions.c test/test_functions.h
	gcc -D TEST -o q1test -I test/ q1.c test/test_functions.c -lm

q2: q2.c
	gcc -lm -o q2 q2.c

q2test: q2.c test/test_functions.c test/test_functions.h
	gcc -D TEST -o q2test -I test/ q2.c test/test_functions.c -lm

