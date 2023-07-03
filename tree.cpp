#include "tree.h"
#include "settings.h"

#include <stdlib.h>
#include <string.h>

tree* tree_ctor(const char* name_of_tree, const char* name_of_func, const char* name_of_file, size_t num_str)
{
    tree* tr   = (tree*) calloc(1, sizeof(tree));
    node* start_root = make_node((elem_t) "", nullptr, nullptr); 
    
    if (!tr || !start_root)
        return nullptr;

    tr->root = start_root;

    tr->info.name_tree = (name_of_tree[0] == '&') ? name_of_tree + 1 : name_of_tree;
    tr->info.name_func = name_of_func;
    tr->info.name_file = name_of_file;
    tr->info.num_str   = num_str;

    return tr;
}

node* make_node (elem_t data_of_node, node* left_ptr, node* right_ptr)
{
    node* new_node  = (node*) calloc(1, sizeof(node));
    if (!new_node)
    {
        printf("Has not memory for node\n");
        return nullptr;
    }

    node_data(new_node) = make_data(data_of_node);
    if (!node_data(new_node))
    {
        printf("Has not memory for \"");
        printf(elem_out, data_of_node);
        printf("\"\n");
        return nullptr;
    }

    left_node(new_node)  = left_ptr;
    right_node(new_node) = right_ptr;

    return new_node;
}

elem_t make_data(elem_t data)
{
    elem_t copy_data = (elem_t) calloc(MAX_LENGHT_DATA + 1, sizeof(char));
    if (copy_data)
        strncpy(copy_data, data, MAX_LENGHT_DATA);

    return copy_data;
}

void tree_dtor(tree* tr)
{
    if (!tr)
        return;
    tr->info.name_tree = tr->info.name_file = tr->info.name_func = (const char*) TREE_POISON_NAME;
    tr->info.num_str  = TREE_POISON_STR;
    node_dtor(tr->root);
    free(tr);
}

void node_dtor(node* now_node)
{
    if (!now_node)
        return;
    if (now_node->is_visited)
    {
        free(now_node);
        return;
    }
    else
    {
        now_node->is_visited = true;
        node_dtor(left_node(now_node));
        node_dtor(right_node(now_node));
        free(now_node);    
    }
}

