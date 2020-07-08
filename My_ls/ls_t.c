#include "ls.h"

/*
 * ls_t function to print regular files sorted by modification time, 
 * Can use recursion if it is chosen
 * The same as ls_a option with t, except exluding hidden files
 */ 
void ls_t(char* path, bool r)
{
    if (r) printf("%s:", path);

    DIR *dir = opendir(path);
    struct dirent *sd;
    
    if (dir == NULL)
    {
        printf("%s\n", path);
        return;
    }

    int fileCount = getFileCount(path);
    file_array* files = init_files(fileCount);
    if (r && files->size !=0) printf("\n");
    int index = 0;
    char* filepath;
    while ((sd = readdir(dir)) != NULL)
    {
        if (is_regular_file(sd->d_name))
        {
            add_to_array(&files->array[index], sd->d_name);                               
            filepath = get_filepath(path, sd->d_name);                                 
            assign_times(&files->array[index], filepath);                                     
            free(filepath);
            index++;                                     
        }
    }
    sort_files(&files, true);
    print_files(files);
    
    if (r) ls_r(files, path, false, true);
    
    free_files(files);
    closedir(dir);
}