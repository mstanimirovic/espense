#ifndef DB_HEADER
#define DB_HEADER

#include <sqlite3.h>
#include "utils.h"

typedef sqlite3* database;
typedef int32_t(*query_callback_t)(void*,int32_t,string_ptr,string_ptr);

#define QUERY_USERS "SELECT * FROM users;"
#define QUERY_EXPENSES "SELECT users.name,categories.name,amount,description,date FROM expenses JOIN users on user_id = users.id JOIN categories ON category_id = categories.id;"

#define QUERY_INSERT_EXPENSE "INSERT INTO expenses (user_id, category_id, amount, date) VALUES (?, ?, ?, ?);"

database db_setup(string_view path);
int32_t db_exec(database db, string_view query, query_callback_t func, string_ptr err_msg);
int32_t db_id_by_name(database id, string table, string_view name);
int32_t db_insert_name(database db, string table, string_view name);
bool db_insert_expense(database db, int32_t user_id, int32_t category_id, double amount, string date);
void db_free(database db);

#endif // DB_HEADER
