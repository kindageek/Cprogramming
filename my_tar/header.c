#include "my_tar.h"

// Function to get typeflag of a file by its mode
char get_typeflag(int mode)
{
    // printf("\n==============\n %d \n==============\n %d \n==============\n", mode, mode&S_IFMT);
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

// Function to get user name of a file by user id
char* get_user_name(int uid)
{
    struct passwd *pwd;
    pwd = getpwuid(uid);
    return pwd->pw_name;
}

// Function to get group name of a file by group id
char* get_group_name(int gid)
{
    struct group *grp;
    grp = getgrgid(gid);
    return grp->gr_name;
}

// Function to calculate checksum of a header 
// by addding all header bytes with chksum initially being empty spaces
unsigned int get_chksum(header* header)
{
    int sum = 0;
    char* headerBytes = (char*)header;		
    for( size_t i = 0; i < BLOCKSIZE; ++i )
    {
        sum += headerBytes[i];
    }
    return sum;
}

// Function to get header of a file 
header* get_header(char* filename)
{
    header* header = malloc(BLOCKSIZE);     // init header
    my_bzero(header, BLOCKSIZE);            // fill with zeros

    struct stat info;
    if(stat(filename, &info) < 0){          // if the file does not exist
        free(header);
        return NULL;
    }
                                                                    // POSIX header struct
    strncpy(header->name, filename, 100);                           // name
    my_itoa(header->mode, info.st_mode & 0777, 8, OCTAL_BASE);      // mode
    my_itoa(header->uid, info.st_uid, 8, OCTAL_BASE);               // uid
    my_itoa(header->gid, info.st_gid, 8, OCTAL_BASE);               // gid
    my_itoa(header->size, info.st_size, 12, OCTAL_BASE);            // size
    my_itoa(header->mtime, info.st_mtime, 12, OCTAL_BASE);          // mtime
    
    header->typeflag = get_typeflag(info.st_mode);                  // typeflag
    readlink(filename, header->linkname, 100);                      // linkname
    if(strlen(header->linkname) != 0) header->typeflag = SYMTYPE;
    
    strcpy(header->magic, TMAGIC);                                  // magic
    header->magic[5] = ' ';                                         // space after ustar
    header->version[0] = ' ';                                       // another space
    
    strcpy(header->uname, get_user_name(info.st_uid));              // uname
    strcpy(header->gname, get_group_name(info.st_gid));             // gname
    
    my_memset(header->chksum, ' ', 8);                              // empty checksum
    my_itoa(header->chksum, get_chksum(header), 7, OCTAL_BASE);     // checksum
    header->chksum[7] = ' ';                                        // space after cheksum
    
    return header;
}

// get file size from header
// string -> octal -> decimal
int get_header_size(header* hdr)
{
    return my_oct_to_dec(my_atoi(hdr->size, strlen(hdr->size)));
}

// get mtime of file from header
// string -> octal -> decimal -> unsigned long
unsigned long get_header_mtime(header* hdr)
{
    return (unsigned long)my_oct_to_dec(my_atoi(hdr->mtime, 12));
}

// get mode of file from header
// string -> octal -> decimal
int get_header_mode(header* hdr)
{
    return my_oct_to_dec(my_atoi(hdr->mode, sizeof(hdr->mode)));
}

// get header chksum
// string -> octal -> decimal
int get_header_chksum(header* hdr)
{
    return my_oct_to_dec(my_atoi(hdr->chksum, 8));
}

// Function to check if given header is actually a header
bool is_header(header* hdr)
{
    unsigned int  header_checksum = get_header_chksum(hdr);         // get header chksum
    unsigned int my_checksum = find_chksum(hdr);                       // calculate chksum yourself
    
    if(my_checksum == 0 || header_checksum != my_checksum) return false;  // compare chksums, they must be equal
    if(my_checksum == header_checksum) return true;
    return false;    
}

// Function to free the memory allocated for header
void free_header(header* hdr)
{
    free(hdr->name);
    free(hdr->mode);
    free(hdr->uid);
    free(hdr->gid);
    free(hdr->size);
    free(hdr->mtime);
    free(hdr->chksum);
    hdr->typeflag = '\0';
    free(hdr->linkname);
    free(hdr->magic);
    free(hdr->version);
    free(hdr->uname);
    free(hdr->gname);
    free(hdr->devmajor);
    free(hdr->devminor);
    free(hdr->prefix);
}