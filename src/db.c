#include "db.h"
#include "utils.h"
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

int32_t db_id_by_name(database db, string table, string_view name) {
    char query[255];
    zero_out(query, 255);
    sprintf(query, "SELECT id FROM %s WHERE name = ?", table);
    sqlite3_stmt *stmt;
    int32_t rc = sqlite3_prepare_v2(db, query, -1, &stmt, 0);
    if (rc != SQLITE_OK) {
        fprintf(stderr, "Failed to prepare statement: %s\n", sqlite3_errmsg(db));
        return -1;
    }

    // binding name to placeholder
    sqlite3_bind_text(stmt, 1, name, -1, SQLITE_STATIC);

    int32_t id = -1;
    rc = sqlite3_step(stmt);
    if (rc == SQLITE_ROW) {
        id = sqlite3_column_int(stmt, 0);
    }
    else if (rc != SQLITE_DONE) {
        fprintf(stderr, "Execution failed: %s\n", sqlite3_errmsg(db));
        sqlite3_finalize(stmt);
        return -1;
    }

    sqlite3_finalize(stmt);
    return id;
}

int32_t db_insert_name(database db, string table, string_view name) {
    char query[255];
    sprintf(query, "INSERT INTO %s (name) VALUES (?);", table);
    sqlite3_stmt *stmt;
    int32_t rc = sqlite3_prepare_v2(db, query, -1, &stmt, 0);
    if (rc != SQLITE_OK) {
        fprintf(stderr, "Failed to prepare statement: %s\n", sqlite3_errmsg(db));
        return -1;
    }

    // binding name to placeholder
    sqlite3_bind_text(stmt, 1, name, -1, SQLITE_STATIC);

    rc = sqlite3_step(stmt);
    if (rc != SQLITE_DONE) {
        fprintf(stderr, "Execution failed: %s\n", sqlite3_errmsg(db));
        sqlite3_finalize(stmt);
        return -1;
    }

    int32_t id = (int32_t)sqlite3_last_insert_rowid(db);
    sqlite3_finalize(stmt);
    return id;
}

bool db_insert_expense(database db, int32_t user_id, int32_t category_id, double amount, string desc, string date) {
    sqlite3_stmt *stmt;
    int32_t rc = sqlite3_prepare_v2(db, QUERY_INSERT_EXPENSE, -1, &stmt, 0);
    if (rc != SQLITE_OK) {
        fprintf(stderr, "Failed to prepare statement: %s\n", sqlite3_errmsg(db));
        return false;
    }

    // binding name to placeholder
    sqlite3_bind_int(stmt, 1, user_id);
    sqlite3_bind_int(stmt, 2, category_id);
    sqlite3_bind_double(stmt, 3, amount);
    sqlite3_bind_text(stmt, 4, desc, -1, SQLITE_STATIC);
    sqlite3_bind_text(stmt, 5, date, -1, SQLITE_STATIC);

    rc = sqlite3_step(stmt);
    if (rc != SQLITE_DONE) {
        fprintf(stderr, "Execution failed: %s\n", sqlite3_errmsg(db));
        sqlite3_finalize(stmt);
        return false;
    }

    sqlite3_finalize(stmt);
    return true;
}

void db_free(database db) {
    sqlite3_close(db);
}
