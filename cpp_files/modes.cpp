#include "../h_files/modes.h"
#include "../h_files/read_tree.h"
#include "../h_files/print.h"
#include "../h_files/dump.h"
#include "../settings_files/akinator_settings.h"
#include <string.h>

int get_modes_num(void)
{
    reproduce_text("Введите номер режима:", "russian");

    #define define_mod(short_flag, long_flag, description, function, cnt_char, need_tree, mod_name)   \
        printf("%d - %-15s - %s\n", mod_name, long_flag + 2, description);

    #include "../settings_files/flags.h"

    #undef define_mod

    int modes_num = 0;

    #define define_mod(short_flag, long_flag, description, function, cnt_char, need_tree, mod_name)   \
        case mod_name:                                                                                  \
            return modes_num;

    while (true)
    {
        sprintf(cmd_text, "Ответом должно быть целое число от 0 до %u.", (unsigned) CNT_MODES - 1);
        reproduce_text(cmd_text, "russian");
        while(scanf("%d", &modes_num) != 1)
            scanf("%*s");
        getchar();

        switch (modes_num)
        {
            #include "../settings_files/flags.h"
            default:
                reproduce_text("Такого режима не существует, попробуйте ещё раз.", "russian");
                break;
        }
    }
    
    #undef define_mod
    
    return modes_num;
}

void modes(int argc, const char** argv)
{
    int modes_num = 0;
    
    if (argc == 1)
        modes_num = get_modes_num();
    else
    {
        #define define_mod(short_flag, long_flag, description, function, cnt_char, need_tree, mod_name)       \
            if (strncmp(argv[1], short_flag, cnt_char) == 0 || strncmp(argv[1], long_flag, cnt_char) == 0)    \
                modes_num = mod_name;                                                                           \
            else

        #include "../settings_files/flags.h"
        {
            reproduce_text("Такая команда не найдена.", "russian");
            modes_num = HELP;
        }

        #undef define_mod
    }
    
    const char* name_tree_file = nullptr;

    if (argc == 3)
        name_tree_file = argv[2];

    tree* tr = nullptr;

    while (modes_num != EXIT)
    {
        #define define_mod(short_flag, long_flag, description, function, cnt_char, need_tree, mod_name)       \
            case mod_name:                                                                                      \
                if (need_tree)                                                                                  \
                    tr = get_tree(name_tree_file);                                                              \
                function;                                                                                       \
                break;

        switch (modes_num)
        {
            #include "../settings_files/flags.h"
            default:
                sprintf(cmd_text, "Нет режима с номером %d.", modes_num);
                reproduce_text(cmd_text, "russian");
                break;
        }

        #undef define_mod

        reproduce_text("Хотите продолжить играть?", "russian");
        
        if (get_answer() == 0)
            modes_num = EXIT;
        else
            modes_num = get_modes_num();
    }

    tree_dtor(tr);
    return;
}

#undef define_mod