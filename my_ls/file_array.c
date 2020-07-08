# include "ls.h"

// Function to initialize array of files
file_array* init_files(int fileCount)
{
    file_array* files = (file_array*)malloc(sizeof(file_array));
    files->size = fileCount;
    files->array = (file**)malloc(sizeof(file*) * fileCount);
    for (int i = 0; i < fileCount; i++)
    {
        files->array[i] = (file*)malloc(sizeof(file*));
    } 
    return files;
}

// Function to add filename to array of files
void add_to_array(file** dest, char* src)
{
    file* f = *dest;
    f->name = (char*)malloc(sizeof(char) * strlen(src));
    strcpy(f->name, src);
}

// Function to assign modification times to file in an array
void assign_times(file** f, char* filepath)
{
    file* buffer = *f;
    struct stat file_info;
    stat(filepath, &file_info);
    struct timespec time = file_info.st_mtimespec;
    buffer->sec = (unsigned long)time.tv_sec;
    buffer->nsec = (unsigned long)time.tv_nsec;
}

// Function to swap files in the array of files 
void swap_files(file** a, file** b)
{
    file* temp;
    temp = *a;
    *a = *b;
    *b = temp;
}

// Function needed to sort files
bool has_higher_precedence(file* a, file* b, bool by_time)
{
    if (by_time && ((a->sec < b->sec)                                                                            // case 1: if the seconds of the first file is less than that of the second one
                || (a->sec == b->sec && a->nsec < b->nsec)                                                       // case 2: if the seconds are equal, but nanoseconds of the first file is less than that of the second one
                || (a->sec == b->sec && a->nsec == b->nsec && my_strcmp(a->name, b->name) > 0))) return true;    // case 3: if both seconds and nanoseconds are equal -> sort alphabetically
    else if (!by_time && my_strcmp(a->name, b->name) > 0) return true;
    else return false;
}

// Function to sort the array of files
void sort_files(file_array** files, bool by_time)
{
    file_array* arr = *files;
    for (int i = 0; i < arr->size; i++)
    {
        for (int j = i; j < arr->size; j++)
        {
            if (has_higher_precedence(arr->array[i], arr->array[j], by_time))
            {
                swap_files(&arr->array[i], &arr->array[j]);
            }
        }
    }
}

// Function to print names of files in the array of files 
void print_files(file_array* files)
{
    for (int i = 0; i < files->size; i++)
    {
        printf("%s", files->array[i]->name);
        if (i != files->size - 1) printf("  ");
    }
}

// Function to free memory allocated for array of files
void free_files(file_array* files)
{
    for(int i = 0; i < files->size; i++)
    {
        free(files->array[i]->name);
        free(files->array[i]);
    }
    free(files->array);
    free(files);
}