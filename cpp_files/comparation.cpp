#include "../h_files/comparation.h"
#include "../h_files/print.h"
#include "../h_files/definition.h"
#include "../Stack/Stack.h"
#include "../settings_files/akinator_settings.h"
#include <string.h>

void get_word(char* word, int num)
{
    if (num == 1)
        reproduce_text("Введите первое слово в сравнении.", "russian");
    else
        reproduce_text("Введите слово с которым сравнивать.", "russian");

    fgets(word, MAX_LENGHT_DATA, stdin);
    word[strlen(word) - 1] = '\0';
}
#define create_stacks(num)                              \
    stack* stk_of_answer_ ## num = nullptr;             \
    stack* stk_of_name_ ## num   = nullptr;  

#define clear_stacks(num)                               \
    StackDtor(stk_of_answer_ ## num);                   \
    StackDtor(stk_of_name_ ## num);

#define get_description(num)                                \
    StackPop (stk_of_name_ ## num,   &description_ ## num); \
    StackPop (stk_of_answer_ ## num, &answer_ ## num);

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
    while (true)
    {
        if (!tr) return;
        
        char word_1[MAX_LENGHT_DATA] = "";
        char word_2[MAX_LENGHT_DATA] = "";

        get_word(word_1, 1);
        get_word(word_2, 2);

        create_stacks(1)
        create_stacks(2)

        if (find_def(tr->root, &stk_of_name_1, &stk_of_answer_1, word_1) == NOT_INSIDE_TREE)
        {
            sprintf(cmd_text, "Слово \"%s\" не найдено в дереве.", word_1);
            reproduce_text(cmd_text, "russian");
        }
        else
        if (find_def(tr->root, &stk_of_name_2, &stk_of_answer_2, word_2) == NOT_INSIDE_TREE)
        {
            sprintf(cmd_text, "Слово \"%s\" не найдено в дереве.", word_2);
            reproduce_text(cmd_text, "russian");
        }    
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
                char description[3 * MAX_LENGHT_DATA] = ""; //word_1, word_2 + over words
                sprintf(description, "У \"%s\" и у \"%s\" есть сходства:\nОни ", word_1, word_2);
                strncat(cmd_text, description, MAX_LENGHT_DATA);
                unsigned end_flag = 0;

                do
                {
                    sprintf(description, "%s\"%s\"", (strncmp(answer_1, YES, MAX_LENGHT_ANSWER) == 0) ? "" : "не ", description_1);
                    strncat(cmd_text, description, MAX_LENGHT_DATA);

                    if (stk_of_name_1->size > 0 && stk_of_name_2->size > 0)
                        strncat(cmd_text, ", ", MAX_LENGHT_DATA);
                    else
                    {
                        strncat(cmd_text, ".", MAX_LENGHT_DATA);
                        reproduce_text(cmd_text, "russian");
                        end_flag = 1;
                    }

                    if (!end_flag)
                    {
                        get_description(1)
                        get_description(2)
                    }
                    

                } while (description_cmp(description_1, description_2, answer_1, answer_2) == 0);

                if(!end_flag)
                    reproduce_text("однако есть и различия:", "russian");
                
            }
            else
            {
                sprintf(cmd_text, "\"%s\" и \"%s\" полностью разлины.", word_1, word_2);
                reproduce_text(cmd_text, "russian");
            }
                
            
            StackPush(stk_of_name_1, description_1);
            StackPush(stk_of_name_2, description_2);
            StackPush(stk_of_answer_1, answer_1);
            StackPush(stk_of_answer_2, answer_2);
            print_definition(word_1, stk_of_name_1, stk_of_answer_1);
            print_definition(word_2, stk_of_name_2, stk_of_answer_2);
        }

        reproduce_text("Хотите продолжить сравнивать слова?", "russian");

        clear_stacks(1)
        clear_stacks(2)

        if(get_answer() == 0) break;
    }    
}

#undef get_description
#undef create_stacks
#undef clear_stacks