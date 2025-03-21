#ifndef DB_HEADER
#define DB_HEADER

#include <sqlite3.h>
#include "utils.h"

typedef sqlite3* database;
typedef int32_t(*query_callback_t)(void*,int32_t,string_ptr,string_ptr);

#define QUERY_USERS "SELECT * FROM users;"
#define QUERY_EXPENSES "SELECT users.name,categories.name,amount,description,date FROM expenses JOIN users on user_id = users.id JOIN categories ON category_id = categories.id;"

database db_setup(string_view path);
int32_t db_exec(database db, string_view query, query_callback_t func, string_ptr err_msg);
void db_free(database db);

#endif // DB_HEADER
