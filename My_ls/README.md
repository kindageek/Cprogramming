# My_ls.c

This program is a custom implementation of [ls](https://en.wikipedia.org/wiki/Ls) command in UNIX. It was made as a project for Qwant and Silicon Valley Qwasar coding school. The program was divided into several .c files for separate ls options. Also, it has Makefile and .h header file which includes prototypes of custom structures and all functions in the project. It also uses custom implementations of regular and popular functions from string.h library.

## How to use?

1. Download and clone the repository using using this [link](https://github.com/SanzharNussipbek/Cprogramming.git)
2. Open terminal and go to the my_ls directory
3. Type `make all` and press Enter
4. Type `./ls [-R/a/t] [file1, file2, ...]`
5. Type `make clean` to delete all .o files created after the step 3

## Supported commands:

- `ls` - prints out ***regular* *files*** in the specified directory in ***lexicographical*** ***order***
- `ls -a` - prints out ***regular and hidden* *files*** in the specified directory in ***lexicographical*** ***order***
- `ls -t` - prints out ***regular* *files*** in the specified directory sorted by their ***modification*** ***time***
- `ls -R` - prints out ***regular* *files*** in the specified directory and all its subdirectories ***recursively*** in ***lexicographical*** ***order***
- `ls -at` - prints out ***regular** **and** **hidden*** ***files*** in the specified directory sorted by their ***modification*** ***time***
- `ls -Ra` - prints out ***regular** **and** **hidden*** ***files*** in the specified directory and all its subdirectories ***recursively*** in ***lexicographical*** ***order***
- `ls -Rt` - prints out ***regular*** ***files*** in the specified directory and all its subdirectories ***recursively*** sorted by their ***modification*** ***time***
- `ls -Rat` - prints out ***regular** **and** **hidden*** ***files*** in the specified directory and all its subdirectories ***recursively*** sorted by their ***modification*** ***time***

## Files:

- my_ls.c - main program which handles reading command line arguments
- _ls.c - program to handle simple ls command
- ls_a.c - program to handle "ls -a" command, supports "-R" to use recursion
- ls_t.c - program to handle "ls -t" command, supports "-R" to use recursion
- ls.h - header file containing prototypes of string_array, file and file_array structures and prototypes of all functions in the project
- Makefile - Makefile for the project
- functions.c - program containing all functions needed for the project, except command handlers.
    - `void print()` - print the array of files to standard output
    - `void swap_files()` - swap two files in the array, used in sorting
    - `int getFileCount()` - get the number of regular files in the given directory
    - `int hidden_fileCount()` - get the number of hidden files in the given directory
    - `bool isFile()` - check if the given path is a file
    - `int isDirectory()` - check if the given path is a directory
    - `void my_free()` - free the memory allocated for the array of strings
    - `void resetArray()` - free the memory allocated for the array of files
- strfunctions.c - program containing custom implementations of functions from string.h library
    - `int my_strcmp()` - custom strcmp()
    - `const char* my_strcpy()` - custom strcpy()
    - `int my_strlen()` - custom strlen()
    - `const char* my_strcat()` - custom strcat()

## Custom structures

```c
//custom implementation of string array structure
typedef struct s_string_array
{           
    int size;
    char** array;
} string_array;
```

```c
/*
 * custom implementation for a file with its name 
 * and modification time in seconds and nanoseconds
 */
typedef struct file                     
{
    char* name;
    unsigned long sec;
    unsigned long nsec;
} file;
```

```c
//custom implementation for array of file structures
typedef struct file_array               
{
    int size;
    file** array;
} file_array;
```

## Sorting the files and directories

- Selection sort is used to sort files: O(n^2) time complexity
1. Sorting files/directories lexicographically using their name

    ```c
    for(int i = 0; i < files->size; i++){
        for(int j = i; j < files->size; j++){
            if(my_strcmp(files->array[i]->name, files->array[j]->name) > 0){
                swap_files(files->array[i], files->array[j]);
            }
        }
    }
    ```

2. Sorting files/directories by their modification time

    ```c
    for(int i = 0; i < files->size; i++){
        for(int j = i; j < files->size; j++){
    				//case 1: if the seconds of the first file is less than that of the second one
            if((files->array[i]->sec < files->array[j]->sec)
    						//case 2: if the seconds are equal, but nanoseconds of the first file is less than that of the second one
                || (files->array[i]->sec == files->array[j]->sec 
                        && files->array[i]->nsec < files->array[j]->nsec)
                //case 3: if both seconds and nanoseconds are equal, sort alphabetically
    						|| (files->array[i]->sec == files->array[j]->sec                    
                        && files->array[i]->nsec == files->array[j]->nsec                   
                        && my_strcmp(files->array[i]->name, files->array[j]->name) > 0)){
                
                swap_files(files->array[i], files->array[j]);
            }
        }
    }

    /*
     * Function to swap files in the array of files 
     */
    void swap_files(file* a, file* b)
    {
        file temp;
        temp = *a;
        *a = *b;
        *b = temp;
    }
    ```

## Conclusion

As a result of this project, I learned a lot about accessing files and directories using dirent.h library, using UNIX ls command and recursion in C. Also, I am now able to moderately code in C low-level programming language and use Makefiles and headers in the project.
