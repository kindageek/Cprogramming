#include "header.h"

// Function to check if given string is in linked list
bool exists_in_list(string_list* list, char* word)
{
    string_list* current = list;
    while (current && current->name)
    {
        if(strcmp(current->name, word) == 0) return true;
        current = current->next;
    }
    return false;
}

// Function to add new node to linked list
void add_to_string_list(string_list** list, char* word)
{
    if(exists_in_list(*list, word)) return;
    string_list* current = *list;
    if (!current->name)
    {
        current->name = strdup(word);
        return;
    }
    string_list* tmp;
    do {
		tmp = current;
		current = current->next;
	} while (current);

    string_list* new_node = (string_list*)malloc(sizeof(string_list));
    new_node->name = strdup(word);
    new_node->next = NULL;
    tmp->next = new_node;
}

// Function to get size of the linked list
int get_list_size(string_list* list)
{
    string_list* current = list;
    int size = 0;
    while (current && current->name)
    {
        size++;
        current = current->next;
    }
    return size;
}

// Function to free the memory of linked list
void free_string_list(string_list* list)
{
    string_list* current = list;
    string_list* prev;
    while (current)
    {
        free(current->name);
        prev = current;
        current = current->next;
        free(prev);
    }
}

// Function to print linked list
void print_list(string_list* list)
{
    printf("List: ");
    string_list* current = list;
    while (current && current->name)
    {
        printf("%s", current->name);
        if(current->next) printf(", ");
        else printf("\n");
        current = current->next;
    }
}