CC = gcc
CC_OPT = -g3 -fsanitize=address #-Wall -Wextra -Werror
OUTPUT = my_tar

all: ${OUTPUT}

${OUTPUT}: my_tar.o get_opt.o print_opt.o my.o args.o
	${CC} ${CC_OPT} my_tar.o get_opt.o print_opt.o my.o args.o -o ${OUTPUT}

my_tar.o: my_tar.c my_tar.h
	${CC} ${CC_OPT} -c my_tar.c
	
get_opt.o: get_opt.c my_tar.h
	${CC} ${CC_OPT} -c get_opt.c

print_opt.o: print_opt.c my_tar.h
	${CC} ${CC_OPT} -c print_opt.c

my.o: my.c
	${CC} ${CC_OPT} -c my.c

args.o: args.c my_tar.h
	${CC} ${CC_OPT} -c args.c

clean: 
	rm -f *.o ${OUTPUT}