#include "ls.h"
/*
 *  My my_ls is compiled with the name "ls", so when testing my program, please use "./ls". Thanks :) 
 */

// Main function, takes command line arguments as parameters
int main(int argc, const char* argv[])
{
    if (argc == 1)
    {
        my_ls(CURRENT_DIR, false, false, false);                                                // if there is only "./ls", then print current directory data
    }
    else
    {
        run(argc, argv);                                                                        // else run the program with arguments
    }
    return 0;
}