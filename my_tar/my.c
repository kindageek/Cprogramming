#include "my_tar.h"

// Custom pow
int my_iterative_pow(int num, int pow)
{
    int result = 1;
    if (pow < 0) return 0;
    for (int i = 0; i < pow; i++) result *= num;
    return result;
}

// Custom string to integer/long
long my_atoi(char* number_string, int size)
{
    int index = 0;
    long res = 0;
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

// custom integer to string with specific base number
char* my_itoa(char* res, unsigned int num, int size, int base)
{
    const char symbols[] = "0123456789abcdef";
    my_memset(res, '0', size - 1);
    res[size - 1] = '\0';
    size--;
    while (num)
    {
        res[--size] = symbols[num % base];
        num /= base;
    }
    return res;
}

// custom octal to decimal
long my_oct_to_dec(long octal_number)
{
    int decimal = 0;
    int index = 0;
    while (octal_number > 0)
    {
        decimal += (octal_number % 10) * my_iterative_pow(8, index);
        index++;
        octal_number /= 10;
    }
    return decimal;
}

// custom memset
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