#include "header.h"

#define READLINE_READ_SIZE 512

// Function to get the index of the start of the next line
int get_next_index(char* leftover, int* offset)
{
    int index = 0;
    while (leftover[index] != '\0')
    {
        if (leftover[index] == '\n')
        {
            break;
        }
        else if (leftover[index] == '\\' && leftover[++index] == 'n')
        {
            *offset = 1;
            break;
        }
        index++;
    }
    return index;
}

// Function to read from the fd and return the content
char* get_next_content(int fd)
{
    char* content = (char*)malloc(sizeof(char) * (READLINE_READ_SIZE + 1));
    // my_bzero(content, strlen(content));
    read(fd, content, READLINE_READ_SIZE);
    content[READLINE_READ_SIZE] = '\0';
    return content;
}

// Function to move the leftover string after getting a line
// Example: before -> leftover = "First line\nSecond line"
//          after  -> leftover = "Second line"
void move_string(char* leftover, int index, int offset)
{
    char* buff = (char*)malloc(strlen(leftover) - index + offset);
    my_bzero(buff, strlen(buff));
    strcpy(buff, &leftover[index+offset]);
    my_bzero(leftover, strlen(leftover));
    if (buff[0] == '\n')
    {
        if (strlen(buff) == 1)
        {
            free(buff);
            my_bzero(leftover, strlen(leftover));
            return;
        }
        else
        {
            buff += 1;
        }
    }
    strcpy(leftover, buff);
    free(buff);
}

// my_readline function to read from fd and return the content line by line
char* my_readline(int fd)
{
    if (fd < 0) return NULL;
    static char leftover[READLINE_READ_SIZE + 1];               // static variable to save leftover content
    char* content = get_next_content(fd);                       // read READLINE_READ_SIZE bytes of content from the fd
    strcat(leftover, content);                                  // append the leftover with content
    free(content);
    if (leftover[0] == '\n')                                     // if the first line is empty, move to the second line
    {
        move_string(leftover, 1, 0);
    }
    else if (strlen(leftover) == 0)                              // if the content from fd is empty, return NULL
    {
        free(content);
        return NULL;
    }
    
    unsigned int index = 0;
    int offset = 0;                                             // offset is needed if there are symbols "\n" in the text
                                                                // because it is two spaces, rather than one space in case of '\n'
    index = get_next_index(leftover, &offset);                  // get end-line index and offset

    if (index >= strlen(leftover) && leftover[index] != EOF)     // if READLINE_READ_SIZE is less than the length of a line
    {
        while (index >= strlen(leftover))                        // read from the fd until getting the whole line
        {
            content = get_next_content(fd);
            if (strlen(content) == 0)                            // if content is empty it means EOF is reached
            {
                free(content);
                break;
            }
            strcat(leftover, content);                          // append content to leftover
            index = get_next_index(leftover, &offset);          // get enf-line index
            free(content);
        }
    }

    char* line = malloc(sizeof(char) * (index + 1 - offset));   // init a line string
    strncpy(line, leftover, index - offset);                    // copy first n(index-offset) characters from leftover to line

    move_string(leftover, index, offset);                       // move leftover
    free(content);
    if (strlen(line) == 0) free(line);                           // if line is empty, free the memory
    return line;
    // return strlen(line) > 0 ? line : NULL;                      // return line if it is not empty, else return NULL
}