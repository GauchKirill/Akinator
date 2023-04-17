#include "definition.h"
#include "akinator.h"
#include "print.h"
#include <string.h>

extern elem_t YES;
extern elem_t NO;
    
void definition(tree* tr)
{
    if (!tr || !tr->root)
    {
        printf("Невалидные указатели\n");
        return;
    }
    while (true)
    {
        char name[MAX_LENGHT_DATA] = "";
        printf("Введите слово, которому дать определение или \"-\" для выхода:\n");
        fgets(name, MAX_LENGHT_DATA, stdin);
        name[strlen(name) - 1] = '\0';
        if (strncmp(name, "-", 2) == 0)
            return;
        stack* answer_stk = {0};
        stack* name_stk   = {0};

        if (make_stacks(name, tr, &name_stk, &answer_stk) == INSIDE_TREE)
        {
            print_definition(name, name_stk, answer_stk);

            printf("Хотите продолжить?\n");
            if (get_answer() == 0) break;
            getchar();  
        } else
            printf("Слово \"%s\" не найдено в дереве\n", name);
    }
}

int make_stacks(elem_t name, tree* tr, stack** name_stk, stack** answer_stk)
{
    if (!tr) return TREE_INVALID_PTR;
    stack* stk_of_name = {0};
    stack* stk_of_answer = {0};
    StackCtor(&stk_of_name, 1);
    StackCtor(&stk_of_answer, 1);

    int find_word = find_def(tr->root, stk_of_name, stk_of_answer, name);
    *name_stk   = stk_of_name;
    *answer_stk = stk_of_answer;
    return find_word;
}

int find_def(node* now_node, stack* stk_of_name, stack* stk_of_answer, elem_t name)
{
    if (left_node(now_node) && right_node(now_node))
    {
        if (find_def(left_node(now_node), stk_of_name, stk_of_answer, name))
        {
            StackPush(stk_of_name,   node_data(now_node));
            StackPush(stk_of_answer, YES);
            return INSIDE_TREE;
            
        } else if (find_def(right_node(now_node), stk_of_name, stk_of_answer, name))
        {
            StackPush(stk_of_name,   node_data(now_node));
            StackPush(stk_of_answer, NO);
            return INSIDE_TREE;     

        } else
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