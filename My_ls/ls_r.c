# include "ls.h"

void ls_r(file_array* files, char* path, bool a, bool t)
{
    char* filepath = NULL;
    for (int i = 0; i < files->size; i++)
    {   
        if (a == true && is_curr_par_dir(files->array[i]->name))
        {
            continue;
        }     
        else
        {
            filepath = get_filepath(path, files->array[i]->name);                           
            if (isDirectory(filepath))
            {
                printf("\n\n");
                if (a) ls_a(filepath, true, t); 
                else
                {
                    if (t) ls_t(filepath, true);
                    else _ls(filepath, true);
                }                                                   
            }
            free(filepath);
        }                            
    }
}