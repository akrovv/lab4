#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stddef.h>
#include <stdbool.h>

#define STR_SIZE 257
#define ARRAY_SIZE 1024

char *my_strpbrk(char str[], char sym[]);
size_t my_strspn(char str[], char sym[]);
size_t my_strcspn(char str[], char sym[]);
char *my_strchr(char str[], int symbol);
char *my_strrchr(char str[], int symbol);

int main(void)
{
    size_t error_count = 0;
    char test_str_array[STR_SIZE][STR_SIZE] = { "How are you?", "LOST: 4-8-15-16-23-42", "0123456789", "xyzbxz", "xyzbxz", "hell", "hell", "", "\0" };
    char test_sym_array[STR_SIZE][STR_SIZE] = { "?", "1234567890", "9876", "abc", "xyz", "word", "hword", "", "\0" };
    char test_str_digit[STR_SIZE][STR_SIZE] = { "8He1llo 8world", "0123456789", "l5rd", "51123123", "Lord of the R0ng", "81", "95123", "", "0" };
    int test_sym_digit[ARRAY_SIZE] = { '8', '7', '1', '1', 0, '9', '5', 1, 4 };
    
    for (size_t i = 0; *test_str_array[i]; i++)
    {
        if (my_strpbrk(test_str_array[i], test_sym_array[i]) != strpbrk(test_str_array[i], test_sym_array[i]))
            error_count++;

        if (my_strspn(test_str_array[i], test_sym_array[i]) != strspn(test_str_array[i], test_sym_array[i]))
            error_count++;

        if (my_strcspn(test_str_array[i], test_sym_array[i]) != strcspn(test_str_array[i], test_sym_array[i]))
            error_count++;

        if (my_strchr(test_str_digit[i], test_sym_digit[i]) != strchr(test_str_digit[i], test_sym_digit[i]))
            error_count++;
               
        if (my_strrchr(test_str_digit[i], test_sym_digit[i]) != strrchr(test_str_digit[i], test_sym_digit[i]))
            error_count++;
    }

    printf("%zu\n", error_count);

    return EXIT_SUCCESS;
}

char *my_strpbrk(char str[], char sym[])
{
    for (size_t i = 0; str[i]; i++)
        for (size_t j = 0; sym[j]; j++)
            if (str[i] == sym[j])
                return str + i;

    return NULL;
}

size_t my_strspn(char str[], char sym[])
{
    size_t i = 0;
    bool flag;

    for (; str[i]; i++)
    {
        flag = true;
        
        for (size_t j = 0; sym[j]; j++)
            if (str[i] == sym[j])
                flag = false;

        if (flag)
            return i;
    }

    return i;
}

size_t my_strcspn(char str[], char sym[])
{
    size_t i = 0;

    for (; str[i]; i++)
        for (size_t j = 0; sym[j]; j++)
            if (sym[j] == str[i])
                return i;

    return i;
}


char *my_strchr(char str[], int symbol)
{
    size_t i;

    for (i = 0; str[i]; i++)
        if (str[i] == symbol)
            return str + i;

    if (str[i] == symbol)
        return str + i;

    return NULL;
}

char *my_strrchr(char str[], int symbol)
{
    bool flag = true;
    size_t i;
    size_t start_index = 0;


    for (i = 0; str[i]; i++)
    {
        if (str[i] == symbol)
        {
            flag = false;
            start_index = i;
        }
    }

    if (str[i] == symbol)
        return str + i;

    return (flag) ? NULL : str + start_index;
}
