#include "my_tar.h"

int main(int ac, char** av)
{
    options *options = get_opt(ac, av);

    if(options == NULL){
        printf("Error\n");
        return 1;
    }

    reset_options(options);
    return 0;
}