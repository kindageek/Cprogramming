#include "header.h"

// Function to load the backup data to the blockchain
// The backup is stored in the following format:    nid1 bid1 bid2 ...
//                                                  nid2 bid1 bid2 ...
node* load_data()
{
    int fd = open("./backup.txt", O_RDONLY);                          // open the backup file
    node* head = init_nodes();                                      // init head node
    if (!head) return NULL;
    string_array* words;                                            // array to store the words of a line
    char* line;
    int nid;
    while ((line = my_readline(fd)) != NULL)                        // use my_readline to get line by line
    {
        words = my_split(line, " ");                                // split the line into words
        nid = my_atoi(words->array[0], strlen(words->array[0]));    // convert first word to decimal
        add_node(&head, nid);                                       // add a node with the given nid
        if(words->size != 1)                                        // if there's more than one word in the line
        {
            for (int i = 1; i < words->size; i++)                   // get words starting from the second one
            {
                add_block(&head, words->array[i], nid);             // add the blocks one by one
            }
        }
        free(line);                                                 // free the line
        free_string_array(words);                                   // free the array
    }
    close(fd);                                                      // close the file
    return head;                                                    // return head node of the blockchain
}