#include "cli.h"
#include "db.h"
#include "utils.h"
#include <sqlite3.h>
#include <stdio.h>

void cli_menu(database db) {
    string err_msg;
    char input;
    int32_t rs = SQLITE_OK;
    while (1) {
        printf("[A]ll expenses  [I]nsert data  [U]sers  [E]xit\n");
        input = getchar();
        while (getchar() != '\n');

        switch (input) {
            case 'A':
            case 'a':
                rs = db_exec(db, QUERY_EXPENSES, cli_display, &err_msg);
                break;
            case 'I':
            case 'i':
                cli_insert_menu(db);
                break;
            case 'U':
            case 'u':
                rs = db_exec(db, QUERY_USERS, cli_display, &err_msg);
                break;
            case 'E':
            case 'e':
                return;
        }

        if (rs != SQLITE_OK) {
            fprintf(stderr, "DB Error: %s\n", err_msg);
            sqlite3_free(db);
            return;
        }
    }
}

bool cli_insert_menu(database db) {
    string name = get_string("name >> ");
    string category = get_string("category >> ");
    float amount = get_float("amount >> ");
    string desc = get_string("description >> ");

    int32_t user_id = db_id_by_name(db, "users", name);
    int32_t category_id = db_id_by_name(db, "categories", category);

    if (user_id < 0) {
        user_id = db_insert_name(db, "users", name);
    }

    if (category_id < 0) {
        category_id = db_insert_name(db, "categories", category);
    }

    string date = datetime();
    (void)db_insert_expense(db, user_id, category_id, amount, desc, date);

    free(category);
    free(name);
    return true;
}

int32_t cli_display(void* data, int32_t argc, string_ptr argv, string_ptr col_name) {
    for (int i = 0; i < argc; i++) {
        printf("%s  ", argv[i]);
    }
    printf("\n");
    return 0;
}
