#include "ls.h"

/*
 * _ls function to print regular files sorted lexicographically
 * Can use recursion if it is chosen
 */ 
void _ls(char* path, bool r)
{
    if (r) printf("%s:", path);                                                     // if the 'r' option is chosen, print directory name

    DIR *dir = opendir(path);                                                       // open the directory
    struct dirent *sd;                                                          

    int fileCount = getFileCount(path);                                             // get number of regular files                                 
    file_array* files = init_files(fileCount);                                      // init array of files
    
    if (r && files->size !=0) printf("\n");                                         // this is for output design to be similar with original ls output

    int index = 0;
    while ((sd = readdir(dir)) != NULL)                                             // raverse the directory                                    
    {    
        if (is_regular_file(sd->d_name))                                            // if the file is a regular gile
        {
            add_to_array(&files->array[index], sd->d_name);                         // add filename to array of file
            index++;                                                            
        }
    }
    sort_files(&files, false);                                                       // sort the array of files alphabetically
    print_files(files);                                                              // print the files
    if (r) ls_r(files, path, false, false);
    
    free_files(files);                                                               // free the memory allocated for the array of files
    closedir(dir);                                                      
}