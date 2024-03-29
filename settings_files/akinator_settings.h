#ifndef SETTINGS_H
#define SETTINGS_H

#include <string.h>

const size_t    MAX_LENGHT_DATA         = 100;
const size_t    MAX_LENGHT_NAME_FILE    = 100;
const size_t    MAX_LENGHT_ANSWER       = 8;
const size_t    MAX_LENGHT_INSTRUCTION  = 500;
const size_t    MAX_LENGHT_CMD          = 500;

static char yes_answer[MAX_LENGHT_ANSWER]   = "y";
static char no_answer[MAX_LENGHT_ANSWER]    = "n";
static char cmd_text[MAX_LENGHT_CMD]        = "";

static const elem_t YES = yes_answer;
static const elem_t NO  = no_answer;

#endif  