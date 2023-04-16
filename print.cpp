#include "print.h"
#include <string.h>

extern Elem_t YES;
extern Elem_t NO;

void print_node_to_file(const node* now_node, size_t num_layer, FILE* tree_file)
{
    if (!left_node(now_node) || !right_node(now_node))
    {
        print_tabs(num_layer);
        fprintf(tree_file, "{ %s }\n", node_data(now_node));
    }
    else
    {
        print_tabs(num_layer);
        fprintf(tree_file,
            "{ %s \n", node_data(now_node));
        print_node_to_file(left_node(now_node),  num_layer+1, tree_file);
        print_node_to_file(right_node(now_node), num_layer+1, tree_file);
        print_tabs(num_layer);
        fprintf(tree_file, "}\n");
    }
}

void print_definition(Elem_t name, stack* name_stk, stack* answer_stk)
{
    printf("\"%s\" это", name);

    while(name_stk->size > 0)
    {
        char* definition = nullptr;
        char* answer     = nullptr; 
        StackPop (name_stk,   &definition);
        StackPop (answer_stk, &answer);
        printf(" %s\"%s\"", (strncmp(answer, YES, max_lenght_answer) == 0) ? "" : "не ", definition);
        if (name_stk->size > 0)
            printf (",");
        else
            printf (".");
    }
    printf("\n");
}

#define define_mod(first_flag, secong_flag, description, ...)           \
    printf("%-3s    %-15s   %-s\n", first_flag, secong_flag, description);

void printf_help(void)
{
    #include "flags.h"
}

#undef define_mod