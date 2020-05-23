#include <stdio.h>
#include <string.h>
#include <stdarg.h>
#include <unistd.h>
#include <stdlib.h>

int my_printf(char * restrict format, ...);             //implementation of printf()
void my_putchar(char ch);                               //implementation of putchar()
void my_putstr(char *str);                              //implementation of putstr()
char* my_itoa(int val, int base);                       //implementation of itoa()
char* my_reverse(char* ptr);                            //implementation of string reversing function
char* my_ultoa(unsigned long value, int base);          //implementation of ultoa()
void checkFormat(char* restrict format);                //function to check for unauthorised specifiers
int my_strlen(const char* a);                           //custom strlen


int main(){
    //any tests
    return 0;
}

/*
* Implementation of printf()
* Returns the length of the final string
*/
int my_printf(char * restrict format, ...){
    checkFormat(format);                                        //check if there is any unauthorised specifiers other than 'douxscp%'
    va_list args;                                               //declare va_list
    va_start(args, format);                                     //declare va_start

    int i = 0;
    int length = 0;                                             //length of the final string which the function returns
    unsigned int intVal;                                        //variable to save integer values
    char* strVal;                                               //variable to save char* values
    void* voidPtr;                                              //variable to save address

    while(format[i] != '\0'){                                   //iterate the char* format
        if(format[i] == '%'){                                   //look for '%' of the specifier
            i++;                                                //look for the specifier character
            switch (format[i]){
                case 'd':                                       //if specifier is %d
                    intVal = va_arg(args, int);                 //get int type argument
                    strVal = my_itoa(intVal, 10);               //convert to string with base 10
                    my_putstr(strVal);                          //print it to stdout
                    length += my_strlen(strVal);                   //append length
                    break;
                
                case 'o':                                       //if specifier is %o
                    intVal = va_arg(args, int);                 //get int type argument
                    strVal = my_itoa(intVal, 8);                //convert to string with base 8
                    my_putstr(strVal);                          //print it to stdout
                    length += my_strlen(strVal);                   //append length
                    break;

                case 'u':                                       //if specifier is %u
                    intVal = (unsigned int)va_arg(args, int);   //get unsigned int type argument
                    strVal = my_itoa(intVal, 10);               //convert to string with base 10
                    my_putstr(strVal);                          //print it to stdout
                    length += my_strlen(strVal);                   //append length
                    break;
                
                case 'x':                                       //if specifier is %x
                    intVal = va_arg(args, int);                 //get int type argument
                    strVal = my_itoa(intVal, 16);               //convert to string with base 16
                    my_putstr(strVal);                          //print it to stdout
                    length += my_strlen(strVal);                   //append length
                    break;

                case 's':                                       //if specifier is %s
                    strVal = va_arg(args, char*);               //get char* type argument
                    if(strVal == NULL){
                        my_putstr("(null)");
                        length += 6;
                    }else{
                        my_putstr(strVal);                      //print it to stdout
                        length += my_strlen(strVal);               //append length
                    }
                    break;
                
                case 'c':                                       //if specifier is %c
                    intVal = va_arg(args, int);                 //get int type argument
                    my_putchar(intVal);                         //print it to stdout
                    length++;                                   //append length
                    break;
                
                case 'p':                                               //if specifier is %p
                    voidPtr = va_arg(args, void*);                      //get void* type argument
                    unsigned long longVal = (unsigned long)voidPtr;     //cast it to unsigned long variable
                    strVal = my_ultoa(longVal, 16);                     //convert to string with base 16
                    my_putstr("0x");                                    //print this
                    my_putstr(strVal);                                  //print it to stdout
                    length += my_strlen(strVal);                           //append length
                    break;
                
                case '%':                                       //if specifier is just '%%'
                    my_putchar('%');                            //print '%'
                    length += 1;                                //append length
                    break;

                default:                                                 //if none of the above
                    my_putstr("Error: Invalid conversion specifier");    //print error message
                    return -1;                                           //return
                    break;
            }
        }
        else if(format[i] == '\\'){                             //if there is '\' character, which can be either \n, \t, \" or '\\'
            i++;                                                //get the next character
            switch (format[i]){                                 //check that character
                case 'n':                                       //if it is \n
                    write(1,"\n", 0);                           //print new line but do not append length
                    break;

                case 't':                                       //if it is \t
                    write(1, "    ", 4);                        //print four spaces(one tab == four spaces)
                    length+=4;                                  //append length
                    break;

                case '"':                                       //if it is \"
                    my_putchar(format[i]);                      //print it
                    length++;                                   //append length
                    break;
                
                case '\\':                                      //if it is '\\'
                    my_putchar(format[i]);                      //print it
                    length++;                                   //append length
                    break;
                
                default:                                        //if it is none of the above
                    my_putchar('\\');                           //print '\'
                    my_putchar(format[i]);                      //print that character
                    length+=2;                                  //append length
                    break;
            }
        }
        else{
            my_putchar(format[i]);                              //if element is just a character, print it
            length++;                                           //append length
        }
        i++;                                                    //continue iteration
    }

    va_end(args);                                               //finish va_list
    return length;                                              //return length
}


