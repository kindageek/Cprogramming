#include "my_tar.h"

void print_opt(tar_options* opt)
{
    printf("==========================\n\n");
    printf("Creation:       %s\n", opt->create ? "True" : "False");
    printf("Extraction:     %s\n", opt->extract ? "True" : "False");
    printf("Archive name:   %s\n", opt->archive_name);

    tar_arg* current = opt->args;
    int index = 0;

    while(current && current->filename != NULL){
        printf("Argument %d:     %s\n", index, current->filename);
        current = current->next;
        index += 1;
    }

    printf("\n==========================\n");
    return;
}