#ifndef CLI_HEADER
#define CLI_HEADER

#include "utils.h"
#include "db.h"

void cli_menu(database db);
int32_t cli_display(void* data, int32_t argc, string_ptr argv, string_ptr col_name);

#endif
