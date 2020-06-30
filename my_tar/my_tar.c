#include "my_tar.h"


// main function
int main(int ac, char** av)
{
    int res = 0;
    tar_options *options = get_opt(ac, av);

    if(options == NULL) return 1;
    
    int fd = open_archive(options);

    if(fd < 0){
        reset_options(options);
        return 1;
    }

    if(options->c)
        res += create_archive(fd, options);
    else if(options->x)
        res += extract_archive(fd, options);
    else if(options->r)
        res += append_archive(fd, options);
    else if(options->t)
        res += print_archive(fd, options);
    else if(options->u)
        res += update_archive(fd, options);
    
    close(fd);
    reset_options(options);
    return res;
}