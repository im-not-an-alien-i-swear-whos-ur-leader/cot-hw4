DB=
# debug flag

q1_c_files=q1.c src/bisection.c hw4_function.c helper_functions.c lib/generic_functions.c
q1_h_files=include/generic_functions.h helper_functions.h include/bisection.h

q2_c_files=q2.c src/fixed_iteration.c hw4_function.c helper_functions.c lib/generic_functions.c src/bisection.c
q2_h_files=include/generic_functions.h helper_functions.h include/fixed_iteration.h include/bisection.h

all: q1 q2

all_test: q1test q2test

q1: $(q1_c_files) $(q1_h_files)
	gcc $(DB) -I lib/ -I include/ -I ./ -o q1 $(q1_c_files) -lm

q1test: test/test_functions.c test/test_functions.h $(q1_c_files) $(q1_h_files)
	gcc $(DB) -D TEST -o q1test -I include/ -I lib/ -I test/ -I ./ $(q1_c_files) -lm


q2: $(q2_c_files) $(q2_h_files)
	gcc $(DB) -I lib/ -I include/ -I ./ -o q2 $(q2_c_files) -lm

q2test: test/test_functions.c test/test_functions.h $(q2_c_files) $(q2_h_files)
	gcc $(DB) -D TEST -o q1test -I include/ -I lib/ -I test/ -I ./ $(q2_c_files) -lm

