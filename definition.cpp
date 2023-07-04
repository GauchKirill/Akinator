#include "definition.h"
#include "akinator.h"
#include "print.h"
#include "settings.h"
#include <string.h>

extern elem_t YES;
extern elem_t NO;
    
void definition(tree* tr)
{
    if (!tr || !tr->root)
    {
        printf("\nНевалидные указатели.\n");
        return;
    }
    while (true)
    {
        char name[MAX_LENGHT_DATA] = "";
        printf("\nВведите слово, которому дать определение или \"-\" для выхода:\n");
        fgets(name, MAX_LENGHT_DATA, stdin);
        name[strlen(name) - 1] = '\0';
        if (strncmp(name, "-", 2) == 0)
            return;
        stack* answer_stk = nullptr;
        stack* name_stk   = nullptr;

        if (find_def(tr->root, &name_stk, &answer_stk, name) == INSIDE_TREE)
        {
            print_definition(name, name_stk, answer_stk);

            printf("\nХотите продолжить искать определения?\n");
            if (get_answer() == 0) break;
            getchar();  
        } else
            printf("\nСлово \"%s\" не найдено в дереве.\n", name);
    }
}

#define find_in_child(name_child, push_word)                                                        \
    if (find_def(name_child ## _node(now_node), stk_of_name, stk_of_answer, name) == INSIDE_TREE)   \
    {                                                                                               \
        StackPush(*stk_of_name, node_data(now_node));                                                \
        StackPush(*stk_of_answer, push_word);                                                        \
        return INSIDE_TREE;                                                                         \
    } else                                                                               

int find_def(node* now_node, stack** stk_of_name, stack** stk_of_answer, elem_t name)
{
    if (!stk_of_name || !stk_of_answer)
        return STACK_NULLPTR;

    StackCtor(stk_of_name,   1);
    StackCtor(stk_of_answer, 1);

    if (left_node(now_node) && right_node(now_node))
    {
        find_in_child(left, YES)
        find_in_child(right, NO)
            return NOT_INSIDE_TREE;
    }
    else
    {
        if (strncmp(node_data(now_node), name, MAX_LENGHT_DATA) == 0)
            return INSIDE_TREE;
        else
            return NOT_INSIDE_TREE;
    }
}

#undef find_in_child