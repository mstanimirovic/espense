#include "espense.h"

database db = NULL;

int32_t main(int32_t argc, string argv[]) {
    db = db_setup("data.db");
    cli_menu(db);
    db_free(db);
}
