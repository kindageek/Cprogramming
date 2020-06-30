#include "my_tar.h"

// print options [not necessary, just for checking that the program works]
void print_opt(tar_options* opt)
{
    printf("==========================\n\n");
    printf("Option [c]:  %s\n", opt->c ? "True" : "False");
    printf("Option [x]:  %s\n", opt->x ? "True" : "False");
    printf("Option [r]:  %s\n", opt->r ? "True" : "False");
    printf("Option [u]:  %s\n", opt->u ? "True" : "False");
    printf("Option [t]:  %s\n", opt->t ? "True" : "False");
    printf("Option [f]:  %s\n", opt->f ? "True" : "False");
    printf("Archv name:  %s\n", opt->archive_name);
    tar_arg* current = opt->args;
    int index = 0;
    while (current && current->filename != NULL)
    {
        printf("Argument %d:  %s\n", index, current->filename);
        current = current->next;
        index += 1;
    }
    printf("\n==========================\n");
    return;
}