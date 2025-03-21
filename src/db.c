#include "db.h"
#include <sqlite3.h>
#include <stdio.h>

database db_setup(string_view path) {
    database tmp;
    int32_t rs;

    rs = sqlite3_open(path, &tmp);
    if (rs) {
        fprintf(stderr, "error sqlite3_open: %s\n", sqlite3_errmsg(tmp));
        return NULL;
    }

    return tmp;
}

int32_t db_exec(
    database db,
    string_view query,
    query_callback_t func,
    string_ptr err_msg
) {
    return sqlite3_exec(db, query, func, NULL, err_msg);
}

void db_free(database db) {
    sqlite3_close(db);
}
