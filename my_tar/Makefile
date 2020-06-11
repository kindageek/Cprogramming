CC = gcc
CC_OPT = -g3 -fsanitize=address 
OUTPUT = my_tar

all: $(OUTPUT)

my_tar: my_tar.o get_opt.o print_opt.o
	$(CC) $(CC_OPT) my_tar.o get_opt.o print_opt.o -o $(OUTPUT)

my_tar.o: my_tar.c my_tar.h
	$(CC) $(CC_OPT) my_tar.c
	
get_opt.o: get_opt.c my_tar.h
	$(CC) $(CC_OPT) get_opt.c

print_opt.o: print_opt.c my_tar.h
	$(CC) $(CC_OPT) print_opt.c

clean: 
	rm -f *.o $(OUTPUT)