#include "my_tar.h"

tar_arg* init_args()
{
    tar_arg* head = (tar_arg*)malloc(sizeof(tar_arg));
    head->filename = NULL;
    head->next = NULL;

    return head;
}


void add_to_list(tar_arg** args, char* filename)
{
    tar_arg* tmp;
    tar_arg* current = *args;

    if(current->filename == NULL){
        current->filename = strdup(filename);
        return;
    }

    do {
		tmp = current;
		current = current->next;
	} while (current);

    tar_arg* new = (tar_arg*)malloc(sizeof(tar_arg));
    new->filename = strdup(filename);
    new->next = NULL;

    tmp->next = new;
}


void reset_args(tar_arg** args)
{
    tar_arg* current = *args;
    while(current && current->filename != NULL){
        free(current->filename);
        current = current->next;
    }
}