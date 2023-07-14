#include "../h_files/print.h"
#include "../settings_files/akinator_settings.h"
#include <string.h>

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

void print_definition(elem_t name, stack* name_stk, stack* answer_stk)
{
    if (name_stk->size == 0)
        return;
    
    printf("\"%s\" это", name);

    while(name_stk->size > 0)
    {
        char* definition = nullptr;
        char* answer     = nullptr; 
        StackPop (name_stk,   &definition);
        StackPop (answer_stk, &answer);
        printf(" %s\"%s\"", (strncmp(answer, YES, MAX_LENGHT_ANSWER) == 0) ? "" : "не ", definition);
        if (name_stk->size > 0)
            printf (",");
        else
            printf (".");
    }
    printf("\n");
}

int get_answer(void)
{
    char answer[MAX_LENGHT_ANSWER] = "";
    int is_no = 0;
    do
    {
        printf("Введите \"%s\" (да) или \"%s\" (нет)?\n", YES, NO);
        scanf("%s", answer);
    }
    while (         strncmp(answer, YES, MAX_LENGHT_ANSWER) != 0 &&
           (is_no = strncmp(answer, NO,  MAX_LENGHT_ANSWER) != 0));

    return is_no;
}

#define define_mod(short_flag, long_flag, description, ...)           \
    printf("%-3s    %-15s   %-s\n", short_flag, long_flag, description);

void printf_help(void)
{
    #include "../settings_files/flags.h"
}

#undef define_mod