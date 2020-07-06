CC = gcc
CC_FLAGS = -g3 #-fsanitize=leak #-Wall -Wextra -Werror
OUTPUT = my_readline

all: ${OUTPUT}

${OUTPUT}: my_readline.o
	${CC} ${CC_FLAGS} my_readline.o -o ${OUTPUT}

my_readline.o: my_readline.c
	${CC} ${CC_FLAGS} -c my_readline.c

clean: 
	rm -f *.o core* ${OUTPUT}