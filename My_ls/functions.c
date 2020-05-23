#include "ls.h"     //Include custom heading "ls.h"

/*
 * Function to print names of files in the array of files 
 */ 
void print(file_array* files)
{
    for(int i = 0; i < files->size; i++){
        printf("%s  ", files->array[i]->name);
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


/*
 * Function to get the number of regular files in the directory
 */
int getFileCount(const char* path)
{
    DIR *dir = opendir(path);
    struct dirent *sd;
    int fileCount = 0;
    
    while((sd = readdir(dir)) != NULL){
        if (my_strcmp(sd->d_name, ".") != 0 && my_strcmp(sd->d_name, "..") != 0 && sd->d_name[0] != '.')
            fileCount++;
    }
    
    closedir(dir);
    return fileCount;
}

/*
 * Function to get the number of hidden files in the directory
 */
int hidden_fileCount(const char* path)
{
    DIR *dir = opendir(path);
    struct dirent *sd;
    int count = 0;
    
    while((sd = readdir(dir)) != NULL){
        if (sd->d_name[0] == '.' && my_strcmp(sd->d_name, ".") != 0 && my_strcmp(sd->d_name, "..") != 0)
            count++;
    }
    
    closedir(dir);
    return count;
}


/*
 * Function to check if the path is file
 */
bool isFile(const char* path)
{
    FILE *file;
    file = fopen(path, "r");
    
    if(file == NULL)
        return false;

    return true;
}

/*
 * Function to check if the path is directory
 */ 
int isDirectory(const char *path) 
{
   struct stat statbuf;
   if (stat(path, &statbuf) != 0)
       return 0;
   
   return S_ISDIR(statbuf.st_mode);
}


/*
 * Function to free memory allocated for array of strings
 */
void my_free(string_array* arr)
{
    for(int i = 0; i < arr->size; i++){
        free(arr->array[i]);
    }
    free(arr);
}

/*
 * Function to free memory allocated for array of files
 */
void resetFiles(file_array* files)
{
    for(int i = 0; i < files->size; i++){
        free(files->array[i]->name);
        free(files->array[i]);
    }
    free(files);
}