#include "cli.h"
#include "db.h"
#include <stdio.h>

void cli_menu(database db) {
    string err_msg;
    char input;
    int32_t rs;
    while (1) {
        printf("[A]ll expenses  [U]sers  [E]xit\n");
        input = getchar();
        while (getchar() != '\n');

        switch (input) {
            case 'A':
            case 'a':
                rs = sqlite3_exec(db, QUERY_EXPENSES, cli_display, NULL, &err_msg);
                (void)rs;
                (void)err_msg;
                break;
            case 'U':
            case 'u':
                rs = sqlite3_exec(db, QUERY_USERS, cli_display, NULL, &err_msg);
                (void)rs;
                (void)err_msg;
                break;
            case 'E':
            case 'e':
                return;
        }
    }
}

int32_t cli_display(void* data, int32_t argc, string_ptr argv, string_ptr col_name) {
    for (int i = 0; i < argc; i++) {
        printf("%s  ", argv[i]);
    }
    printf("\n");
    return 0;
}
