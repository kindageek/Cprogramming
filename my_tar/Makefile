CC = gcc
CC_OPT = -g3 -fsanitize=leak -Wall -Wextra -Werror
OUTPUT = my_tar

all: ${OUTPUT}

${OUTPUT}: my_tar.o get_opt.o print_opt.o archive.o my.o args.o create.o append.o extract.o update.o print.o write.o header.o
	${CC} ${CC_OPT} my_tar.o get_opt.o print_opt.o archive.o my.o args.o create.o append.o extract.o update.o print.o write.o header.o -o ${OUTPUT}

my_tar.o: my_tar.c my_tar.h
	${CC} ${CC_OPT} -c my_tar.c
	
get_opt.o: get_opt.c my_tar.h
	${CC} ${CC_OPT} -c get_opt.c

print_opt.o: print_opt.c my_tar.h
	${CC} ${CC_OPT} -c print_opt.c

archive.o: archive.c my_tar.h
	${CC} ${CC_OPT} -c archive.c

my.o: my.c my_tar.h
	${CC} ${CC_OPT} -c my.c

args.o: args.c my_tar.h
	${CC} ${CC_OPT} -c args.c

create.o: create.c my_tar.h
	${CC} ${CC_OPT} -c create.c

extract.o: extract.c my_tar.h
	${CC} ${CC_OPT} -c extract.c

append.o: append.c my_tar.h
	${CC} ${CC_OPT} -c append.c

update.o: update.c my_tar.h
	${CC} ${CC_OPT} -c update.c

print.o: print.c my_tar.h
	${CC} ${CC_OPT} -c print.c

write.o: write.c my_tar.h
	${CC} ${CC_OPT} -c write.c

header.o: header.c my_tar.h
	${CC} ${CC_OPT} -c header.c

clean: 
	rm -f *.o ${OUTPUT} *.tar