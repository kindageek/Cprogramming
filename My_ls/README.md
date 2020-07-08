# My_ls program in C programming language

This program is a custom implementation of [ls](https://en.wikipedia.org/wiki/Ls) command in UNIX. It was made as a project for Qwant and Silicon Valley Qwasar coding school. The program was divided into several .c files for separate ls options. Also, it has Makefile and .h header file which includes prototypes of custom structures and all functions in the project. It also uses custom implementations of regular and popular functions from string.h library.

## How to use?

1. Download and clone the repository using this [link](https://github.com/SanzharNussipbek/Cprogramming.git)
2. Open terminal and go to the my_ls directory
3. Type `make` and press Enter
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

- ***main.c*** - main program
- ***my_ls.c*** -  program which handles reading command line arguments
- ***_ls.c*** - program to handle simple ls command
- ***ls_a.c*** - program to handle `-a` option, supports -R to use recursion
- ***ls_t.c*** - program to handle `-t` option, supports -R to use recursion
- ***ls_r.c*** - program to handle `-R` option
- ***ls.h*** - header file containing prototypes of string_array, file and file_array structures and prototypes of all functions in the project
- ***get_opt.c*** - function to get list of options from command line
- ***Makefile*** - Makefile for the project
- ***file_manipulation.c*** - program to handle file manipulations like checking if the file is a regular or a hidden file, or parent/current directory
- ***file_array.c*** - program to handle manipulations with the array of file structures
- ***string.c*** - program to handle manipulations with the array of strings and containing custom implementations of functions from string.h library

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

```c
// Function to swap files in the array of files 
void swap_files(file** a, file** b)
{
    file* temp;
    temp = *a;
    *a = *b;
    *b = temp;
}

// Function needed to sort files
bool has_higher_precedence(file* a, file* b, bool by_time)
{
    if (by_time && ((a->sec < b->sec)                                                                            // case 1: if the seconds of the first file is less than that of the second one
                || (a->sec == b->sec && a->nsec < b->nsec)                                                       // case 2: if the seconds are equal, but nanoseconds of the first file is less than that of the second one
                || (a->sec == b->sec && a->nsec == b->nsec && my_strcmp(a->name, b->name) > 0))) return true;    // case 3: if both seconds and nanoseconds are equal -> sort alphabetically
    else if (!by_time && my_strcmp(a->name, b->name) > 0) return true;
    else return false;
}

// Function to sort the array of files
void sort_files(file_array** files, bool by_time)
{
    file_array* arr = *files;
    for (int i = 0; i < arr->size; i++)
    {
        for (int j = i; j < arr->size; j++)
        {
            if (has_higher_precedence(arr->array[i], arr->array[j], by_time))
            {
                swap_files(&arr->array[i], &arr->array[j]);
            }
        }
    }
}
```

## Conclusion

As a result of this project, I learned a lot about accessing files and directories using dirent.h library, using UNIX ls command and recursion in C. Also, I am now able to moderately code in C low-level programming language and use Makefiles and headers in the project.