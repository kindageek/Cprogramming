# include "ls.h"

// Function to check if given argument is option starting with '-'
bool is_option(const char* arg)
{
    return arg[0] == '-';
}

// Function to parse the option list
int get_options(const char* arg, bool* r, bool* a, bool* t)
{
    char* option = (char*)(arg + 1);                                      // get the pointer for the option character
    while (*option != '\0')
    {                                                 // iterate through options
        if (*option == 'R')
        {
            *r = true;                                                       // if there is option "R", modify its identifier to 1
        }
        else if (*option == 'a')
        {
            *a = true;                                                       // if there is option "a", modify its identifier to 1
        }
        else if (*option == 't')
        {
            *t = true;                                                       // if there is option "t", modify its identifier to 1
        }
        else
        {                                                  
            printf(INVALID_OPT, *option);              // if there is unidentified option, prompt for error and return
            printf(TRY_HELP);
            return -1;
        }
        option++;                                                           // continue iteration
    }
    return 0;
}