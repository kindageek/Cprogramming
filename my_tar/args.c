#include "my_tar.h"

// initialize the head of linked list of arguments
tar_arg* init_args()
{
    tar_arg* head = (tar_arg*)malloc(sizeof(tar_arg));
    head->filename = NULL;
    head->next = NULL;

    return head;
}

// add filename to the linked list
void add_to_list(tar_arg** args, char* filename)
{
    tar_arg* tmp;
    tar_arg* current = *args;
    
    // add to the head if linked list is empty
    if(current->filename == NULL){
        current->filename = strdup(filename);
        return;
    }

    // go to the end of the linked list
    do {
		tmp = current;
		current = current->next;
	} while (current);

    // create new node and assign
    tar_arg* new_node = (tar_arg*)malloc(sizeof(tar_arg));
    new_node->filename = strdup(filename);
    new_node->next = NULL;

    tmp->next = new_node;
}


// free the memory allocated for the linked list and its nodes
void reset_args(tar_arg** args)
{
    tar_arg* current = *args;
    if(current->filename == NULL){
        free(current);
        return;
    }
    tar_arg* prev;
    while(current && current->filename != NULL){
        free(current->filename);
        prev = current;
        current = current->next;
        free(prev);
    }
}

// Function to check if given filename is in linked list
bool in_args(char* filename, tar_arg** args)
{
    tar_arg* current = *args;
    if(current->filename == NULL) return false;

    while(current && current->filename != NULL){
        if(strcmp(current->filename, filename) == 0)
            return true;
        current = current->next;
    }

    return false;
}