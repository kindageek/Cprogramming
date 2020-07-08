#include "ls.h"

// Function to initialize array of strings
string_array* init_array(int size)
{
    string_array* path = (string_array*)malloc(sizeof(string_array));                  // array of paths with max possible length is argc-1
    path->size = size;
    path->array = (char**)malloc(sizeof(char*) * size);
    return path;
}

// Function to free memory allocated for array of strings
void free_string_array(string_array* arr)
{
    for (int i = 0; i < arr->size; i++)
    {
        free(arr->array[i]);
    }
    free(arr->array);
    free(arr);
}

// Custom strcmp
int my_strcmp(const char* a, const char* b) 
{
    while (*a)
    {
        if (*a != *b) break;
        a++;
        b++;
    }
    return *(const unsigned char*)a - *(const unsigned char*)b;
}

// Custom strcpy
char* my_strcpy(char* a, const char* b) 
{
    if (!b || my_strlen(b) == 0) return NULL;
    while (*a) *a++ = *b++;
    return a;
}

// Custom strlen
int my_strlen(const char* a)
{
    int length = 0;
    while (a && *a != '\0')
    {
        length++;
        a++;
    }
    return length;
}

// Custom strcat
char* my_strcat(char* a, const char* b)
{
    a = realloc(a, my_strlen(a) + my_strlen(b) + 1);
    while (a && *a != '\0') 
    {
        a++;
    }
    while (b && *b != '\0')
    {
        *a++ = *b++;
    }
    *a = '\0';
    return a;
}