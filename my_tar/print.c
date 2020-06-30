#include "my_tar.h"


// Function for -t option of my_tar
// Print the names of the files inside the tar archive
int print_archive(int fd, tar_options* opt)
{
    int size = get_archive_size(opt->archive_name);             // archive size
    char* content = get_archive_content(fd, size);              // archive content
    int index = 0;                                              // index of a header                                    
    int filesize = 0;                                           // file size of a file inside tar
    int offset = 0;                                             // offset of the file size, because it is not multiple of 512
    header* hdr;                                                // header pointer
    while (index < size)
    {
        hdr = (header*)&content[index];                         // get header from content by casting, first header is at index 0 always
        if (strlen(hdr->name) != 0) printf("%s\n", hdr->name);  // if there is header and it is not empty, print header->name
        if (hdr->typeflag != SYMTYPE)                           // if file in tar is not a symlink
        {
            filesize = get_header_size(hdr);                    // get file size from header
            offset = BLOCKSIZE - (filesize % 512);              // calculate offset
        }
        else                                                    // if it is a symlink
        {
            filesize = 0;
            offset = 0;
        }
        index += BLOCKSIZE + filesize + offset;                 // increment index
        free(hdr);
    }
    return 0;                                                   // return result
}