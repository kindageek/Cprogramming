#include "ls.h"     //Include custom heading "ls.h"


/*
 * _ls function to print regular files sorted lexicographically
 * Can use recursion if it is chosen
 */ 
void _ls(const char* path, bool r)
{
    if(r) printf("%s:", path);                                      //if the 'r' option is chosen, print directory name

    DIR *dir = opendir(path);                                                   
    struct dirent *sd;                                                          

    int fileCount = getFileCount(path);                             //get number of regular files                                 
    int index = 0;       

    file_array* files = (file_array*)malloc(sizeof(file_array*));   //create an array of files
    files->size = fileCount;
    files->array = (file**)malloc(sizeof(file*) * fileCount);
    for(int i = 0; i < fileCount; i++){
        files->array[i] = (file*)malloc(sizeof(file*));
    }           
    
    if(r && files->size !=0) printf("\n");                          //this is for output design to be similar with original ls output

    while((sd = readdir(dir)) != NULL){                                                                         //traverse the directory                                    
        if (my_strcmp(sd->d_name, ".") != 0 && my_strcmp(sd->d_name, "..") != 0 && sd->d_name[0] != '.'){       //if the file is not hidden
            files->array[index]->name = (char*)malloc(sizeof(char) * my_strlen(sd->d_name));                    //allocate memory
            my_strcpy(files->array[index]->name, sd->d_name);                                                   //save file to array
            index++;                                                           
        }
    }


    //sorting the array of files alphabetically
    for(int i = 0; i < files->size; i++){
        for(int j = i; j < files->size; j++){
            if(my_strcmp(files->array[i]->name, files->array[j]->name) > 0){
                swap_files(files->array[i], files->array[j]);
            }
        }
    }
    
    //print the files
    print(files);


    //if the recursion option is chosen
    //find directories in the array of files and call _ls function recursively with them
    if(r == true){
        char* new_path;
        for(int i = 0; i < files->size; i++){
            if (my_strcmp(files->array[i]->name, ".") != 0 && my_strcmp(files->array[i]->name, "..") != 0 && files->array[i]->name[0] != '.'){  
                new_path = (char*)malloc(sizeof(char) * (my_strlen(path) + 1 + my_strlen(files->array[i]->name)));     //create new path with existing path, slash and filename                            
                my_strcpy(new_path, path);                                         
                my_strcat(new_path, "/");                                          
                my_strcat(new_path, files->array[i]->name);                                   

                if(isDirectory(new_path)){      //check if the new path is a directory
                    printf("\n\n");
                    _ls(new_path, r);                                                     
                }

                free(new_path);                 //free the memory allocated for the new path
            }
        }
    }

    resetFiles(files);                          //free the memory allocated for the array of files
    closedir(dir);                                                      
}