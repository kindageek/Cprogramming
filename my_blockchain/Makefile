CC = gcc
CFLAGS = -g3 -fsanitize=leak -Wall -Wextra -Werror
OUTPUT = my_blockchain

all: ${OUTPUT}

${OUTPUT}: main.o my_functions.o my_readline.o block.o node.o blockchain.o command.o load.o save.o prompt.o string_list.o
	${CC} ${CFLAGS} main.o my_functions.o my_readline.o block.o node.o blockchain.o command.o load.o save.o prompt.o string_list.o -o ${OUTPUT}

main.o: main.c header.h
	${CC} ${CFLAGS} -c main.c

my_functions.o: my_functions.c header.h
	${CC} ${CFLAGS} -c my_functions.c

my_readline.o: my_readline.c header.h
	${CC} ${CFLAGS} -c my_readline.c

block.o: block.c header.h
	${CC} ${CFLAGS} -c block.c

node.o: node.c header.h
	${CC} ${CFLAGS} -c node.c

blockchain.o: blockchain.c header.h
	${CC} ${CFLAGS} -c blockchain.c

command.o: command.c header.h
	${CC} ${CFLAGS} -c command.c

load.o: load.c header.h
	${CC} ${CFLAGS} -c load.c

save.o: save.c header.h
	${CC} ${CFLAGS} -c save.c

prompt.o: prompt.c header.h
	${CC} ${CFLAGS} -c prompt.c

string_list.o: string_list.c header.h
	${CC} ${CFLAGS} -c string_list.c

clean: 
	rm -f *.o core* ${OUTPUT}