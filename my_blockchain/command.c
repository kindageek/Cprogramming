#include "header.h"

// Function to start the blockchain
void start(node** head)
{
    char* command;                                                      // container for a command line
    prompt_line(*head);                                                 // prompt to terminal
    while ((command = my_readline(0)) != NULL)                          // loop until "quit" command or NULL
    {
        if (!parse_command(head, command)) break;                       // parse command and break the loop if command is "quit"          
        prompt_line(*head);                                             // prompt to terminal
        free(command);
    }
    free(command);
}

// Function to handle "add" command
void command_add(node** head, string_array* words)
{
    int nid;
    if (words->size < 3)
    {
        write(1, NOT_ENOUGH_ARGS, strlen(NOT_ENOUGH_ARGS));
        return;
    }
    if (strcmp(words->array[1], "node") == 0)                           // if "add node ..."
    {
        if (words->size != 3)                                           // format is : "add node nid"
        {
            write(1, NOT_ENOUGH_ARGS, strlen(NOT_ENOUGH_ARGS));
        }
        else 
        {
            nid = my_atoi(words->array[2], strlen(words->array[2]));    // get node id by covnerting string to decimal
            add_node(head, nid);                                        // add node to the blockchain
        }
    }
    else if (strcmp(words->array[1], "block") == 0)                     // if "add block ..."
    {
        if (words->size != 4)                                           // format is : "add block bid nid"
        {
            write(1, NOT_ENOUGH_ARGS, strlen(NOT_ENOUGH_ARGS));
        }
        else 
        {
            if (strcmp(words->array[3], "*") == 0)                      // if "add block bid *"
            {
                node* current = *head;
                while (current && current->nid != NULL_HEAD)            // traverse all nodes
                {
                    nid = current->nid;                                 // get node id
                    add_block(head, words->array[2], nid);              // add block to all nodes one by one
                    current = current->next;
                }
            }
            else                                                        // if "add block bid nid"
            {
                nid = my_atoi(words->array[3], strlen(words->array[3])); // get node id by covnerting string to decimal
                add_block(head, words->array[2], nid);                  // add block to the blockchain
            }
        }
    }
    else                                                                // if "add [unknown word] ..."
    {
        write(1, UNKNOWN, strlen(UNKNOWN));
    }
}

// Function to handle "rm" command
void command_rm(node** head, string_array* words)
{
    if (words->size < 3)
    {
        write(1, NOT_ENOUGH_ARGS, strlen(NOT_ENOUGH_ARGS));
        return;
    }
    int nid;
    if (strcmp(words->array[1], "node") == 0)                           // if "rm node ..."
    {
        if (strcmp(words->array[2], "*") == 0)                          // if "rm node *"
        {
            node* current = *head;
            *head = NULL;                                               // set head to null
            free_node(&current);                                        // free the memory
        }
        else                                                            // if "rm node nid"
        {
            nid = my_atoi(words->array[2], strlen(words->array[2]));
            remove_node(head, nid);
        }
    }
    else if (strcmp(words->array[1], "block") == 0)                     // if "rm block ..."
    {
        if (strcmp(words->array[2], "*") == 0)                          // if "rm block *"
        {
            node* current = *head;                                      
            block* current_block;
            while (current && current->nid != NULL_HEAD)
            {
                current_block = current->block;
                current->block = NULL;
                free_blocks(&current_block);
                current = current->next;
            }
        }
        else                                                            // if "rm block bid"
        {
            remove_block(head, words->array[2]);
        }
    }
    else                                                                // if "rm [unknown word]"
    {
        write(1, UNKNOWN, strlen(UNKNOWN));
    }
}

// Function to handle add/rm commands
void add_rm(node** head, char* command)
{
    string_array* words = my_split(command, " ");
    if (strcmp(words->array[0], "add") == 0)                            // if "add ..."
    {
        command_add(head, words);
    }
    else if (strcmp(words->array[0], "rm") == 0)                        // if "rm ..."
    {
        command_rm(head, words);
    }
    else
    {
        write(1, UNKNOWN, strlen(UNKNOWN));
    }
    free_string_array(words);                                           // free the array of strings
}

// Function to parse the command and call corresponding functions
bool parse_command(node** head, char* command)
{
    if (strcmp(command, QUIT) == 0)                                     // "quit" command
    {
        save_data(*head);                                            // save all data to data.txt
        return false;
    }
    else if (strcmp(command, SYNC) == 0)                                // "sync" command
    {
        sync_nodes(head);                                               // synchronize all nodes
    }
    else if (strcmp(command, LIST) == 0)                                // "ls" command
    {
        print_nodes(*head, false);                                      // print all nodes
    }
    else if (strcmp(command, LIST_L) == 0)                              // "ls -l" command
    {
        print_nodes(*head, true);                                       // print all nodes with blocks
    }
    else 
    {
        add_rm(head, command);                                          // handle add/rm commands
    }
    return true;
}