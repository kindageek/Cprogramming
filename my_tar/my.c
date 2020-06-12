#include <stdlib.h>

void my_memset(char* buff, char val, int size)
{
    int index = 0;
    while(index < size){
        buff[index] = val;
        index += 1;
    }
}

void my_bzero(char* buff, int size)
{
    my_memset(buff, 0, size);
}