#include "my_tar.h"

// Function to open archive with specific modes and flags
int open_archive(tar_options* opt)
{
    int fd, flags;
    const mode_t mode = S_IRUSR | S_IWUSR | S_IRGRP | S_IROTH;

    if (opt->c)                                 // if creation
        flags = O_CREAT | O_WRONLY | O_TRUNC;
    else if (opt->x || opt->t)                  // extraction
        flags = O_RDONLY;   
    else if (opt->r)                            // append
        flags = O_WRONLY | O_APPEND;
    else if (opt->u)                            // update
        flags = O_RDWR;
    
    fd = open(opt->archive_name, flags, mode);  // open tar file
    return fd;
}

// Function to end archive with two BLOCKSIZE empty blocks
void end_archive(int fd)
{
    char end[BLOCKSIZE * 2];
    my_bzero(end, BLOCKSIZE * 2);
    write(fd, end, BLOCKSIZE * 2); 
}

// Function to calculate file size as a multiple of BLOCKSIZE
int get_file_size(int fd)
{
    int res = 0, reader = 0;
    char buffer[BLOCKSIZE];

    while((reader = read(fd, buffer, BLOCKSIZE)) > 0){  // Calculate file size
        res += reader;
    }

    if(res % BLOCKSIZE != 0){                           // if it is not a multiple of BLOCKSIZE
        res += BLOCKSIZE - (res % BLOCKSIZE);           // add sufficient amount
    }

    lseek(fd, 0, SEEK_SET);                             // move reader to the start of the file
    return res;
}

// Function to get the size of archive file
int get_archive_size(char* filename)
{
    struct stat info;
    if(stat(filename, &info) < 0)
       return -1; 
    return info.st_size;
}

// Function to get the content of an archive file
char* get_archive_content(int fd, int size)
{   
    char* content = malloc(size * sizeof(char)+1);
    read(fd, content, size);
    return content;
}