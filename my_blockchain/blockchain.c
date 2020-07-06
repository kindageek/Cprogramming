#include <sys/wait.h>
#include "header.h"

// Function to check if two head blocks are equal(e.g. synced)
bool equal(block* first, block* second)
{
    block* block1 = first;
    block* block2 = second;
    if ((!block1 || !block1->bid) && (!block2 || !block2->bid)) return true;
    if (((!block1 || !block1->bid) && (block2 || block2->bid)) || ((block1 || block1->bid) && (!block2 || !block2->bid))) return false;
    if ((block1->nid == NULL_HEAD && block2->nid == NULL_HEAD)) return true;
    while ((block1 && block1->bid) && (block2 && block2->bid))
    {
        if (strcmp(block1->bid, block2->bid) != 0) return false;
        block1 = block1->next;
        block2 = block2->next;
    }
    if ((!block1 && block2) || (block1 && !block2)) return false;
    return true;
}

// Function to check if all the nodes are synced among each other
bool is_synced(node* head)
{
    if (get_size(head) <= 1) return true;               // if size is 0 or 1, the blockchain is synced
    node* current = head->next;                         // check all blocks with blocks of head node
    block* b = head->block;
    while (current && current->nid != NULL_HEAD)
    {
        if (!equal(b, current->block)) return false;    // if blocks of a node are not the same as blocks of head, blockchain is not synced
        current = current->next;
    }
    return true;
}

// Function to return list of all blocks from the blockchain nodes without duplicates
string_list* get_set_of_blocks(node* head)
{
    if (!head || head->nid == NULL_HEAD) return NULL;
    node* current = head;
    string_list* set_list = (string_list*)malloc(sizeof(string_list));
    set_list->name = NULL;
    set_list->next = NULL;
    block* current_block;

    while (current && current->nid != NULL_HEAD)
    {
        current_block = current->block;
        while (current_block && current_block->bid)
        {
            add_to_string_list(&set_list, current_block->bid);
            current_block = current_block->next;
        }
        current = current->next;
    }
    return set_list;
}

// Function to sync all nodes
void sync_nodes(node** head)
{
    node* current = *head;
    if(!current || current->nid == NULL_HEAD)
    {
        write(1, NO_NODES, strlen(NO_NODES));
        return;
    }
    string_list* list = get_set_of_blocks(*head);
    string_list* list_node;
    while (current)
    {
        free_blocks(&current->block);
        current->block = init_blocks();
        list_node = list;
        while (list_node && list_node->name)
        {
            add_block(head, list_node->name, current->nid);
            list_node = list_node->next;
        }
        current = current->next;
    }
    free_string_list(list);
}