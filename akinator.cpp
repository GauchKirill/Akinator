#include "akinator.h"
#include "definition.h"
#include "dump.h"
#include "print.h"
#include "settings.h"
#include <string.h>

elem_t YES = (elem_t) "y";
elem_t NO  = (elem_t) "n";

void akinator(tree* tr)
{
    if (!tr || !tr->root)
    {
        printf("\nНевалидные указатели\n");
        return;
    }
    while (true)
    {
        ask_quation(tr, tr->root);
        printf("\nХотите продолжить играть в акинатора?\n");
        if (get_answer() == 0) break;
    }

    printf("\nХотите сохранить получившееся дерево?\n");
    
    if (get_answer())
        dump(tr);
    else
        return;

}

void ask_quation(tree* tr, node* now_node)
{
    if (left_node(now_node) && right_node(now_node))
    {
        printf("\nЭто %s?\n", node_data(now_node));

        if (get_answer())
            ask_quation(tr, left_node(now_node));
        else
            ask_quation(tr, right_node(now_node));  
    } else
    {
        printf("\nНаверное это %s?\n", node_data(now_node));

        if (get_answer())
            printf ("\nЯ угадал, я молодец!\n");
        else
            new_object(tr, now_node);
    }
}

void new_object(tree* tr, node*     old_node)
{
    printf("\nКто/что это был(a/о)?\n");
    char name[MAX_LENGHT_DATA] = "";
    getchar();
    fgets(name, MAX_LENGHT_DATA, stdin);
    name[strlen(name) - 1] = '\0';
    stack* stk_of_name   = nullptr;
    stack* stk_of_answer = nullptr;

    if (find_def(tr->root, &stk_of_name, &stk_of_answer, name) == INSIDE_TREE)
    {
        printf("\nЭто слово уже есть в дереве\n");
        print_definition(name, stk_of_name, stk_of_answer);
        return;
    }

    printf("\nЧем \"%s\" отличается от \"%s\"?\n Он(а/о) ...\n", name, node_data(old_node));
    char difference[MAX_LENGHT_DATA] = "";
    fgets(difference, MAX_LENGHT_DATA, stdin);
    difference[strlen(difference) - 1] = '\0';
    left_node (old_node) = make_node(name,                  nullptr, nullptr);
    right_node(old_node) = make_node(node_data(old_node),   nullptr, nullptr);
    strncpy(node_data(old_node), difference, MAX_LENGHT_DATA);
}