# My_tar project in C programming language

This program is a custom implementation of GNU tar command. It was made as a group project with [Gassyr Bakubay](https://github.com/bakubay) for Qwant and Silicon Valley Qwasar coding school. The program was divided into several .c files for separate tar options. Also, it has Makefile and .h header file which includes prototypes of custom structures and all functions in the project. It also uses custom implementations of regular and popular functions from string.h library.

my_tar is a command to manipulate tape archive. The first option to tar is a mode indicator from the following list:

- `-c` Create a new archive containing the specified items.
- `-r` Like -c, but new entries are appended to the archive. The -f option is required.
- `-t` List archive contents to stdout.
- `-u` Like -r, but new entries are added only if they have a modification date newer than the corresponding entry in the archive. The -f option is required.
- `-x` Extract to disk from the archive. If a file with the same name appears more than once in the archive, each copy will be extracted, with later copies overwriting (replacing) earlier copies.

In `-c, -r, or -u` mode, each specified file or directory is added to the archive in the order specified on the command line. By default, the contents of each directory are also archived.

Unless specifically stated otherwise, options are applicable in all operating modes:

- -f file Read the archive from or write the archive to the specified file. The filename can be standard input or standard output

The tar utility returns 0 on success, and >0 if an error occurs.

## How to use?

1. Download and clone the repository using this [link](https://github.com/SanzharNussipbek/Cprogramming.git)
2. Open terminal and go to the my_tar directory
3. Type `make` and press Enter
4. Type `./my_tar -c/x/r/u/f archive.tar file1 file2 ...`
5. Type `make clean` to delete all .o files created after the step 3

## Files:

- my_tar.c - file with the main function
- my_tar.h - header file which includes all custom structures and function prototypes
- Makefile - makefile to run the program with one-word-command
- archive.c - file with all functions related to an archive
- header.c - file with all functions related to a header
- args.c - file which handles linked list of arguments containing filenames from command line
- write.c - file with all functions needed to write files/directories to an archive
- get_opt.c - file to handle command line arguments and initiate options, archive name and argument list
- print_opt.c - file with a function to print options in order to check if get_opt.c worked correctly
- create.c - file to handle -c option
- append.c - file to handle -r option
- update.c - file to handle -u option
- extract.c - file to handle -x option
- print.c - file to handle -t option

## Conclusion

As a result of this project, I learned a lot about custom structures, GNU tar format and using git to work in a group project.
