#include "ls.h"     //Include custom heading "ls.h"

/*
 * ls_t function to print regular files sorted by modification time, 
 * Can use recursion if it is chosen
 * The same as ls_a option with t, except exluding hidden files
 */ 
void ls_t(const char* path, bool r)
{
    if(r) printf("%s:", path);

    DIR *dir = opendir(path);
    struct dirent *sd;
    
    if(dir == NULL){
        printf("%s\n", path);
        return;
    }

    int fileCount = getFileCount(path);
    int index = 0;
    file_array* files = (file_array*)malloc(sizeof(file_array*));
    files->size = fileCount;
    files->array = (file**)malloc(sizeof(file*) * fileCount);
    for(int i = 0; i < fileCount; i++){
        files->array[i] = (file*)malloc(sizeof(file*));
    } 

    if(r && files->size !=0) printf("\n");
    
    char* new_path;
    while((sd = readdir(dir)) != NULL){
        if (my_strcmp(sd->d_name, ".") != 0 && my_strcmp(sd->d_name, "..") != 0 && sd->d_name[0] != '.'){
            files->array[index]->name = (char*)malloc(sizeof(char) * my_strlen(sd->d_name));      
            my_strcpy(files->array[index]->name, sd->d_name);                                   

            new_path = (char*)malloc(sizeof(char) * (my_strlen(path) + 1 + my_strlen(sd->d_name)));
            my_strcpy(new_path, path);                                         
            my_strcat(new_path, "/");                                          
            my_strcat(new_path, sd->d_name);                               

            struct stat file_info;
            stat(new_path, &file_info);
            struct timespec time = file_info.st_mtim;
            
            files->array[index]->sec = (unsigned long)time.tv_sec;
            files->array[index]->nsec = (unsigned long)time.tv_nsec;                                        
             
            index++;      
            free(new_path);                               
        }
    }
    
    for(int i = 0; i < files->size; i++){
        for(int j = i; j < files->size; j++){
            if((files->array[i]->sec < files->array[j]->sec) 
                || (files->array[i]->sec == files->array[j]->sec 
                        && files->array[i]->nsec < files->array[j]->nsec) 
                || (files->array[i]->sec == files->array[j]->sec 
                        && files->array[i]->nsec == files->array[j]->nsec 
                        && my_strcmp(files->array[i]->name, files->array[j]->name) > 0)){
                
                swap_files(files->array[i], files->array[j]);
            
            }
        }
    }
    
    print(files);

    if(r){
        char* new_path;
        for(int i = 0; i < files->size; i++){
            if (my_strcmp(files->array[i]->name, ".") != 0 && my_strcmp(files->array[i]->name, "..") != 0 && files->array[i]->name[0] != '.'){
                new_path = (char*)malloc(sizeof(char) * (my_strlen(path) + 1 + my_strlen(files->array[i]->name)));
                my_strcpy(new_path, path);                                         
                my_strcat(new_path, "/");                                          
                my_strcat(new_path, files->array[i]->name);                                   

                if(isDirectory(new_path)){
                    printf("\n\n");
                    ls_t(new_path, r);                                                     
                }

                free(new_path);
            }
        }
    }

    resetFiles(files);
    closedir(dir);
}