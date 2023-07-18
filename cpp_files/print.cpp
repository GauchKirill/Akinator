#include "../h_files/print.h"
#include "../settings_files/akinator_settings.h"
#include <string.h>
#include <stdlib.h>

void print_node_to_file(const node* now_node, size_t num_layer, FILE* tree_file)
{
    if (!left_node(now_node) || !right_node(now_node))
    {
        print_tabs(num_layer);
        fprintf(tree_file, "{ %s }\n", node_data(now_node));
    }
    else
    {
        print_tabs(num_layer);
        fprintf(tree_file,
            "{ %s \n", node_data(now_node));
        print_node_to_file(left_node(now_node),  num_layer+1, tree_file);
        print_node_to_file(right_node(now_node), num_layer+1, tree_file);
        print_tabs(num_layer);
        fprintf(tree_file, "}\n");
    }
}

void print_definition(elem_t name, stack* name_stk, stack* answer_stk)
{
    if (name_stk->size == 0)
        return;
    
    printf("\"%s\" это", name);

    while(name_stk->size > 0)
    {
        char* definition = nullptr;
        char* answer     = nullptr; 
        StackPop (name_stk,   &definition);
        StackPop (answer_stk, &answer);
        printf(" %s\"%s\"", (strncmp(answer, YES, MAX_LENGHT_ANSWER) == 0) ? "" : "не ", definition);
        if (name_stk->size > 0)
            printf (",");
        else
            printf (".");
    }
    printf("\n""");
}

int get_answer(void)
{
    char* answer = nullptr;
    int is_no = 0;
    do
    {
        if (answer) free(answer);
        sprintf(cmd_text, "Введите \"%s\" (да) или \"%s\" (нет)?", YES, NO);
        reproduce_text(cmd_text, "russian");
        scanf("%ms", &answer);
        getchar();
    }
    while ((is_no = strncmp(answer, NO,  MAX_LENGHT_ANSWER)) != 0 &&
                    strncmp(answer, YES, MAX_LENGHT_ANSWER)  != 0 );

    free(answer);
    return is_no;
}

#define define_mod(short_flag, long_flag, description, ...)           \
    printf("%-3s    %-15s   %-s\n", short_flag, long_flag, description);

void printf_help(void)
{
    #include "../settings_files/flags.h"
}

void reproduce_text(const char* text, const char* language)
{
    char cmd[MAX_LENGHT_INSTRUCTION] = "";
    printf("\n"
            "%s\n", text);
    sprintf(cmd, "echo \"%s\" | festival --tts --language %s",
            text, language);
    system(cmd);
    return;
}

#undef define_mod