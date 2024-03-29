#include "../h_files/dump.h"
#include "../h_files/print.h"
#include "../settings_files/akinator_settings.h"
#include <string.h>
#include <stdlib.h>
#include <stdio.h>

void dump(const tree* tr)
{
    if (!tr) 
    {
        reproduce_text("Не валидные указатели.", "russian");
        return;
    }

    char name_file[MAX_LENGHT_NAME_FILE] = "";
    reproduce_text("Введите имя файла без расширения, куда сохранить дерево.", "russian");
    
    fgets(name_file, MAX_LENGHT_NAME_FILE, stdin);

    char system_instruction[MAX_LENGHT_INSTRUCTION] = "";
    sprintf(system_instruction, "%s.dot", name_file);
    FILE* dump_file_ptr = fopen(system_instruction, "w");
    if (!dump_file_ptr)
    {
        sprintf(cmd_text, "Cann't open file %s.dot\n", name_file);
        reproduce_text(cmd_text, "english");
        return;
    }

    fprintf (dump_file_ptr,
        "digraph G{\n"
        "   rankdir=TB;\n"
        "   node[shape=\"rectangle\",fontsize=14];\n"
        "   edge[arrowhead=\"open\"];\n");
    int num_node = 0;
    dump_note(tr->root, &num_node, dump_file_ptr);

    fprintf (dump_file_ptr,
        "}\n");
    fclose(dump_file_ptr);
    
    sprintf(system_instruction, "dot -Tpng %s.dot -o %s.png", name_file, name_file);
    system(system_instruction);

    save_tree(strncat(name_file, ".txt", 5), tr);
    
    return;
}

#define edge(num1, num2, label)                             \
    fprintf (dump_file,                                     \
        "   V%d->V%d[label=\"%s\"];\n", num1, num2, label)


void dump_note(node* top, int* num_node, FILE* dump_file)
{
    int num_now_node = *num_node;
    (*num_node)++;

    fprintf (dump_file,
        "   V%d[label=\"%s\"];\n", num_now_node, top->data);

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

    return;
}

void save_tree(const char* name_file, const tree* tr)
{
    FILE* tree_file = fopen(name_file, "w");
    if (!tree_file)
    {
        sprintf(cmd_text, "Cann't open file \"%s\"\n", name_file);
        reproduce_text(cmd_text, "english");
        return;
    }

    print_node_to_file(tr->root, 0, tree_file);
    fclose(tree_file);

    return;
}