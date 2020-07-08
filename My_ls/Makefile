# -*- MakeFile -*-
CC = gcc
CFLAGS = -g3 -fsanitize=leak -Wall -Wextra -Werror
OUTPUT = ls

all: ${OUTPUT}

ls: main.o my_ls.o _ls.o ls_a.o ls_t.o ls_r.o get_opt.o file_manipulation.o file_array.o string.o
	${CC} ${CFLAGS} main.o my_ls.o _ls.o ls_a.o ls_t.o ls_r.o get_opt.o file_manipulation.o file_array.o string.o -o ${OUTPUT}

main.o: main.c ls.h
	${CC} ${CFLAGS} -c main.c

my_ls.o: my_ls.c ls.h
	${CC} ${CFLAGS} -c my_ls.c

_ls.o: _ls.c ls.h
	${CC} ${CFLAGS} -c _ls.c

ls_a.o: ls_a.c ls.h
	${CC} ${CFLAGS} -c ls_a.c

ls_t.o: ls_t.c ls.h
	${CC} ${CFLAGS} -c ls_t.c

ls_r.o: ls_r.c ls.h
	${CC} ${CFLAGS} -c ls_r.c

get_opt.o: get_opt.c ls.h
	${CC} ${CFLAGS} -c get_opt.c

file_manipulation.o: file_manipulation.c ls.h
	${CC} ${CFLAGS} -c file_manipulation.c

file_array.o: file_array.c ls.h
	${CC} ${CFLAGS} -c file_array.c

string.o: string.c ls.h
	${CC} ${CFLAGS} -c string.c

clean: 
	rm -f *.o core* ${OUTPUT}