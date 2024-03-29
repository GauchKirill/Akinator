#ifndef READ_TREE_H
#define READ_TREE_H

#include "tree.h"

tree* get_tree   (const char* name_tree_file);
tree* tree_from_file        (const char* name_tree_file);
char* get_buf               (const char* name_file);
node* parse_buf             (node* now_node, const char** buf);
node* parse_block           (node* now_node, const char** buf);
node* syntax_error          ();
char  get_bracket           (const char** buf);

#endif