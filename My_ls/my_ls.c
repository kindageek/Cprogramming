#include "ls.h"                

void run(int argc, const char* argv[])
{
    bool r = false;                                                                     // identifiers for "R", "a", "t" options
    bool a = false;
    bool t = false;                                                         
    bool empty_path = true;                                                             // identifier for path array whether it is empty or not
    int index = 0;
    int dirCount = 0;                                                                   // counter for index and directories

    string_array* path = init_array(argc - 1);
    for (int i = 1; i < argc; i++)
    {
        if (is_option(argv[i]))                                                         // if the argument is an option
        {                                                      
            if (get_options(argv[i], &r, &a, &t) != 0)                                      // parse the options
            {                                                                           // if option is invalid
                free_string_array(path);                                                // free memory allocated for array of paths
                return;
            }
        }
        else
        {
            empty_path = false;                                                         // set array as non-empty
            path->array[index] = (char*)malloc(sizeof(char) * my_strlen(argv[i]));      // allocate memory for array element
            my_strcpy(path->array[index], argv[i]);                                     // copy argument to array element
            index++;                                                                    // increment index   
            dirCount++;                                                                 // increment counter for directories
        }
    }

    if (!empty_path)                                                                    // if array of paths is not empty
    {                                                                
        for (int i = 0; i < dirCount; i++)                                              // Use my_ls for all directories in the array
        {                                          
            if (dirCount != 1) printf("%s:\n", path->array[i]);                         // print directory name if there are more than one, just like in ls
            my_ls(path->array[i], r, a, t);                                             // call my_ls function with array element and "Rat" options
            if (i != dirCount - 1) printf("\n\n");                                      // print new lines after every directory data
            else printf("\n");                                                       
        }
    }
    else
    {
        my_ls(CURRENT_DIR, r, a, t);                                                    // if array is empty, use options to current directory
    }
    free_string_array(path);                                                            // free memory allocated for array of paths
}


/*
 * my_ls function takes path and options as parameters
 * Firstly, it checks whether the paths is file or if it doesn't exist
 * If so, it prompts accordingly and returns
 * In other case, it checks options and call one of the following functions: ls_a, ls_t or simple _ls function 
 */ 
void my_ls(char *path, bool r, bool a, bool t)
{
    DIR *dir = opendir(path);                                                           // create a directory with given path                                                                                                            
    if (dir == NULL)                                                                    // if the path is not a directory
    {                                                                    
        if (isFile(path)) printf("%s", path);                                           // if the path is file, print filename 
        else printf(NO_FILE, path);                                                     // if the path is neither directory nor file, print error message
        return;                                                                         // return
    }
    closedir(dir);                                                                      // close the directory
    if (a)                                                                              // if option 'a' is chosen
    {                     
        ls_a(path, r, t);                                                               // call ls -a
    }
    else
    {                      
        if (t) ls_t(path, r);                                                           // if option 't' is chosen
        else  _ls(path, r);                                                             // if not, call regular ls
    }
    if (!r && !a && !t) printf("\n");                                                   // if none of the options are chosen, print new line after regular ls
}