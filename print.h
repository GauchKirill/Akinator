#ifndef PRINT_H
#define PRINT_H

#include "tree.h"
#include "Stack.h"

#define print_tabs(num_tab)                                     \
    for (size_t i = 1; i <= num_tab; i++) fprintf(tree_file, "  ");

void print_node_to_file(const node* now_node, size_t num_layer, FILE* tree_file);
void print_definition  (elem_t name,    stack* name_stk,    stack* answer_stk);
void printf_help       (void);
int   get_answer       (void);

#endif