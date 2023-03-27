#ifndef TREE_H
#define TREE_H

#include <stdio.h>
#include <stdint.h>

const size_t max_lenght_data      = 50;
const size_t max_lenght_name_file = 20;
const size_t max_lenght_answer    = 4;

typedef char* Elem_t;
extern const char* Elem_out;

typedef struct
{
	const char* name_tree; //rename
	const char* name_func; //where tree made
	const char* name_file; //where tree made
	size_t num_str;        //where tree made
} tree_info; 

typedef struct _node
{
	Elem_t        data;
	struct _node* left;
	struct _node* right;
} node;

typedef struct
{
	node*     root;
	tree_info info;
} tree;

enum poisons
{
	TREE_POISON_DATA = 0,
	TREE_POISON_PTR  = 0,
	TREE_POISON_NAME = 0,
	TREE_POISON_STR  = SIZE_MAX,
};

enum tree_errors
{
	TREE_INVALID_PTR = 1<<1,
};

#define node_data(Node) (Node)->data

#define left_node(Node)  (Node)->left

#define right_node(Node)  (Node)->right

#define TreeCtor(tr) tree_ctor(#tr, __PRETTY_FUNCTION__, __FILE__, __LINE__)

tree* tree_ctor	(const char* name_of_tree, const char* name_of_func, const char* name_of_file, size_t num_str);
node* make_node (Elem_t data_of_node, node* left_ptr, node* right_ptr);
void  tree_dtor	(tree* tr);
void  node_dtor	(node* now_node);
char* make_data(Elem_t data_of_node);

#endif