#include "header.h"

// Function to inititalize the head of nodes in blockchain
node* init_nodes()
{
    node* head = (node*)malloc(sizeof(node));               // init the first node in blockchain
    if (!head)                                              // if failed to alloc memory, return NULL
    {
        free(head);
        write(1, NO_RESOURSE, strlen(NO_RESOURSE));
        return NULL;
    }
    head->block = init_blocks();                            // init blocks of the node
    head->next = NULL;
    head->nid = NULL_HEAD;                                  // assign NULL_HEAD to head node id
    return head;
}

// Function to check if a node with given nid exists in the blockchain
bool exists_node(node** head, int nid)
{
    node* current = *head;
    if (!current || current->nid == NULL_HEAD) return false;            // it means no nodes in the blockchain
    while (current && current->nid != NULL_HEAD)
    {
        if (current->nid == nid) return true;
        current = current->next;
    }
    return false;
}

// Function to add a node to the blockchain
void add_node(node** head, int nid)
{
    if (exists_node(head, nid))                             // check if given node already exists
    {
        write(1, NODE_EXISTS, strlen(NODE_EXISTS));
    }
    else 
    {
        node* tmp;
        node* current = *head;

        if (current == NULL)                           // if head node is not malloced with init_nodes() and is empty
        {
            current = (node*)malloc(sizeof(node));
            if(!current)
            {
                free(current);
                write(1, NO_RESOURSE, strlen(NO_RESOURSE));
                return;
            }
            current->block = init_blocks();
            current->nid = nid;
            current->next = NULL;
            *head = current;
        }
        else if (current->nid == NULL_HEAD)                      // if head node is malloced but empty
        {
            current->nid = nid;
        }
        else
        {
            do{                                             // get to the last node
                tmp = current;
                current = current->next;
            }while (current);

            node* newNode = (node*)malloc(sizeof(node));    // create a new node
            if (!newNode)                                   // check if memory is allocated correctly
            {
                free(newNode);
                write(1, NO_RESOURSE, strlen(NO_RESOURSE));
                return;
            }
            newNode->nid = nid;
            newNode->block = init_blocks();                     
            newNode->next = NULL;
            tmp->next = newNode;
        }
    }
}

// Function to remove a node with given nid from the blockchain
void remove_node(node** head, int nid)
{
    node* current = *head;
    if(!current || current->nid == NULL_HEAD)
    {
        write(1, NO_NODES, strlen(NO_NODES));
        return;
    }
    if (!exists_node(head, nid))                            // check if given node doesn't exist in the blockchain
    {
        write(1, NODE_NOT_EXISTS, strlen(NODE_NOT_EXISTS));
    }
    else
    {
        if (current->nid == nid)                            // if given node is the head node
        {
            *head = current->next;                          // move the head
            free_blocks(&current->block);
            free(current);
        }
        else 
        {
            node* prev = current;
            while (current && current->nid != NULL_HEAD)    // traverse all nodes
            {
                if (current->nid == nid)
                {
                    prev->next = current->next;             // jump over the node
                    free_blocks(&current->block);
                    free(current);
                }
                prev = current;
                current = current->next;
            }
        }
    }
}

// function to free all the nodes in the blockchain
void free_node(node** head)
{
    node* current = *head;
    node* prev = NULL;
    while (current)
    {
        free_blocks(&current->block);
        prev = current;
        current = current->next;
        free(prev);
    }
}

// Function to print node id and its blocks 
void print_node(node* n, bool with_blocks)
{
    printf("%d", n->nid);
    if (!with_blocks)
    {
        printf("\n");
    }
    else
    {
        printf(": ");
        print_block(n->block);
    }
}

// Function to get the number of nodes in the blockchain
int get_size(node* head)
{
    if(!head || head->nid == NULL_HEAD) return 0;
    node* current = head;
    int size = 0;
    while (current)
    {
        size++;
        current = current->next;
    }
    return size;
}

// Function to print all the nodes with or without blocks for "ls/ls -l" commands
void print_nodes(node* head, bool with_blocks)
{
    if (!head || head->nid == NULL_HEAD)
    {
        write(1, NO_NODES, strlen(NO_NODES));
    }
    else 
    {
        node* current = head;
        while (current)
        {
            print_node(current, with_blocks);
            current = current->next;
        }
    }
}