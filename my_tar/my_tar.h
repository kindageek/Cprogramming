#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include <unistd.h>
#include <stdarg.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <pwd.h>
#include <grp.h>
#include <time.h>
#include <utime.h>
#include <dirent.h>

#define BLOCKSIZE 512
#define OCTAL_BASE 8
#define DECIMAL_BASE 10

/* POSIX header.  */
typedef struct posix_header
{                                 /* byte offset */
    char name[100];               /*   0 */
    char mode[8];                 /* 100 */
    char uid[8];                  /* 108 */
    char gid[8];                  /* 116 */
    char size[12];                /* 124 */
    char mtime[12];               /* 136 */
    char chksum[8];               /* 148 */
    char typeflag;                /* 156 */
    char linkname[100];           /* 157 */
    char magic[6];                /* 257 */
    char version[2];              /* 263 */
    char uname[32];               /* 265 */
    char gname[32];               /* 297 */
    char devmajor[8];             /* 329 */
    char devminor[8];             /* 337 */
    char prefix[155];             /* 345 */
                                  /* 500 */
} header;

#define TMAGIC   "ustar"        /* ustar and a null */
#define TMAGLEN  6
#define TVERSION "00"           /* 00 and no null */
#define TVERSLEN 2

/* Values used in typeflag field.  */
#define REGTYPE  '0'            /* regular file */
#define AREGTYPE '\0'           /* regular file */
#define LNKTYPE  '1'            /* link */
#define SYMTYPE  '2'            /* reserved */
#define CHRTYPE  '3'            /* character special */
#define BLKTYPE  '4'            /* block special */
#define DIRTYPE  '5'            /* directory */
#define FIFOTYPE '6'            /* FIFO special */
#define CONTTYPE '7'            /* reserved */


typedef struct s_arg
{
    char *filename;
    struct s_arg *next;
}tar_arg;


typedef struct s_options
{
    bool c;
    bool x;
    bool r;
    bool u;
    bool t;
    bool f;
    char *archive_name;
    struct s_arg *args;
}tar_options;


// get_opt.c
tar_options* get_opt(int ac, char** av);
void reset_options(tar_options* opt);

// print_opt.c
void print_opt(tar_options* opt);

// args.c
tar_arg* init_args();
void add_to_list(tar_arg** args, char* filename);
void reset_args(tar_arg** args);
bool in_args(char* filename, tar_arg** args);

// my.c
void my_memset(char* buff, char val, int size);
void my_bzero(void * buff, size_t size);
char *my_itoa(char * res, unsigned int num, int size, int base);  
long my_atoi(char * number_string, int size);
long my_oct_to_dec(long octal_number);  

// header.c
header* get_header(char* filename);
unsigned int get_chksum(header* header);
int get_header_size(header* hdr);
unsigned long get_header_mtime(header* hdr);
int get_header_mode(header* hdr);
int get_header_chksum(header* hdr);
bool is_header(header* hdr);
void free_header(header* hdr);

// write.c
int write_to_tar(char* filename, int fd);
int write_file(int fd, char* filename);
int write_dir(int fd, char* dirname);

// archive.c
int open_archive(tar_options* opt);
void end_archive(int fd);
int get_file_size(int fd);
int get_archive_size(char* filename);
char* get_archive_content(int fd, int size);

// create.c
int create_archive(int fd, tar_options* opt);

// extract.c
int extract_archive(int fd, tar_options* opt);
unsigned int find_chksum(header* hdr);

// append.c
int append_archive(int fd, tar_options* opt);

// update.c
int update_archive(int fd, tar_options* opt);

// print.c
int print_archive(int fd, tar_options* opt);
