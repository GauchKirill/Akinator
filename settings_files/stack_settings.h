#ifndef STACK_SETTINGS_H
#define STACK_SETTINGS_H

#include "elem_settings.h"
#include <stdio.h>

elem_t      POISON          = nullptr;
const int   MIN_SIZE_DATA   = 4;
const char* log_file_name   = (const char*) "log_file.txt";
FILE*       log_stream      = nullptr;

#endif