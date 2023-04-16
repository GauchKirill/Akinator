#include "read_tree.h"

#include <string.h>
#include <ctype.h>
#include <stdlib.h>
#include <sys/stat.h>
#include <sys/types.h>

tree* read_tree_from_text()
{
    printf ("Введите название файла с деревом или \"-\", если хотите продолжить с системным деревом\n");
    char name_file[max_lenght_name_file] = "";
    scanf("%s", name_file);
    getchar();
    if (strncmp(name_file, "-", max_lenght_name_file) == 0)
    {
        tree* tr = TreeCtor(tr);
        if (!tr)
        {
            printf ("Has not memory\n");
            return nullptr;
        }
        return tr;

    } else
        return tree_from_file(name_file);
}

tree* tree_from_file(const char* name_file)
{
    tree* tr = (tree*) calloc(1, sizeof(tree));
    if (!tr)
    {
        printf("Has not memory for tree\n");
        return nullptr;
    }

    const char* buf = get_buf(name_file);
    if (!buf)
        return nullptr;
    tr->root = parse_buf(tr->root, &buf);
    if (!tr->root)
        return nullptr;
    return tr;
}

char* get_buf(const char* name_file)
{
    char* buf;
    struct stat stbuf;
    
    if (stat(name_file, &stbuf) == -1)
    {
        printf ("Can not open file \"%s\"\n", name_file);
        return nullptr;
    }
    else
    {
        size_t size = stbuf.st_size + 1;
        buf = (char*) calloc(size, sizeof(char));
        if (!buf)
        {
            printf("Has not memory for buf\n");
            return nullptr;
        }
        FILE* file = fopen(name_file, "r");
        if (!file)
        {
            printf ("Can not open file \"%s\"\n", name_file);
            return nullptr;
        }

        fread(buf, size, sizeof(char), file);
        buf[size - 1] = '\0';

        fclose(file);
        return buf;
    }
}

node* parse_buf(node* now_node, const char** buf)
{
    char c = get_bracket(buf);

    if (c == '{')
        return parse_block(now_node, buf);
    else if (c == '}')
        return nullptr;
    else
        return syntax_error();
}

node* parse_block(node* now_node, const char** buf)
{
    char data[max_lenght_data] = "";
    int length = strpbrk(*buf, "{}\n") - *buf;
    strncpy(data, *buf + 1, length);
    data[length - 2] = '\0';
    (*buf) += length;
    now_node = make_node(data, nullptr, nullptr);

    left_node(now_node) = parse_buf(left_node(now_node), buf);
    if (left_node(now_node))
    {
        right_node(now_node) = parse_buf(right_node(now_node), buf);
        char c = get_bracket(buf);
        if (c != '}')
            syntax_error();
    }

    return now_node;
}

node* syntax_error()
{
    printf (R"(Invalid input
syntaxis mast be:
node: " { "name" { "left node" } { "right node"} }"
and:  " { "name" } ")");
    return nullptr; 
}

char get_bracket(const char** buf)
{
    char c = 0;
    do
    {
        c = **buf;
        (*buf)++;
    }
    while (isspace(c));
    return c;
}