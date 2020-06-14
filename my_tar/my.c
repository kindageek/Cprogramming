#include <stdlib.h>

// custom memset implementation to fill the buffer with zeros
void my_memset(char* buff, char val, int size)
{
    int index = 0;
    while(index < size){
        buff[index] = val;
        index += 1;
    }
}


// custom bzero implementation which uses custom memset
void my_bzero(void * buff, size_t size)
{
    if (size == 0) {
        return;
    }
    
    my_memset(buff, 0, size);
}