#include "my_tar.h"

int open_archive(tar_options* opt)
{
    int fd, flags;
    const mode_t mode = S_IRUSR | S_IWUSR | S_IRGRP | S_IROTH;

    if (opt->c)
        flags = O_CREAT | O_WRONLY | O_TRUNC;
    else if (opt->x)
        flags = O_RDONLY;
    
    fd = open(opt->archive_name, flags, mode);
    
    return fd;
}

char get_typeflag(int mode)
{
    switch(mode & S_IFMT){
        case S_IFREG:
            return REGTYPE;
        case S_IFLNK:
            return SYMTYPE;
        case S_IFCHR:
            return CHRTYPE;
        case S_IFBLK:
            return BLKTYPE;      
        case S_IFDIR:
            return DIRTYPE;
        case S_IFIFO:
            return FIFOTYPE;
        default:
            return REGTYPE;
    }
    
}

header* get_header(char* filename)
{
    header* header = malloc(BLOCKSIZE);
    my_bzero(header, BLOCKSIZE);

    struct stat info;
    if(stat(filename, &info) < 0){
        return NULL;
    }

    strncpy(header->name, filename, 100);
    my_itoa_base(header->size, info.st_size, 12, OCTAL_BASE);
    my_itoa_base(header->mtime, info.st_mtime, 12, OCTAL_BASE);
    header->typeflag = get_typeflag(info.st_mode);


    return header;
}

// int write_file(int fd, char* filename)
// { 
// }

int create_archive(int fd, tar_options* opt)
{
    int res = 0;
    tar_arg* current = opt->args;
    header* header;

    while(current){
        header = get_header(current->filename);
        if(header != NULL){
            write(fd, header, BLOCKSIZE);
            // write_file(fd, current->filename);
            // free(header);
        }else{
            res += 1;
        }
        current = current->next;
    }
    return res;
}