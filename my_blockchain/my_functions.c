#include "header.h"

// custom memset which fills the buffer with specific value
void my_memset(char* buff, char val, int size)
{
    int index = 0;
    while (index < size)
    {
        buff[index] = val;
        index += 1;
    }
}

// custom bzero implementation which uses custom memset
void my_bzero(void* buff, size_t size)
{
    my_memset(buff, 0, size);
}

// custom my_split made in BootCamp C Quest08
string_array* my_split(char* a, char* b) 
{
    int lenA = strlen(a);                                               //get length of ptr a
    int lenB = strlen(b);                                               //get length of ptr b

    if (lenA == 0 || lenB == 0) return NULL;                            //if either of a or b is empty            
    
    int size = 0;                                                       //size of the returning string_array
    int index = 0;                                                      //index for the string_array elements
    
    for (int i = 0; i < lenA; i++)                                      //count number of separators in the text
    {                                     
        if (a[i] == *b) size++;
    }
    size+=1;                                                            //+1 because one separators divides the text into 2, 
                                                                        //another +1 is for null terminator
    string_array* arr = (string_array*)malloc(sizeof(string_array*));   //initialize string_array
    arr->size = size;                                                   //size of the array
    arr->array = (char**)malloc(sizeof(char*) * size);                  //malloc the array
    
    char* piece = strtok(a, b);                                         //pointer for each piece of the divided text                                           
    char* word;
    while (piece != NULL)                                               //while there are pieces
    {   
        word = strdup(piece);
        arr->array[index] = (char*)malloc(sizeof(char) * strlen(word));                                                              
        strcpy(arr->array[index], word);                               //save the piece 
        piece = strtok(NULL, b);                                        //get the next piece
        free(word);
        index++;                                                        //increment the index
    }
    free(piece);
    return arr;                                                         //return array
}

// Custom string to integer/long
int my_atoi(char* number_string, int size)
{
    int index = 0;
    int res = 0;
    while (index < size && number_string[index])
    {
        if (number_string[index] >= '0' && number_string[index] <= '9')
        {
            res *= 10;
            res += number_string[index] - '0';
        }
        index++;
    }
    return res;
}

// Function to reverse a string
char* my_reverse(char* ptr){
    int len = strlen(ptr);
    if (len <= 1) return ptr;
    int i = len - 1;  
    char* s = (char*)malloc(sizeof(char) * (len + 1));  
    s[len]='\0';
    while (ptr && *ptr !='\0')
    {
        s[i] = *ptr;
        ptr++;
        i--;
    }
    free(ptr);
    return s;
}

// Custom integer to string with specific base number
char* my_itoa(int val, int base)
{
    char* ptr = (char*)malloc(sizeof(char) * 100);
    my_bzero(ptr, 100);
    if (base < 2 || base > 16) return ptr;
    int num, i = 0;
    if(val < 0) num = -val;
    else num = val;
    if (num == 0)
    {
        ptr[i++] = '0';
        ptr[i] = '\0';
        return ptr;
    }
    while (num != 0)
    {
        int r = num % base;
        if (r >= 10) ptr[i] = 65 + (r - 10);
        else ptr[i] = 48 + r;
        num /= base;
        i++;
    }
    if (val < 0 && base == 10) ptr[i++] = '-';
    char* res = (char*)malloc(strlen(ptr));
    strcpy(res, ptr);
    res = my_reverse(res);
    free(ptr);
    return res;
}

void free_string_array(string_array* words)
{
    for (int i = 0; i < words->size; i++)
    {
        free(words->array[i]);
    }
    free(words->array);
    free(words);
}