#ifndef AKINATOR_H
#define AKINATOR_H

#include "tree.h"

void  akinator      (tree* tr);
void  ask_question   (tree* tr, node* now_node);
node* make_node     (elem_t* node_data, node* left_ptr, node* right_ptr);
void  new_object    (tree* tr, node* old_node);

#endif