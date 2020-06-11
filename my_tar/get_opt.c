#include "my_tar.h"

options* init_opt()
{
    options* opt = (options*)malloc(sizeof(options*));
    
    opt->create = false;
    opt->extract = false;
    opt->archive_name = NULL;
    opt->args = NULL;

    return opt;
}

bool is_option(char* arg)
{
    return arg[0] == '-';
}

void set_option(options* opt, char* options, bool *is_archive_name)
{
    int index = 0;
    while(options[index] != '\0'){
        if(options[index] == 'c')
            opt->create = true;
        else if(options[index] == 'x')
            opt->extract = true;
        else if(options[index] == 'f')
            *is_archive_name = true;

        index += 1;
    }
}

void add_to_list(options* opt, char* filename){
    
}

options* get_opt(int ac, char** av)
{
    if (ac < 2) return NULL;
    
    options* opt = init_opt();
    int index = 1;
    bool is_archive_name = false;

    while(index < ac){
        if(is_option(av[index]))
            set_option(opt, av[index] + 1, &is_archive_name);
        else if(is_archive_name)
            opt->archive_name = av[index];
        else
            add_to_list(opt, av[index]);
        
        index += 1;
    }

    return opt;
}

void reset_args(arg* args)
{
    while(args){
        free(args->filename);
        args = args->next;
    }
}

void reset_options(options* opt)
{
    free(opt->archive_name);
    reset_args(opt->args);
}