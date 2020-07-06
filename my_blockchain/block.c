#include "header.h"

// Function to initialize head block of a node in blockchain
block* init_blocks()
{
    block* head = (block*)malloc(sizeof(block));                // init head block of a node
    if(!head)                                                   // check if memory is allocated
    {
        free(head);
        write(1, NO_RESOURSE, strlen(NO_RESOURSE));
        return NULL;
    }
    head->bid = NULL;
    head->nid = NULL_HEAD;
    head->next = NULL;
    return head;
}

// Function to check if a block with given bid and nid exists in the blockchain
bool exists_block(node* head, char* bid, int nid)
{
    if (!head || head->nid == NULL_HEAD) return false;
    node* current = head;
    block* current_block;
    while (current && current->nid != NULL_HEAD)
    {
        current_block = current->block;
        while (current_block && current_block->bid)
        {
            if (strcmp(current_block->bid, bid) == 0 && current_block->nid == nid) return true;
            current_block = current_block->next;
        }
        current = current->next;
    }
    return false;
}

// Function to add a block to the node with the given nid
void add_block(node** head, char* bid, int nid)
{
    node* current_node = *head;
    if(!current_node || current_node->nid == NULL_HEAD)          // if head is null
    {
        write(1, NO_NODES, strlen(NO_NODES));
        return;
    }

    if (exists_block(*head, bid, nid))                           // check if given block exists
    {
        write(1, BLOCK_EXISTS, strlen(BLOCK_EXISTS));
    }
    else
    {
        while (current_node && current_node->nid != nid)
        {
            current_node = current_node->next;
        }
        if (!current_node)
        {
            write(1, NODE_NOT_EXISTS, strlen(NODE_NOT_EXISTS));
            return;
        }
        if (current_node->block == NULL) current_node->block = init_blocks();
        block* current_block = current_node->block;
        block* tmp;
        if (current_block->nid == NULL_HEAD)                     // if the block is a head(null) block
        {
            current_block->bid = strdup(bid);
            current_block->nid = current_node->nid;
        }
        else
        {
            do{
                tmp = current_block;
                current_block = current_block->next;
            }while (current_block);                              // get to the last block

            block* newBlock = (block*)malloc(sizeof(block));     // create new block
            if (!newBlock)
            {
                free(newBlock);
                write(1, NO_RESOURSE, strlen(NO_RESOURSE));
                return;
            }
            newBlock->bid = strdup(bid);
            newBlock->nid = current_node->nid;
            newBlock->next = NULL;
            tmp->next = newBlock;
        }
    }
}

// Function to remove a block from the blockchain
void remove_block(node** head, char* bid)
{
    node* current = *head;
    if(!current || current->nid == NULL_HEAD)
    {
        write(1, NO_NODES, strlen(NO_NODES));
        return;
    }
    int counter = 0;
    while (current && current->nid != NULL_HEAD)
    {
        if (exists_block(*head, bid, current->nid)) counter++;
        if (counter > 0) break;
        current = current->next;
    }
    if (counter == 0)                                               // if there is no block with the given bid
    {
        write(1, BLOCK_NOT_EXISTS, strlen(BLOCK_NOT_EXISTS));
        return;
    }
    current = *head;
    block* current_block;
    block* prev_block;
    while (current && current->nid != NULL_HEAD)
    {
        current_block = current->block;
        if (current_block->nid != NULL_HEAD)                    // if node has no block
        {
            if (strcmp(current_block->bid, bid) == 0)           // if it is the head block
            {
                current->block = current_block->next;
                free(current_block->bid);
                free(current_block);
            }
            else
            {            
                while (current_block && current_block->bid)
                {
                    if (strcmp(current_block->bid, bid) == 0)
                    {
                        prev_block->next = current_block->next;
                        free(current_block->bid);
                        free(current_block);
                    }
                    prev_block = current_block;
                    current_block = current_block->next;
                }
            }
        }
        current = current->next;
    }
}

// Function to free all the blocks of a node
void free_blocks(block** head)
{
    block* current = *head;
    block* prev;
    while (current)
    {
        free(current->bid);
        prev = current;
        current = current->next;
        free(prev);
    }
}

// Function to print the bid of the blocks of a node for "ls -l" command
void print_block(block* current)
{
    if (!current || !current->bid)
    {
        printf("no blocks\n");
    }
    else 
    {
        while (current && current->bid)
        {
            printf("%s", current->bid);
            if(current->next) printf(", ");
            current = current->next;
        }
        printf("\n");
    }
}