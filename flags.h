//  flgs:  1-st       2-nd                  discription                  function    length  need tree?   name   
define_mod("-a", "--akinator",    "launches the akinator program",    akinator(tr),    11,     true,   AKINATOR)
define_mod("-d", "--definition",  "defines a word",                   definition(tr),  13,     true,   DEFINITION)
define_mod("-c", "--comparation", "compares the definition of words", comparation(tr), 14,     true,   COMPARATION)
define_mod("-D", "--dump",        "builds a tree graph",              dump(tr),        7,      true,   DUMP)
define_mod("-h", "--help",        "prints out possible flags",        printf_help(),   7,      false,  HELP)
define_mod("-e", "--exit",        "exits the program",                return,          7,      false,  EXIT)