#include "akinator.h"
#include "definition.h"
#include "dump.h"
#include "print.h"
#include <string.h>

Elem_t YES = (Elem_t) "y";
Elem_t NO  = (Elem_t) "n";

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
		printf("Наверное это \"%s\"?\n", node_data(now_node));

		if (get_answer())
			printf ("Я угадал, я молодец!\n");
		else
			new_object(tr, now_node);
	}
}

int get_answer(void)
{
	char answer[max_lenght_answer] = "";
	do
	{
		printf("Введите \"%s\" (да) или \"%s\" (нет)?\n", YES, NO);
		scanf("%s", answer);
	}
	while (strncmp(answer, YES, max_lenght_answer) != 0 &&
	       strncmp(answer, NO,  max_lenght_answer) != 0);

	return strncmp(answer, NO, max_lenght_answer);
}

void new_object(tree* tr, node* old_node)
{
	printf("Кто/что это был(a/о)?\n");
	char answer[max_lenght_data] = "";
	fgets(answer, max_lenght_data, stdin);

	stack* stk_of_name   = nullptr;
	stack* stk_of_answer = nullptr;
	if (make_stacks(answer, tr, &stk_of_name, &stk_of_answer) == INSIDE_TREE)
	{
		printf("Это слово уже есть в дереве\n");
		print_definition(answer, stk_of_name, stk_of_answer);
		return;
	}

	printf("Чем \"%s\" отличается от \"%s\"?\n Он(а/о) ...\n", answer, node_data(old_node));
	char difference[max_lenght_data] = "";
	scanf("%s", difference);

	left_node (old_node) = make_node(answer,              nullptr, nullptr);
	right_node(old_node) = make_node(node_data(old_node), nullptr, nullptr);
	strncpy(node_data(old_node), difference, max_lenght_data);
}

Elem_t make_data(Elem_t data)
{
	Elem_t copy_data = (Elem_t) calloc(max_lenght_data + 1, sizeof(char));
	if (copy_data)
		strncpy(copy_data, data, max_lenght_data);

	return copy_data;
}