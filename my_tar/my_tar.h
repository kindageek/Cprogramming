#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

typedef struct arg
{
    char* filename;
    struct arg* next;
}arg;

typedef struct options
{
    bool create;
    bool extract;
    char *archive_name;
    struct arg *args;
}options;

options* get_opt(int ac, char** av);
void reset_options(options* opt);