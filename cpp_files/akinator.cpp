#include "../h_files/akinator.h"
#include "../h_files/definition.h"
#include "../h_files/dump.h"
#include "../h_files/print.h"
#include "../settings_files/akinator_settings.h"
#include <string.h>
#include <stdlib.h>

void akinator(tree* tr)
{
    if (!tr || !tr->root)
    {
        reproduce_text("Невалидные указатели.", "russian");
        return;
    }
    while (true)
    {
        ask_question(tr, tr->root);
        reproduce_text("Хотите продолжить играть в акинатора?", "russian");
        if (get_answer() == 0) break;
    }

    reproduce_text("Хотите сохранить получившееся дерево?", "russian");

    if (get_answer())
        dump(tr);
    else
        return;

}

void ask_question(tree* tr, node* now_node)
{
    if (left_node(now_node) && right_node(now_node))
    {
        sprintf(cmd_text, "Это %s?", node_data(now_node));
        reproduce_text(cmd_text, "russian");

        if (get_answer())
            ask_question(tr, left_node(now_node));
        else
            ask_question(tr, right_node(now_node));  
    } else
    {
        sprintf(cmd_text, "Наверное это %s?", node_data(now_node));
        reproduce_text(cmd_text, "russian");

        if (get_answer())
            reproduce_text("Я угадал, я молодец!", "russian");
        else
            new_object(tr, now_node);
    }
}

void new_object(tree* tr, node*     old_node)
{
    reproduce_text("Кто или что это было?", "russian");

    char name[MAX_LENGHT_DATA] = "";
    getchar();
    fgets(name, MAX_LENGHT_DATA, stdin);
    name[strlen(name) - 1] = '\0';
    stack* stk_of_name   = nullptr;
    stack* stk_of_answer = nullptr;

    if (find_def(tr->root, &stk_of_name, &stk_of_answer, name) == INSIDE_TREE)
    {
        reproduce_text("Это слово уже есть в дереве.", "russian");

        print_definition(name, stk_of_name, stk_of_answer);
        return;
    }

    sprintf(cmd_text, "Чем \"%s\" отличается от \"%s\"?\n Оно ...", name, node_data(old_node));
    reproduce_text(cmd_text, "russian");
    
    char difference[MAX_LENGHT_DATA] = "";
    fgets(difference, MAX_LENGHT_DATA, stdin);
    difference[strlen(difference) - 1] = '\0';
    left_node (old_node) = make_node(name,                  nullptr, nullptr);
    right_node(old_node) = make_node(node_data(old_node),   nullptr, nullptr);
    strncpy(node_data(old_node), difference, MAX_LENGHT_DATA);
}