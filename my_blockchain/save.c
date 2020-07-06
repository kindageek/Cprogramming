#include "header.h"

// Function to get line size
int get_line_size(node* current)
{
    char* nid_string = my_itoa(current->nid, DEC_BASE);
    int size = 1 + strlen(nid_string);
    if (current->block && current->block->bid) size++;
    block* current_block = current->block;
    while(current_block && current_block->bid)
    {
        size += strlen(current_block->bid);
        if (current_block->next) size++;
        current_block = current_block->next;
    }
    free(nid_string);
    return size;
}

// Function to get one line: nid bid bid ...
char* get_line(node* current, size_t nbytes)
{
    char* line = malloc(nbytes);
    char* nid_string = my_itoa(current->nid, DEC_BASE);
    strcpy(line, nid_string);
    if (current->block && current->block->bid) strcat(line, " ");
    block* current_block = current->block;
    while (current_block && current_block->bid)
    {
        strcat(line, current_block->bid);
        if (current_block->next) strcat(line, " ");
        current_block = current_block->next;
    }
    line[nbytes-1] = '\n';
    free(nid_string);
    return line;
}

// Function to write the blockchain data to the given file
void write_blockchain(int fd, node* head)
{
    if (!head || head->nid == NULL_HEAD) return;            
    node* current = head;
    char* line;
    size_t size;
    while (current && current->nid != NULL_HEAD)
    {
        size = get_line_size(current);                      
        line = get_line(current, size);
        write(fd, line, size);
        free(line);
        current = current->next;
    }
    free(line);
} 

// Function to save the blockchain data to backup.txt
void save_data(node* head)
{
    int fd = open("./backup.txt", O_WRONLY | O_TRUNC);
    write_blockchain(fd, head);
    close(fd);
}