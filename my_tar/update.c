#include "my_tar.h"

// Function to get mtime of file using stat
unsigned long get_file_mtime(char* filename)
{
    struct stat file_info;
    stat(filename, &file_info);
    return (unsigned long)file_info.st_mtim.tv_sec;
}

// Function to update the tar archive with files
// by checking the mtimes of corresponding files
int update_archive(int fd, tar_options* opt)
{
    int res = 0;
    int size = get_archive_size(opt->archive_name);     // get archive size
    char* content = get_archive_content(fd, size);      // get archive content
    int index = 0;                                      // index of a header      
    int filesize = 0;                                   // file size of a file inside tar
    int offset = 0;                                     // offset of the file size, because it is not multiple of 512
    unsigned long mtime_in_tar, mtime_of_file;          // modification times for file and its corresponding entry in tar
    header* hdr;
    while (index < size)
    {
        hdr = (header*)&content[index];                 // get header from content by casting, first header is at index 0 always
        if (in_args(hdr->name, &opt->args))             // if header->name, e.g. filename is in arguments
        {
            mtime_in_tar = get_header_mtime(hdr);       // get mtime from header
            mtime_of_file = get_file_mtime(hdr->name);  // get mtime of the file

            if (mtime_in_tar < mtime_of_file)           // compare them
            {
                res += write_to_tar(hdr->name, fd);     // write file to tar
            }
        }
        else
        {
            res += 1;                                   // increment returning result
        }

        if (hdr->typeflag != SYMTYPE)                   // if file in tar is not a symlink
        {
            filesize = get_header_size(hdr);            // get file size from header
            offset = BLOCKSIZE - (filesize % 512);      // calculate offset
        }
        else                                            // if it is a symlink
        {
            filesize = 0;
            offset = 0;
        }
        index += BLOCKSIZE + filesize + offset;         // increment index
        free(hdr);                                      // free header
    }   
    free(content);                                      // free content
    return res;
}