#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include <unistd.h>
#include <stdarg.h>

#define BLOCKSIZE 512

/* POSIX header.  */

struct posix_header
{                               /* byte offset */
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
};

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

// my.c
void my_memset(char* buff, char val, int size);
void my_bzero(char* buff, int size);