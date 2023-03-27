#include "dump.h"
#include "print.h"
#include <string.h>

void dump(tree* tr)
{
	if (!tr) return;
	char name_dump_file[max_lenght_name_file] = {0};
	printf ("\nВведите название файла для диагностики с расширением .dot или введите \"-\" чтобы пропустить шаг\n");
	scanf ("%s", name_dump_file);
	if (strncmp(name_dump_file, "-", 2) == 0)
		return;
	FILE* dump_file = fopen(name_dump_file, "w");
	if (!dump_file)
	{
		printf("Cann't open file %s\n", name_dump_file);
		return;
	}

	fprintf (dump_file,
		"digraph G{\n"
		"	rankdir=TB;\n"
		"	node[shape=\"rectangle\",fontsize=14];\n"
		"	edge[arrowhead=\"open\"];\n");
	int num_node = 0;
	dump_note(tr->root, &num_node, dump_file);

	fprintf (dump_file,
		"}\n");
	fclose(dump_file);
	system ("dot -Tpng tree.dot -o tree.png");
}

#define edge(num1, num2, label)								\
	fprintf (dump_file,										\
		"	V%d->V%d[label=\"%s\"];\n", num1, num2, label)


void dump_note(node* top, int* num_node, FILE* dump_file)
{
	int num_now_node = *num_node;
	(*num_node)++;

	fprintf (dump_file,
		"	V%d[label=\"%s\"];\n", num_now_node, top->data);

	if (left_node(top))
	{
		edge(num_now_node, *num_node, "yes");
		dump_note(left_node(top), num_node, dump_file);
	}

	if (right_node(top))
	{
		edge(num_now_node, *num_node, "no");
		dump_note(right_node(top), num_node, dump_file);
	}
}

void save_tree(const tree* tr)
{
	if (!tr) return;
	printf("Введите имя файла, куда записать получившееся дерево или \"-\", чтобы пропустить шаг?\n");
	char name_file[max_lenght_name_file]  = "";
	scanf("%s", name_file);
	if (strncmp(name_file, "-", 2) == 0)
		return;

	FILE* tree_file = fopen(name_file, "w");
	if (!tree_file)
	{
		printf("Cann't open file \"%s\"\n", name_file);
		return;
	}

	print_node_to_file(tr->root, 0, tree_file);
	fclose(tree_file);
}