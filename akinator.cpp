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
        printf("Невалидные указатели\n");
        return;
    }
    while (true)
    {
        ask_quation(tr, tr->root);
        printf("Хотите продолжить?\n");
        if (get_answer() == 0) break;
    }

    save_tree(tr);
    dump(tr);
}

void ask_quation(tree* tr, node* now_node)
{
    if (left_node(now_node) && right_node(now_node))
    {
        printf("Это %s?\n", node_data(now_node));

        if (get_answer())
            ask_quation(tr, left_node(now_node));
        else
            ask_quation(tr, right_node(now_node));  
    } else
    {
        printf("Наверное это %s?\n", node_data(now_node));

        if (get_answer())
            printf ("Я угадал, я молодец!\n");
        else
            new_object(tr, now_node);
    }
}

int get_answer(void)
{
    char answer[MAX_LENGHT_ANSWER] = "";
    do
    {
        printf("Введите \"%s\" (да) или \"%s\" (нет)?\n", YES, NO);
        scanf("%s", answer);
    }
    while (strncmp(answer, YES, MAX_LENGHT_ANSWER) != 0 &&
           strncmp(answer, NO,  MAX_LENGHT_ANSWER) != 0);

    return strncmp(answer, NO, MAX_LENGHT_ANSWER);
}

void new_object(tree* tr, node*     old_node)
{
    printf("Кто/что это был(a/о)?\n");
    char name[MAX_LENGHT_DATA] = "";
    getchar();
    fgets(name, MAX_LENGHT_DATA, stdin);
    name[strlen(name) - 1] = '\0';
    stack* stk_of_name   = nullptr;
    stack* stk_of_answer = nullptr;

    if (find_def(tr->root, &stk_of_name, &stk_of_answer, name) == INSIDE_TREE)
    {
        printf("Это слово уже есть в дереве\n");
        print_definition(name, stk_of_name, stk_of_answer);
        return;
    }

    printf("Чем \"%s\" отличается от \"%s\"?\n Он(а/о) ...\n", name, node_data(old_node));
    char difference[MAX_LENGHT_DATA] = "";
    fgets(difference, MAX_LENGHT_DATA, stdin);
    difference[strlen(difference) - 1] = '\0';
    left_node (old_node) = make_node(name,                  nullptr, nullptr);
    right_node(old_node) = make_node(node_data(old_node),   nullptr, nullptr);
    strncpy(node_data(old_node), difference, MAX_LENGHT_DATA);
}