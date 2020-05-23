#include "ls.h"     //Include custom heading "ls.h"

/*
 * Custom strcmp
 */
int my_strcmp(const char* a, const char* b) {
    while((*a!='\0' && *b!='\0') && *a==*b){
        a++;
        b++;
    }
    
    if(*a==*b) 
        return 0;
    else if(*a - *b > 0) 
        return 1;
    else 
        return -1;
}


/*
 * Custom strcpy
 */
const char* my_strcpy(char* a, const char* b) {
    if(b==NULL) return NULL;
    
    const char* ptr = a;
    while(*b!='\0'){
        *a++ = *b++;
    }

    *a='\0';
    return ptr;
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


/*
 * Custom strcat
 */
const char* my_strcat(char* a, const char* b){
    a = realloc(a, my_strlen(a) + my_strlen(b));
    while(a && *a != '\0') a++;

    while(b && *b != '\0'){
        *a++ = *b++;
    }
    *a = '\0';
    return a;
}