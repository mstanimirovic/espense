#include "utils.h"

void zero_out(string str, int32_t n) {
    for (int i = 0; i < n; i++)
        str[i] = 0;
}

int32_t str_to_int(string_view str) {
    int32_t result = 0;
    while (*str != '\0') {
        if (*str < 48 || *str > 57) return INT32_MIN;
        result *= 10;
        result += *str - 48;
        str++;
    }
    return result;
}

int32_t get_integer(string_view prompt) {
    char buffer[255];
    int32_t result;
    while (true) {
        printf("%s", prompt);
        if (fgets(buffer, 255, stdin) == NULL) {
            printf("something went wrong, try again\n");
            fflush(stdin);
            zero_out(buffer, 255);
            continue;
        }

        strip(buffer);
        result = str_to_int(buffer);
        if (result == INT32_MIN) {
            printf("please enter a number\n");
            fflush(stdin);
            zero_out(buffer, 255);
            continue;
        }

        return result;
    }
}

string get_string(string_view prompt) {
    string buffer = (string)malloc(sizeof(char) * 255);
    while (true) {
        printf("%s", prompt);
        if (fgets(buffer, 255, stdin) == NULL) {
            printf("something went wrong, try again\n");
            fflush(stdin);
            zero_out(buffer, 255);
            continue;
        }
        strip(buffer);
        return buffer;
    }
}

string datetime(void) {
    FILE* fptr = popen("date", "r");
    string buffer = (string)malloc(sizeof(char) * 80);
    fgets(buffer, 80, fptr);
    pclose(fptr);
    return buffer;
}

void strip(string str) {
    while (*str != '\0') str++;
    str--;
    while (true) {
        if (*str == ' '
            || *str == '\n'
            || *str == '\t'
            || *str == '\r')
            *str = '\0';
        else break;
        str--;
    }
}
