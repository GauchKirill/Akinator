#ifndef DUMP_H
#define DUMP_H

#include "tree.h"

void dump 		(tree* tr);
void dump_note 	(node* top, int* num_node, FILE* dump_file);
void save_tree 	(const tree* tr);

#endif