#ifndef DEFINITION_H
#define DEFINITION_H

#include "tree.h"
#include "Stack.h"

enum definition_state
{
    INSIDE_TREE         = 1,
    NOT_INSIDE_TREE     = 0,
};

void definition (tree* tr);
int  find_def   (node* now_node, stack** stk_of_name, stack** stk_of_answer, elem_t name);

#endif