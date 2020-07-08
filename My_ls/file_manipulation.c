#include "ls.h" 

// Function to get full path of a file
char* get_filepath(char* old_path, char* filename)
{
    char* filepath = (char*)malloc(sizeof(char) * (my_strlen(old_path) + 1 + my_strlen(filename) + 1));     //create new path with existing path, slash and filename                            
    strcpy(filepath, old_path);                                         
    strcat(filepath, "/");                                          
    strcat(filepath, filename);
    return filepath;
}

// Function to get the number of regular files in the directory
int getFileCount(char* path)
{
    DIR *dir = opendir(path);
    struct dirent *sd;
    int fileCount = 0;
    while ((sd = readdir(dir)) != NULL)
    {
        if (is_regular_file(sd->d_name)) fileCount++;
    }
    closedir(dir);
    return fileCount;
}

// Function to get the number of hidden files in the directory
int hidden_fileCount(char* path)
{
    DIR *dir = opendir(path);
    struct dirent *sd;
    int count = 0;
    
    while ((sd = readdir(dir)) != NULL)
    {
        if (is_hidden_file(sd->d_name) && !is_curr_par_dir(sd->d_name)) count++;
    }
    
    closedir(dir);
    return count;
}

// Function to check if file is a regular file
bool is_regular_file(char* filename)
{
    return filename[0] != '.';
}

// Function to check if file is a hidded file
bool is_hidden_file(char* filename)
{
    return filename[0] == '.';
}

// Function to check if the file is a current or parent directory
bool is_curr_par_dir(char* filename)
{
    return my_strcmp(filename, CURRENT_DIR) == 0 || my_strcmp(filename, PARENT_DIR) == 0;
}

// Function to check if the path is file
bool isFile(char* path)
{
    FILE *file;
    file = fopen(path, "r");
    return file ? true : false;
}

// Function to check if the path is directory
int isDirectory(char *path) 
{
   struct stat statbuf;
   if (stat(path, &statbuf) != 0) return 0;
   return S_ISDIR(statbuf.st_mode);
}