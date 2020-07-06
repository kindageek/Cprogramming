#include "header.h"

int main()
{
    node* head = load_data();                                       // load data from data.txt
    if(!head) return 1;                                             // if failed to allocate memory to the head
    start(&head);                                                   // start the program
    free_node(&head);                                               // free the memory allocated to the blockchain
    return 0;
}