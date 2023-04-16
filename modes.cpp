#include "modes.h"
#include "read_tree.h"
#include "print.h"
#include <string.h>

#define define_mod(first_flag, secong_flag, description, function, num_char, need_tree)                 \
    if (strncmp(argv[1], first_flag, num_char) == 0 || strncmp(argv[1], secong_flag, num_char) == 0)    \
    {                                                                                                   \
        if (need_tree)                                                                                  \
            tr = read_tree_from_text();                                                                 \
        function;                                                                                       \
        tree_dtor(tr);                                                                                  \
    }                                                                                                   \
    else

void modes(int argc, const char** argv)
{
    if (argc == 1)
    {
        tree* tr = read_tree_from_text();
        akinator(tr);
        tree_dtor(tr);
    }
    else if (argc == 2)
    {
        tree* tr = nullptr;
        #include "flags.h"
        printf("Not found modes\n");
    } else
    {
        printf("Not found command\n");
        printf_help();
    }

}

#undef define_mod