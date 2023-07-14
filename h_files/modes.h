#ifndef MODES_H
#define MODES_H

#include "tree.h"
#define define_mod(first_flag, second_flag, description, function, num_char, need_tree, name) \
    name,
enum modes_numbers 
{
    #include "../settings_files/flags.h"
    CNT_MODES,
};

#undef define_mod

void    modes 		    (int argc, const char** argv);
void    akinator 	    (tree* tr);
void    definition     (tree* tr);
void    comparation    (tree* tr);
int     get_modes_num  (void);

#endif