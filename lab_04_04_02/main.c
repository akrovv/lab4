#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <stddef.h>
#include <string.h>
#include <ctype.h>

#define STR_INPUT_ERROR 1
#define STR_SIZE_ERROR 2
#define STR_WORD_SIZE_ERROR 3
#define STR_EMPTY_SIZE_ERROR 4
#define STR_EMPTY_ERROR 5

#define MAX_STR_LEN 300
#define STR_LEN 256
#define MAX_WORD_LEN 16

bool regular_months_expr(char str[], char months[][STR_LEN]);

int main(void) 
{
    char str[MAX_STR_LEN];

    char months[STR_LEN][STR_LEN] = { "january", "february", "march", "april", "may", "june", "july", "august", "september", "october", "november", "december" }; 

    if (fgets(str, MAX_STR_LEN, stdin) == NULL || strlen(str) > STR_LEN)
        return STR_INPUT_ERROR;

    if (!str[0])
        return STR_SIZE_ERROR;

    if (regular_months_expr(str, months))
        printf("YES\n");
    else
        printf("NO\n");

    return EXIT_SUCCESS;
}

void capitalize(char str[]) 
{
    for (size_t i = 0; i < strlen(str); i++)
        str[i] = tolower(str[i]);
}

bool is_leap(size_t year)
{
    return (year % 4 == 0 && year % 100 != 0) || year % 400 == 0;
}

bool is_month(char str[], char months[][STR_LEN], int *number_month)
{
    for (int i = 0; i < 12; i++)
        if (!strcmp(str, months[i]))
        {
            *number_month = i + 1;
            return true;
        }
    return false;
}

size_t str_date(char str[], size_t i, char day[], char signs[])
{
    size_t j = 0;

    for (; !isalpha(str[i]) && !strchr(signs, str[i]); i++)
        if (isdigit(str[i]))
            day[j++] = str[i];

    day[j] = '\0';

    if (strlen(day) < 2 || !isdigit(str[i - 2]) || !isspace(str[i - 1]))
        return 0;

    return i;
}

size_t str_month(char str[], size_t i, char month[], char signs[])
{
    size_t j = 0;

    while (isalpha(str[i]) && !strchr(signs, str[i]))
    {
        month[j] = str[i];
        i++;
        j++;
    }

    month[j] = '\0';

    if (!isspace(str[i]) || !isdigit(str[i + 1]) || !j)
        return 0;

    return i;
}

size_t str_year(char str[], size_t i, char year[], char signs[])
{
    size_t j = 0;

    for (; str[i] && !strchr(signs, str[i]); i++)
        if (isdigit(str[i]))
            year[j++] = str[i];

    year[j] = '\0';

    if (strlen(year) < 4)
        return 0;

    return i;
}


bool regular_months_expr(char str[], char months[][STR_LEN])
{
    size_t i = 0;

    int number_month = 0;

    char day[STR_LEN];
    char month[STR_LEN];
    char year[STR_LEN];

    char signs[] = "<,.>/?;:'\"[{}]\\|!@#$%^&*()-_=+";

    day[0] = '\0';

    i = str_date(str, i, day, signs);

    if (!i)
        return false;

    month[0] = '\0';

    i = str_month(str, i, month, signs);

    if (!i)
        return false;

    capitalize(month);
    if (!is_month(month, months, &number_month))
        return false;

    i = str_year(str, i, year, signs);

    if (!i)
        return false;

    int int_day = atoi(day);
    int int_year = atoi(year);

    if (int_day > 31 || int_year > 9999 || int_year < 1000 || int_day == 0 || int_year == 0)
        return false;

    int current_count_day = 28 + (number_month + number_month / 8) % 2 + 2 % number_month + 1 / number_month * 2;

    if (number_month == 2)
    {
        if (int_day == 29 && !is_leap(int_year))
            return false;
        else if (int_day == 28 && is_leap(int_year))
            return false;
    }
    else if (int_day > current_count_day)
        return false;

    return true;
}
