#include "my_tar.h"

// initialize option struct
static tar_options* init_opt()
{
    tar_options* opt = (tar_options*)malloc(sizeof(tar_options));
    opt->c = false;
    opt->x = false;
    opt->r = false;
    opt->u = false;
    opt->t = false;
    opt->f = false;
    opt->archive_name = NULL;
    opt->args = init_args();
    return opt;
}

// check if given argument is an option list that starts with a hyphen
bool is_option(char* arg)
{
    return arg[0] == '-';
}

// set options from the option list and change is_archive_name if -f option is specified
static tar_options* set_options(tar_options* opt, char* options, bool* is_archive_name)
{
    int index = 0;
    while (options[index] != '\0')
    {
        if (options[index] == 'c')
            opt->c = true;
        else if (options[index] == 'x')
            opt->x = true;
        else if (options[index] == 'r')
            opt->r = true;
        else if (options[index] == 'u')
            opt->u = true;
        else if (options[index] == 't')
            opt->t = true;
        else if (options[index] == 'f')
        {
            opt->f = true;
            *is_archive_name = true;
        }
        index += 1;
    }
    return opt;
}

// check if options and arguments are correct and do not clash with each other
static bool check_options(tar_options* opt)
{
    // check if both extract and create options are specified
    if (opt->x && opt->r)
    {
        printf("tar: Can't specify both -x and -c\n");
        return false;
    }
    // check if both -u and -r options are specified
    if (opt->u && opt->r)
    {
        printf("tar: Can't specify both -u and -r\n");
        return false;
    }
    // check if none of the options are specified
    if (!opt->c && !opt->x && !opt->r && !opt->u && !opt->t)
    {
        printf("tar: Must specify one of -c, -r, -t, -u, -x\n");
        return false;
    }
    // check if -r or -u options are specified without -f option
    if ((opt->r || opt->u) && !opt->f)
    {
        printf("tar: Cannot append to stdout.\n");
        return false;
    }
    // check if -t option is specified without -f option or archive name
    if ((opt->t && !opt->f) || (opt->t && opt->archive_name == NULL))
    {
        printf("tar: no files or directories specified\n");
        return false;
    }
    // check if archive name and arguments are not given
    if (opt->archive_name == NULL && opt->args->filename == NULL)
    {
        printf("tar: Option -f requires an argument\n");
        printf("Usage:\n");
        printf("  List:    tar -tf <archive-filename>\n");
        printf("  Extract: tar -xf <archive-filename>\n");
        printf("  Create:  tar -cf <archive-filename> [filenames...]\n");
        printf("  Help:    tar --help\n");
        return false;
    }
    // check if archive name is not given when arguments are given
    if (opt->archive_name == NULL && opt->args->filename != NULL)
    {
        printf("tar: no files or directories specified\n");
        return false;
    }
    return true;
}

// traverse through command line arguments
// and return struct of options
tar_options* get_opt(int ac, char** av)
{
    tar_options* opt = init_opt();
    int index = 1;
    bool is_archive_name = false;
    while (index < ac)
    {
        if (is_option(av[index]))
        {
            set_options(opt, av[index], &is_archive_name);
        }
        else if (is_archive_name)
        {
            opt->archive_name = strdup(av[index]);
            is_archive_name = false;
        }
        else
        {
            add_to_list(&(opt)->args, av[index]);
        }
        index += 1;
    }
    if (check_options(opt) == false)
    {
        reset_options(opt);
        return NULL;
    }
    // print_opt(opt);
    return opt;
}

// free the memory allocated for the option struct
void reset_options(tar_options* opt)
{
    if (opt->archive_name != NULL) free(opt->archive_name);
    reset_args(&(opt)->args);
    free(opt);
}