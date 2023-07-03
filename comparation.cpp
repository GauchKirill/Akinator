#include "comparation.h"
#include "print.h"
#include "definition.h"
#include "Stack.h"
#include <string.h>

extern elem_t YES;
extern elem_t NO;

#define get_word(num)                                   \
    if (num == 1)                                       \
        printf("Введите первое слово в сравнении\n");   \
    else                                                \
        printf("Введите слово с которым сравнивать\n"); \
                                                        \
    char word ## num [MAX_LENGHT_DATA] = "";            \
    fgets(word_ ## num, MAX_LENGHT_DATA, stdin);        \
    word_ ## num [strlen(word_ ## num) - 1] = '\0';     \
    stack* stk_of_answer_ ## num = nullptr;             \
    stack* stk_of_name_ ## num   = nullptr;             

void comparation(tree* tr)
{
    if (!tr) return;
    // to do...
    char word_1[MAX_LENGHT_DATA] = "";
    char word_2[MAX_LENGHT_DATA] = "";
    get_word(word_1, 1);
    get_word(word_2, 2);

    if (find_def(tr->root, &stk_of_name_1, &stk_of_answer_1, word_1)  == NOT_INSIDE_TREE)
        printf ("Слово \"%s\" не найдено в дереве\n", word_1);
    else if (find_def(tr->root, &stk_of_name_2, &stk_of_answer_2, word_2) == NOT_INSIDE_TREE)
        printf ("Слово \"%s\" не найдено в дереве\n", word_2);
    else
    {
        printf ("\"%s\" похож на \"%s\" тем, что они оба", word_1, word_2);

        while (stk_of_name_1->size > 0 && stk_of_name_2->size > 0)
        {
            char    *definition_1 = nullptr,
                    *definition_2 = nullptr,
                    *answer_1     = nullptr,
                    *answer_2     = nullptr;  
            StackPop (stk_of_name_1,   &definition_1);
            StackPop (stk_of_name_2,   &definition_2);
            StackPop (stk_of_answer_1, &answer_1);
            StackPop (stk_of_answer_2, &answer_2);

            if  ((strncmp(definition_1, definition_2, MAX_LENGHT_DATA  ) == 0) &&
                 (strncmp(answer_1,     answer_2,     MAX_LENGHT_ANSWER) == 0))
            {
                printf(" %s\"%s\"", (strncmp(answer_1, YES, MAX_LENGHT_ANSWER) == 0) ? "" : "не ", definition_1);
                if (stk_of_name_1->size > 0 && stk_of_name_2->size > 0)
                    printf(",");
            } else
            {
                StackPush (stk_of_name_1,   definition_1);
                StackPush (stk_of_name_2,   definition_2);
                StackPush (stk_of_answer_1, answer_1);
                StackPush (stk_of_answer_2, answer_2);

                printf("\nно ");
                print_definition(name_1, stk_of_name_1, stk_of_answer_1);
                printf("А ");
                print_definition(name_2, stk_of_name_2, stk_of_answer_2);
            }
        }
    }
}