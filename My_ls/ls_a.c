#include "ls.h"

/*
 * ls_a function to print regular and hidden files sorted lexicographically or by modification time, 
 * Can use recursion if it is chosen
 */
void ls_a(char *path, bool r, bool t)
{
    if (r) printf("%s:\n", path);

    DIR *dir = opendir(path);
    struct dirent *sd;
    
    if (dir == NULL) return;

    int fileCount = getFileCount(path) + hidden_fileCount(path);                            // get the number of both regular and hidden files
    if (t == true) fileCount += 2;                                                          // add 2 more space for current(".") and parent("..") directories
    file_array* files = init_files(fileCount);  
    
    int index = 0;                                                                                             
    char* filepath;
    while ((sd = readdir(dir)) != NULL)                                                     // save file names and file mtimes in seconds and nanoseconds to the array
    {   
        if (!t && is_curr_par_dir(sd->d_name)) continue;                                     
        add_to_array(&files->array[index], sd->d_name);                 
        filepath = is_curr_par_dir(sd->d_name) ? sd->d_name : get_filepath(path, sd->d_name);
        if (t) assign_times(&files->array[index], filepath);
        if (!is_curr_par_dir(sd->d_name)) free(filepath);
        index++;                                                       
    }
    sort_files(&files, t);
    
    if (!t) printf(".  ..  ");                                                               // print current and parent directory, they should printed at the beginning if t is not chosen
    print_files(files);

    if (r) ls_r(files, path, true, t);                                                       // go recursive if R option
    
    free_files(files);
    closedir(dir);                                                        
}