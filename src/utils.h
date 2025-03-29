#ifndef UTILS_HEADER
#define UTILS_HEADER

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <stdint.h>
#include <stdbool.h>

typedef char* string;
typedef char** string_ptr;
typedef const char* string_view;

// input functions
int32_t get_integer(string_view prompt);
string get_string(string_view prompt);
float get_float(string_view prompt);

int32_t str_to_int(string_view str);
void zero_out(string str, int32_t n);

string datetime(void);
void strip(string str);

#endif
