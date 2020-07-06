#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdbool.h>
#include <stdarg.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>

// error messages
#define NO_RESOURSE         "nok: no more resources available on the computer\n"
#define NODE_EXISTS         "nok: this node already exists\n"
#define BLOCK_EXISTS        "nok: this block already exists\n"
#define NODE_NOT_EXISTS     "nok: node doesn't exist\n"
#define BLOCK_NOT_EXISTS    "nok: block doesn't exist\n"
#define UNKNOWN             "nok: command not found\n"
#define NOT_ENOUGH_ARGS     "nok: incorrect number arguments\n"
#define NO_NODES            "nok: no nodes in the blockchain\n"

// commands
#define QUIT "quit"
#define LIST "ls"
#define LIST_L "ls -l"
#define SYNC "sync"

// custom defines
#define DEC_BASE 10
#define NULL_HEAD -1

typedef struct blockchain_block
{
    char* bid;
    int nid;
    struct blockchain_block* next;
}block;

typedef struct blockchain_node
{
    int nid;
    struct blockchain_block* block;
    struct blockchain_node* next;
}node;

typedef struct string_array
{
    int size;
    char** array;
}string_array;

typedef struct string_linked_list
{
    char* name;
    struct string_linked_list* next;
} string_list;

// prompt.c
void prompt_line(node* head);

// my_functions.c
void my_bzero(void* buff, size_t size);
string_array* my_split(char* a, char* b);
void free_string_array(string_array* words);
int my_atoi(char* number_string, int size);
char* my_itoa(int val, int base);

// my_readline.c
char* my_readline(int fd);

// prompt.c
void prompt_line(node* head);

// command.c
void start(node** head);
bool parse_command(node** head, char* command);

// load.c
node* load_data();

// save.c
void save_data(node* head);

// blockchain.c
bool is_synced(node* head);
void sync_nodes(node** head);

// block.c
block* init_blocks();
void add_block(node** head, char* bid, int nid);
void remove_block(node** head, char* bid);
void free_blocks(block** block);
void print_block(block* b);

// node.c
node* init_nodes();
void add_node(node** head, int nid);
void remove_node(node** head, int nid);
void free_node(node** node);
int get_size(node* head);
void print_node(node* n, bool with_blocks);
void print_nodes(node* head, bool with_blocks);

// string_list.c
void print_list(string_list* list);
void free_string_list(string_list* list);
void add_to_string_list(string_list** list, char* word);