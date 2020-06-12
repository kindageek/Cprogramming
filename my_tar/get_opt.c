#include "my_tar.h"

static tar_options* init_opt()
{
    tar_options* opt = (tar_options*)malloc(sizeof(tar_options));
    
    opt->create = false;
    opt->extract = false;
    opt->archive_name = NULL;
    opt->args = init_args();

    return opt;
}


bool is_option(char* arg)
{
    return arg[0] == '-';
}


static tar_options* set_options(tar_options* opt, char* options, bool *is_archive_name)
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

    return opt;
}


static bool check_options(tar_options* opt)
{
    if(opt->create && opt->extract){
        printf("tar: Can't specify both -x and -c\n");
        return false;
    }else if(!opt->create && !opt->extract){
        printf("tar: Must specify one of -c, -r, -t, -u, -x\n");
        return false;
    }

    if(opt->archive_name == NULL && opt->args->filename == NULL){
        printf("tar: Option -f requires an argument\n");
        printf("Usage:\n");
        printf("  List:    tar -tf <archive-filename>\n");
        printf("  Extract: tar -xf <archive-filename>\n");
        printf("  Create:  tar -cf <archive-filename> [filenames...]\n");
        printf("  Help:    tar --help\n");
        return false;
    }else if(opt->archive_name != NULL && opt->args->filename == NULL){
        printf("tar: no files or directories specified\n");
        return false;
    }

    return true;
}


tar_options* get_opt(int ac, char** av)
{   
    tar_options* opt = init_opt();
    int index = 1;
    bool is_archive_name = false;

    while(index < ac){
        if(is_option(av[index])){
            set_options(opt, av[index], &is_archive_name);
        }else if(is_archive_name){
            opt->archive_name = strdup(av[index]);
            is_archive_name = false;
        }else{
            add_to_list(&(opt)->args, av[index]);
        }

        index += 1;
    }

    if(check_options(opt) == false){
        reset_options(opt);
        return NULL;
    }
    print_opt(opt);
    return opt;
}


void reset_options(tar_options* opt)
{
    if(opt->archive_name != NULL)
        free(opt->archive_name);
    
    reset_args(&(opt)->args);
    free(opt);
}