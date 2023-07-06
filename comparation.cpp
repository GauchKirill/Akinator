#include "comparation.h"
#include "print.h"
#include "definition.h"
#include "Stack.h"
#include "settings.h"
#include <string.h>

extern elem_t YES;
extern elem_t NO ;

void get_word(char* word, int num)
{
    if (num == 1)
        printf("\nВведите первое слово в сравнении.\n");
    else
        printf("\nВведите слово с которым сравнивать.\n");

    fgets(word, MAX_LENGHT_DATA, stdin);
    word[strlen(word) - 1] = '\0';
}
#define create_stacks(num)                              \
    stack* stk_of_answer_ ## num = nullptr;             \
    stack* stk_of_name_ ## num   = nullptr;  

#define get_description(num)                                \
    StackPop (stk_of_name_ ## num,   &description_ ## num); \
    StackPop (stk_of_answer_ ## num, &answer_ ## num);

#define print_difference                                        \
    StackPush(stk_of_name_1, description_1);                    \
    StackPush(stk_of_name_2, description_2);                    \
    StackPush(stk_of_answer_1, answer_1);                       \
    StackPush(stk_of_answer_2, answer_2);                       \
    print_definition(word_1, stk_of_name_1, stk_of_answer_1);   \
    print_definition(word_2, stk_of_name_2, stk_of_answer_2);

int description_cmp(char* description_1, char* description_2, char* answer_1, char* answer_2)
{
    if ((strncmp(description_1, description_2, MAX_LENGHT_DATA) == 0) &&
        (strncmp(answer_1,     answer_2,     MAX_LENGHT_ANSWER) == 0))
        return 0;
    else
        return 1;    
}

void comparation(tree* tr)
{
    if (!tr) return;
    
    char word_1[MAX_LENGHT_DATA] = "";
    char word_2[MAX_LENGHT_DATA] = "";

    get_word(word_1, 1);
    get_word(word_2, 2);

    create_stacks(1)
    create_stacks(2)

    if (find_def(tr->root, &stk_of_name_1, &stk_of_answer_1, word_1) == NOT_INSIDE_TREE)
        printf ("\nСлово \"%s\" не найдено в дереве.\n", word_1);

    else
    if (find_def(tr->root, &stk_of_name_2, &stk_of_answer_2, word_2) == NOT_INSIDE_TREE)
        printf ("\nСлово \"%s\" не найдено в дереве.\n", word_2);
    
    else
    {
        char    *description_1 = nullptr,
                *description_2 = nullptr,
                *answer_1     = nullptr,
                *answer_2     = nullptr;

        get_description(1)
        get_description(2)

        if (description_cmp(description_1, description_2, answer_1, answer_2) == 0)
        {
            printf("\nУ \"%s\" и у \"%s\" есть сходства:\nОни ", word_1, word_2);
            do
            {
                printf("%s\"%s\"", (strncmp(answer_1, YES, MAX_LENGHT_ANSWER) == 0) ? "" : "не ", description_1);        

                if (stk_of_name_1->size > 0 && stk_of_name_2->size > 0)
                    printf(", ");
                else
                {
                    printf(".\n");
                    return;
                }
                get_description(1)
                get_description(2)

            } while (description_cmp(description_1, description_2, answer_1, answer_2) == 0);

            printf("однако есть и различия:\n");
            print_difference
            
        }
        else
        {
            printf("\n\"%s\" и \"%s\" полностью разлины.\n", word_1, word_2);
            print_difference

        }
    }
}

#undef get_description
#undef create_stacks
#undef print_difference