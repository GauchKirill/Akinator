#include "comparation.h"
#include "print.h"
#include "definition.h"
#include "Stack.h"
#include <string.h>

extern Elem_t YES;
extern Elem_t NO;

void comparation(tree* tr)
{
    if (!tr) return;

    char name_1[max_lenght_data] = "";
    printf ("Введите первое слово в сравнении\n");
    fgets(name_1, max_lenght_data, stdin);
    name_1[strlen(name_1) - 1] = '\0';
    stack* answer_stk_1 = nullptr;
    stack* name_stk_1   = nullptr;

    char name_2[max_lenght_data] = "";
    printf ("Введите слово с которым сравнивать\n");
    fgets(name_2, max_lenght_data, stdin);
    name_2[strlen(name_2) - 1] = '\0';
    stack* answer_stk_2 = nullptr;
    stack* name_stk_2   = nullptr;

    if (make_stacks(name_1, tr, &name_stk_1, &answer_stk_1) == NOT_INSIDE_TREE)
        printf ("Слово \"%s\" не найдено в дереве\n", name_1);
    else if (make_stacks(name_2, tr, &name_stk_2, &answer_stk_2) == NOT_INSIDE_TREE)
        printf ("Слово \"%s\" не найдено в дереве\n", name_2);
    else
    {
        printf ("\"%s\" похож на \"%s\" тем, что они оба", name_1, name_2);

        while (name_stk_1->size > 0 && name_stk_2->size > 0)
        {
            char    *definition_1 = nullptr,
                    *definition_2 = nullptr,
                    *answer_1     = nullptr,
                    *answer_2     = nullptr;  
            StackPop (name_stk_1,   &definition_1);
            StackPop (name_stk_2,   &definition_2);
            StackPop (answer_stk_1, &answer_1);
            StackPop (answer_stk_2, &answer_2);

            if  ((strncmp(definition_1, definition_2, max_lenght_data  ) == 0) &&
                 (strncmp(answer_1,     answer_2,     max_lenght_answer) == 0))
            {
                printf(" %s\"%s\"", (strncmp(answer_1, YES, max_lenght_answer) == 0) ? "" : "не ", definition_1);
                if (name_stk_1->size > 0 && name_stk_2->size > 0)
                    printf(",");
            } else
            {
                StackPush (name_stk_1,   definition_1);
                StackPush (name_stk_2,   definition_2);
                StackPush (answer_stk_1, answer_1);
                StackPush (answer_stk_2, answer_2);

                printf("\nно ");
                print_definition(name_1, name_stk_1, answer_stk_1);
                printf("А ");
                print_definition(name_2, name_stk_2, answer_stk_2);
            }
        }
    }
}