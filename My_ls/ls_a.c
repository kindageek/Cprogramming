#include "ls.h"     //Include custom heading "ls.h"


/*
 * ls_a function to print regular and hidden files sorted lexicographically or by modification time, 
 * Can use recursion if it is chosen
 */
void ls_a(const char *path, bool r, bool t)
{
    if(r) printf("%s:\n", path);

    DIR *dir = opendir(path);
    struct dirent *sd;
    
    if(dir == NULL) return;

    int fileCount = getFileCount(path) + hidden_fileCount(path);    //get the number of both regular and hidden files
    if(t == true)
        fileCount+=2;                                               //add 2 more space for current(".") and parent("..") directories

    int index = 0;

    file_array* files = (file_array*)malloc(sizeof(file_array*));
    files->size = fileCount;
    files->array = (file**)malloc(sizeof(file*) * fileCount);
    for(int i = 0; i < fileCount; i++){
        files->array[i] = (file*)malloc(sizeof(file*));
    }             

    //if t is not chosen save all files except current and parent directories to file array
    //if t is chosen, save all files and their mtimes to file array
    if(t == false){
        while((sd = readdir(dir)) != NULL){                                         
            if (my_strcmp(sd->d_name, ".") != 0 && my_strcmp(sd->d_name, "..") != 0){   
                files->array[index]->name = (char*)malloc(sizeof(char) * my_strlen(sd->d_name));    
                my_strcpy(files->array[index]->name, sd->d_name);                            
                index++;                                                           
            }
        }
    }else{                                                                                              
        char* new_path;
        while((sd = readdir(dir)) != NULL){                                         
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

    //if t is not chosen, sort alphabetically
    //if t is chosen, sort by time
    if(!t){
        for(int i = 0; i < files->size; i++){
            for(int j = i; j < files->size; j++){
                if(my_strcmp(files->array[i]->name, files->array[j]->name) > 0){
                    swap_files(files->array[i], files->array[j]);
                }
            }
        }
    }else{
        for(int i = 0; i < files->size; i++){
            for(int j = i; j < files->size; j++){
                if((files->array[i]->sec < files->array[j]->sec)                                //case 1: if the seconds of the first file is less than that of the second one
                    || (files->array[i]->sec == files->array[j]->sec                            //case 2: if the seconds are equal,
                            && files->array[i]->nsec < files->array[j]->nsec)                   //but nanoseconds of the first file is less than that of the second one
                    || (files->array[i]->sec == files->array[j]->sec                            //case 3: if both seconds and nanoseconds are equal
                            && files->array[i]->nsec == files->array[j]->nsec                   //the sort alphabetically
                            && my_strcmp(files->array[i]->name, files->array[j]->name) > 0)){
                    
                    swap_files(files->array[i], files->array[j]);
                }
            }
        }
    }

    if(!t) printf(".  ..  "); //print current and parent directory, they should printed at the beginning if t is not chosen
    print(files);

    //call ls_s recursively with directories if r is chosen
    if(r){
        char* new_path;
        for(int i = 0; i < files->size; i++){
            if (my_strcmp(files->array[i]->name, ".") != 0 && my_strcmp(files->array[i]->name, "..") != 0){
                new_path = (char*)malloc(sizeof(char) * (my_strlen(path) + 1 + my_strlen(files->array[i]->name)));
                my_strcpy(new_path, path);                                         
                my_strcat(new_path, "/");                                          
                my_strcat(new_path, files->array[i]->name);                                   

                if(isDirectory(new_path)){
                    printf("\n\n");
                    ls_a(new_path, r, t);                                                     
                }

                free(new_path);
            }
        }
    }
    
    resetFiles(files);
    closedir(dir);                                                        
}