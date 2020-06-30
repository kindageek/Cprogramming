#include "my_tar.h"

// Function to write file/dir/link to tar archive
int write_to_tar(char* filename, int fd)
{
    int res = 0;
    header* hdr = get_header(filename);     // get header of a file
    if (hdr != NULL)
    {                                       // write only header if file is a link
        write(fd, hdr, BLOCKSIZE);          // write file header
        if (hdr->typeflag == REGTYPE)       // if it is a regular file
            write_file(fd, filename);       // write file content
        else if (hdr->typeflag == DIRTYPE)  // if it is a directory
            write_dir(fd, filename);        // write dir content
        free(hdr);                          // free header
    }
    else
    {
        res += 1;                           // else increment the returning result
    }
    return res;
}

// Function to write file content to tar archive
int write_file(int fd, char* filename)
{
    int res = 0;

    int fd_file = open(filename, O_RDONLY);     // get file descriptor
    int file_size = get_file_size(fd_file);     // get file size

    char content[file_size];                    // init content array
    my_bzero(content, file_size);               // fill with zeros

    read(fd_file, content, file_size);          // read file content
    write(fd, content, file_size);              // write file content to tar archive

    close(fd_file);                             // close the file
    return res;
}

// Function to get new path of a file with its parent directory
// parent/child
char* get_new_path(char* parent, char* child)
{
    char* path = malloc(strlen(parent) + strlen(child) + 1);
    strcpy(path, parent);
    strcat(path, "/");
    strcat(path, child);
    return path;
}

// Function to write directory content to tar archive
int write_dir(int fd, char* dirname)
{
    int res = 0;
    DIR* dir = opendir(dirname);                                                // open directory
    struct dirent* sd;
    char* path;
    while ((sd = readdir(dir)) != NULL)                                         // read dir files one by one
    {
        if (strcmp(sd->d_name, ".") != 0 && strcmp(sd->d_name, "..") != 0)      // check if its not current or parent dirs
        {
            path = get_new_path(dirname, sd->d_name);                           // get full path of file
            res += write_to_tar(path, fd);                                      // write file/dir to tar
            free(path);                                                         // free new path
        }
    }
    closedir(dir);                                                              // close the directory
    return res;
}