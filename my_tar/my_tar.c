#include "my_tar.h"

int main(int ac, char** av)
{
    tar_options *options = get_opt(ac, av);

    if(options == NULL) return 1;

    reset_options(options);
    return 0;
}