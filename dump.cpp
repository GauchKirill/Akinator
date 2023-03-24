#include "dump.h"

#include "print.h"

void dump(tree* tr)
{
	if (!tr) return;
	char name_dump_file[max_lenght_name_file] = {0};
	printf ("\nВведите название файла для диагностики\n");
	scanf ("%s", name_dump_file);

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
	printf("Куда записать получившееся дерево?\n");
	char name_tree_file[max_lenght_name_file]  = {0};
	scanf("%s", name_tree_file);

	FILE* tree_file = fopen(name_tree_file, "w");
	if (!tree_file)
	{
		printf("Cann't open file \"%s\"\n", name_tree_file);
		return;
	}

	print_node_to_file(tr->root, 0, tree_file);
}