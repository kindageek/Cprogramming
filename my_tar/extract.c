#include <fcntl.h>
#include "my_tar.h"

// Function to calculate checksum of the header
// to compare with header->chksum afterwards
unsigned int find_chksum(header* hdr)
{
    if (get_header_chksum(hdr) <= 0) return 0;
    unsigned int sum = 0;
    char hdr_chksum[8];
    strcpy(hdr_chksum, hdr->chksum);
    my_memset(hdr->chksum, ' ', 7);
    char* headerBytes = (char*)hdr;
    for (int i = 0; i < BLOCKSIZE; ++i)
    {
        sum += headerBytes[i];
    }
    strcpy(hdr->chksum, hdr_chksum);
    return sum;
}

// Function to set mtime to a file after its extraction
int set_mtime(header* hdr)
{
    unsigned long m_time_of_file = my_atoi(hdr->mtime, 12);
    struct utimbuf time_buf;
    time_buf.modtime = my_oct_to_dec(m_time_of_file);
    time_buf.actime = time(NULL);
    return utime(hdr->name, &time_buf);
}

// Function to extract file from archive
int extract_file(header* hdr, char* archive_content)
{
    char* f_content = archive_content + BLOCKSIZE;
    // printf("Archive content:\n%s\n", archive_content);
    // printf("Content: %s\n", f_content);
    int f_size = get_header_size(hdr);
    int mode = get_header_mode(hdr);
    int fd = open(hdr->name, O_WRONLY | O_CREAT, mode);
    write(fd, f_content, f_size);
    close(fd);
    set_mtime(hdr);
    int offset = BLOCKSIZE - (f_size % 512);
    return BLOCKSIZE + f_size + offset;
}

// Function to extract directory from archive
int extract_directory(header* hdr)
{
    int mode = get_header_mode(hdr);
    mkdir(hdr->name, mode);
    set_mtime(hdr);
    return BLOCKSIZE;
}

// Function to extract symlink from archive
int extract_symlink(header* hdr)
{
    symlink(hdr->linkname, hdr->name);
    set_mtime(hdr);
    return BLOCKSIZE;
}

// Function to extract files/dirs/symlinks from archive
int extract_archive(int fd, tar_options* options)
{
    int res = 0;
    int archive_size = get_archive_size(options->archive_name);     // get archive size
    char* archive_content = get_archive_content(fd, archive_size);  // get archive content
    header *hdr;
    int index = 0;
    while (index < archive_size)
    {
        hdr = (header*)&archive_content[index];                 // get header from archive content
        if (is_header(hdr))                                     // if it is really a header
        {
            if (hdr->typeflag == REGTYPE)                   
            {
                index += extract_file(hdr, &archive_content[index]);    // extract the file
            }
            else if (hdr->typeflag == DIRTYPE)
            {
                index += extract_directory(hdr);                // extract the directory
            }
            else if (hdr->typeflag == SYMTYPE)
            {
                index += extract_symlink(hdr);                  // extract the symlink
            }
        }
        else
        {
            index += BLOCKSIZE;                                 // increment index
        }
    }

    return res + index;
}

// int main()
// {
//     char a_name[] = "archive.tar";
//     int fd = open(a_name, O_RDONLY);
//     int size = get_archive_size(a_name);
//     char* content = get_archive_content(fd, size);

//     header *hdr;
//     int index = 0;

//     hdr = (header*)&content[index];
//     printf("hdr size: %s\n", hdr->size);
//     printf("oct to dec: %ld\n", my_oct_to_dec(12146));
//     printf("my_atoi %ld\n", my_atoi("13675163707", 12));
//     int f_size = my_oct_to_dec(my_atoi(hdr->size, 12));
//     printf("hdr size\n%d\n", f_size);

//     printf("TH CHECKSUM %ld\n", my_oct_to_dec(my_atoi(hdr->chksum, 8)));
//     printf("MY CHECKSUM %d\n", find_chksum(hdr));
//     index += create_file(hdr, content);


//     printf("%d\n", index);
//     return 0;

// }