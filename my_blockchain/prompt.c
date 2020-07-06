#include "header.h"

// Function to get the string which will be prompt to stdout
char* get_prompt(bool synced, int size)
{
    char* size_string = my_itoa(size, DEC_BASE);                    // get the string version of integer size
    char* prompt = malloc(strlen(size_string) + 6);                 // create prompt string
    strcpy(prompt, "[");                                            // prompt = "["
    strcat(prompt, synced ? "s" : "-");                             // prompt = "[s"
    strcat(prompt, size_string);                                    // prompt = "[s3"
    strcat(prompt, "]> ");                                          // prompt = "[s3]> "
    prompt[strlen(prompt)] = '\0';                                  // end the string
    free(size_string);
    return prompt;
}

// Function to prompt a line to the terminal
// with synced and size values
void prompt_line(node* head)
{
    bool synced = is_synced(head);                                  // check if nodes are synced
    int size = get_size(head);                                      // get new size of blockchain                                           
    char* prompt = get_prompt(synced, size);                        // get the prompt string
    write(1, prompt, strlen(prompt));                               // write the prompt string to stdout
    free(prompt);
}