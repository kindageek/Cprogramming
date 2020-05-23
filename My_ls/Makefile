# -*- MakeFile -*-

all: ls

ls: my_ls.o _ls.o ls_a.o ls_t.o functions.o strfunctions.o
	gcc my_ls.o _ls.o ls_a.o ls_t.o functions.o strfunctions.o -o ls

my_ls.o: my_ls.c ls.h
	gcc -c my_ls.c

_ls.o: _ls.c ls.h
	gcc -c _ls.c

ls_a.o: ls_a.c ls.h
	gcc -c ls_a.c

ls_t.o: ls_t.c ls.h
	gcc -c ls_t.c

functions.o: functions.c
	gcc -c functions.c

strfunctions.o: strfunctions.c
	gcc -c strfunctions.c

clean: 
	rm -f *.o ls