#include "my_tar.h"

// Function to append tar archive with files
int append_archive(int fd, tar_options* opt)
{
    int res = 0;
    tar_arg* current = opt->args;                       // head of linked list of filenames
    while (current)
    {
        res += write_to_tar(current->filename, fd);     // write file to tar 
        current = current->next;
    }
    end_archive(fd);                                    // end archive with two BLOCKSIZE blocks
    return res;
}