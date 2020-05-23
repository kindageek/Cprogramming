#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <dirent.h>
#include <time.h>
#include <stdbool.h>
#include <fcntl.h>

//custom implementation of string array structure
typedef struct s_string_array
{           
    int size;
    char** array;
} string_array;

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

//custom implementation for array of file structures
typedef struct file_array               
{
    int size;
    file** array;
} file_array;


//Prototypes of all functions in this project
void my_ls(const char* path, bool r, bool a, bool t);   //function which handles which option and method to use according to input
void _ls(const char* path, bool r);                     //function to print regular files sorted lexicographically, can use recursion if it is chosen
void ls_a(const char* path, bool r, bool t);            //function to print regular and hidden files sorted lexicographically or by modification time, can use recursion if it is chosen
void ls_t(const char* path, bool r);                    //function to print regular files sorted by modification time, can use recursion if it is chosen
void my_free(string_array* arr);                        //custom function for freeing memory of a string array
void resetFiles(file_array* files);                     //custom function for freeing memory of a file array
int getFileCount(const char* path);                     //function to get the number of regular files in a directory
int hidden_fileCount(const char* path);                 //function to get the number of hidden files in a directory
bool isFile(const char* filename);                      //function to check if the input is the file name
int isDirectory(const char* path);                      //function to check if the input is the directory name
void print(file_array* files);                          //function to print the names of files in the array
void swap_files(file* a, file* b);                      //function to swap two files in the array
int my_strcmp(const char* a, const char* b);            //custom strcmp
const char* my_strcpy(char* a, const char* b);          //custom strcpy
int my_strlen(const char* a);                           //custom strlen
const char* my_strcat(char* a, const char* b);          //custrom strcat