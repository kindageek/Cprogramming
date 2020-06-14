#include "my_tar.h"

char *my_itoa_base(char *res, unsigned int number, int size, int base)
{
    const char symbols[] = "0123456789abcdef";
    my_memset(res, '0', size -1);
    res[size - 1] = '\0';
    size--;
    while(number)
    {
        res[--size] = symbols[number % base];
        number /= base;
    }
    return res;
}