# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include <sys/types.h>
# include <sys/stat.h>
# include <dirent.h>
# include <time.h>
# include <stdbool.h>
# include <fcntl.h>

# define CURRENT_DIR    "."
# define PARENT_DIR     ".."
# define INVALID_OPT    "ls: invalid option -- \'%c\'\n"
# define TRY_HELP       "Try \'ls --help\' for more information.\n"
# define NO_FILE        "ls: cannot access \'%s\': No such file or directory"

//custom implementation of string array structure
typedef struct s_string_array
{           
    int size;
    char** array;
} string_array;

/*
 * custom implementation for a file with its name 
 * and modification time in seconds and nanoseconds
 */
typedef struct file                     
{
    char* name;
    unsigned long sec;
    unsigned long nsec;
} file;

//custom implementation for array of file structures
typedef struct file_array               
{
    int size;
    file** array;
} file_array;


// my_ls.c
void run(int argc, const char* argv[]);
void my_ls( char* path, bool r, bool a, bool t);  

// _ls.c
void _ls(char* path, bool r);

// ls_a.c
void ls_a(char* path, bool r, bool t);    

// ls_t.c
void ls_t(char* path, bool r);      

// ls_r.c
void ls_r(file_array* files,  char* path, bool a, bool t);

// get_opt.c
bool is_option(const char* arg);
int get_options(const char* arg, bool* r, bool* a, bool* t);

// file_array.c
file_array* init_files(int fileCount);
void add_to_array(file** dest, char* src);
void swap_files(file** a, file** b);
void sort_files(file_array** files, bool by_time);
void assign_times(file** f, char* filepath);
void free_files(file_array* files);                                        
void print_files(file_array* files);                                    

// file_manipulation.c.c
char* get_filepath(char* old_path, char* filename);
int getFileCount(char* path);                 
int hidden_fileCount(char* path);                 
bool isFile(char* filename);                      
int isDirectory(char* path);
bool is_regular_file(char* filename);
bool is_hidden_file(char* filename);   
bool is_curr_par_dir(char* filename);

// string.c
string_array* init_array(int size);                     
void free_string_array(string_array* arr);              
int my_strlen(const char* a);                           
int my_strcmp(const char* a, const char* b);            
char* my_strcpy(char* a, const char* b);          
char* my_strcat(char* a, const char* b);          