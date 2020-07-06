# My_readline.c project in C programming language

The function `my_readline` reads a line from the stream represented by `fd`(file descriptor) and returns it into an allocated string (heap or stack ?). It stops when either the newline character is read or when the end-of-file is reached, whichever comes first. The newline character is not copied to the string.

## Details

- On success, a pointer to the string is returned. On error, a ***null*** pointer is returned. If the end-of-file occurs before any characters have been read, the string remains unchanged.
- Number of characters read will be set by the define **READLINE_READ_SIZE**, which can have any value greater than 0.
- Only one static variable `static char leftover[READLINE_READ_SIZE + 1]` is used in this project.
- The function works with any of streams, whether it be a **file, standard input or a redirection**
- It can be used in a loop to read an entire file line by line;
- It has no memory leaks or unused code lines and can be compiled with flags `-g3 -fsanitize=leak` and -Wall -Wextra -Werror

## How to use?

- The **my_readline.c** file has main function and separate **Makefile** which can be used to test the function. To test it, you need to download the files and inside the folder with the file, type `make` to compile the file and `./my_readline` to run it in the console to run the program.
- In case you want to make use of this function in your own project, download the my_readline.c file, remove the main function and add the prototype of **my_readline** function to your header file.

## Conclusion

As a result of this project, I improved my skills in programming in C programming language and learned how to work with static variables.
