#include "ls.h"     //Include custom heading "ls.h"

/*
 *  My my_ls is compiled with the name "ls", so when testing my program, please use "./ls". Thanks :) 
 */


/*
 * Main function, takes command line arguments as parameters
 * Creates the array of paths from arguments
 * Looks for options(r, a, t) in arguments
 * Calls my_ls function
 */
int main(int argc, const char* argv[])
{
    bool r = false;                                                                     //identifiers for "R", "a", "t" options
    bool a = false;
    bool t = false;                                                         
    bool empty_path = true;                                                             //identifier for path array whether it is empty or not
    int index = 0;
    int dirCount = 0;                                                                   //counter for index and directories

    string_array* path = (string_array*)malloc(sizeof(string_array*));                  //array of paths with max possible length is argc-1
    path->size = argc-1;
    path->array = (char**)malloc(sizeof(char*)*(argc-1));

    if(argc == 1){
        my_ls(".", false, false, false);                                                //if there is only "./ls", then print current directory data
        printf("\n");
    }else{
        for(int i = 1; i < argc; i++){
            if(argv[i][0] == '-'){                                                      //if the argument is an option
                char* option = (char*)(argv[i]+1);                                      //get the pointer for the option character
                while(*option != '\0'){                                                 //iterate through options
                    if(*option == 'R'){
                        r = true;                                                       //if there is option "R", modify its identifier to 1
                    }else if(*option == 'a'){
                        a = true;                                                       //if there is option "a", modify its identifier to 1
                    }else if(*option == 't'){
                        t = true;                                                       //if there is option "t", modify its identifier to 1
                    }else{                                                  
                        printf("ls: invalid option -- \'%c\'\n", *option);              //if there is unidentified option, prompt for error and return
                        printf("Try \'ls --help\' for more information.\n");
                        return(1);
                    }
                    option++;                                                           //continue iteration
                }
            }else{
                empty_path = false;                                                     //set array as non-empty
                path->array[index] = (char*)malloc(sizeof(char) * my_strlen(argv[i]));  //allocate memory for array element
                my_strcpy(path->array[index], argv[i]);                                 //copy argument to array element
                index++;                                                                //increment index   
                dirCount++;                                                             //increment counter for directories
            }
        }

        if(!empty_path){                                                                //if array of paths is not empty
            for(int i = 0; i < dirCount; i++){                                          //Use my_ls for all directories in the array
                if(dirCount != 1)           
                    printf("%s:\n", path->array[i]);                                    //print directory name if there are more than one, just like in ls
                
                my_ls(path->array[i], r, a, t);                                         //call my_ls function with array element and "Rat" options
                
                if(i != dirCount - 1)
                    printf("\n\n");                                                     //print new lines after every directory data
                else
                    printf("\n");                                                       
            }
        }else{
            my_ls(".", r, a, t);                                                        //if array is empty, use options to current directory
            printf("\n");
        }
    }

    my_free(path);                                                                      //free memory allocated for array of paths
    return 0;                                                                           //return 0
}


/*
 * my_ls function takes path and options as parameters
 * Firstly, it checks whether the paths is file or if it doesn't exist
 * If so, it prompts accordingly and returns
 * In other case, it checks options and call one of the following functions: ls_a, ls_t or simple _ls function 
 */ 
void my_ls(const char *path, bool r, bool a, bool t)
{
    DIR *dir = opendir(path);                                                           //create a directory with given path                                                                                                            
    
    if(dir == NULL){                                                                    //if the path is not a directory
        if(isFile(path))                                                                //if the path is file
            printf("%s", path);                                                         //print filename 
        else                                                                            //if the path is neither directory nor file
            printf("ls: cannot access \'%s\': No such file or directory", path);        //print error message
            
        return;                                                                         //return
    }

    closedir(dir);                                                                      //close the directory

    if(a){                      //if option 'a' is chosen
        ls_a(path, r, t);       
    }else{                      //if option 'a' is not chosen
        if(t){                  //if option 't' is chosen
            ls_t(path, r);
        }else{                  //if option 't' is not chosen
            _ls(path, r);
        }
    }

}