/*
 * Function to check the string and 
 * look for invalid specifiers other than 'd o u x s c p %'
 */
void checkFormat(char* restrict format){
    int i = 0;
    while(format && format[i] != '\0'){                                 //iterate through the string
        if(format[i] == '%'){                                           //look for '%'
            i++;                                                        //cheack next character
            if(format[i] != 'd' && format[i] != 'o' 
                && format[i] != 'u' && format[i] != 'x' 
                && format[i] != 's' && format[i] != 'c' 
                && format[i] != 'p' && format[i] != '%'){
                    my_putstr("Error: Invalid conversion specifier");   //if it is not the specifier, prompt error
                    return;                                             //return
                }
        }
        i++;
    }
}

/*
* Function to print one char at a time to stdout
*/
void my_putchar(char ch){
    write(1, &ch, 1);
}

/*
* Function to print char* string to strdout by printing every character with my_putchar()
*/
void my_putstr(char *str){
    for(int i = 0; i < my_strlen(str); i++){
        my_putchar(str[i]);
    }
}

/*
* Custom implementation of itoa() which converts integer to string with given base
*/
char* my_itoa(int val, int base){
    char* ptr = (char*)malloc(100);
    if(base < 2 || base > 16) return ptr;
    
    int num, i = 0;

    if(val < 0) num = -val;
    else num = val;
    
    if(num == 0){
        ptr[i++] = '0';
        ptr[i] = '\0';
        return ptr;
    }

    while(num != 0){
        int r = num % base;
        
        if(r >= 10)
            ptr[i] = 65 + (r - 10);
        else
            ptr[i] = 48 + r;
        
        num /= base;
        i++;
    }

    if(val < 0 && base == 10)
        ptr[i++] = '-';

    ptr[i] = '\0';

    return my_reverse(ptr);
}


/*
* Custom implementation of ultoa() which converts unsigned long to string with given base
*/
char* my_ultoa(unsigned long val, int base){
    char* ptr = (char*)malloc(100);
    unsigned long t = 0, res = 0;
    unsigned long tmp = val;
    int count = 0;

    if (tmp == 0)
        count++;

    while(tmp > 0){
        tmp = tmp/base;
        count++;
    }

    ptr += count;
    *ptr = '\0';

    do{
    res = val - base * (t = val / base);
        if (res < 10){
            * -- ptr = '0' + res;
        }else if ((res >= 10) && (res < 16)){
            * --ptr = 'A' - 10 + res;
        }
    } while ((val = t) != 0);

    return(ptr);
}


/*
* Function to reverse a string
*/
char* my_reverse(char* ptr){
    int len = my_strlen(ptr);
    if(len <= 1) return ptr;

    int i = len-1;  
    char s[len+1];  
    s[len]='\0';
    
    while(ptr && *ptr !='\0'){
        s[i] = *ptr;
        ptr++;
        i--;
    }
    
    return strdup(s);
}


/*
 * Custom strlen
 */
int my_strlen(const char* a){
    int counter = 0;
    while(a && *a != '\0'){
        counter++;
        a++;
    }
    return counter;
}