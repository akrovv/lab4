#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <stddef.h>
#include <string.h>

#define STR_INPUT_ERROR 1
#define STR_WORD_SIZE_ERROR 2
#define STR_EMPTY_SIZE_ERROR 3
#define STR_EMPTY_ERROR 4

#define MAX_STR_LEN 300
#define STR_LEN 256
#define MAX_WORD_LEN 16

bool str_split(char str[], char array_words[][STR_LEN], size_t *len, char delims[]);
void delete_subsequent_letters(char array_words[]);
void str_from_words_array(char new_str[], size_t len, char array_words[][STR_LEN], size_t *new_len);
void arr_delete_repeats(char array_words[][STR_LEN], size_t *len, char word[]);
void arr_delete(char array_words[][STR_LEN], size_t *len, size_t pos);
void change_words(char array_words[][STR_LEN], size_t len);

int main(void) 
{
    char str[MAX_STR_LEN];
    size_t len = 0;

    char new_str[MAX_STR_LEN];
    size_t new_len = 0;

    char delims[] = " ,;:-.!?\n";

    char array_words[STR_LEN][STR_LEN];

    if (fgets(str, MAX_STR_LEN, stdin) == NULL || strlen(str) > STR_LEN)
        return STR_INPUT_ERROR;

    if (!str_split(str, array_words, &len, delims))
        return STR_WORD_SIZE_ERROR;

    if (!len)
        return STR_EMPTY_SIZE_ERROR;

    arr_delete_repeats(array_words, &len, array_words[len - 1]);

    change_words(array_words, len);

    str_from_words_array(new_str, len, array_words, &new_len);

    if (!new_len)
        return STR_EMPTY_ERROR;

    printf("Result: %s\n", new_str);

    return EXIT_SUCCESS;
}

void arr_delete(char array_words[][STR_LEN], size_t *len, size_t pos)
{
    for (size_t i = pos; i < *len - 1; i ++)
        strncpy(array_words[i], array_words[i + 1], MAX_WORD_LEN);

    (*len)--;
}

void arr_delete_repeats(char array_words[][STR_LEN], size_t *len, char word[])
{
    size_t i = 0;

    while (i < *len)
        if (strncmp(array_words[i], word, MAX_WORD_LEN) == 0)
            arr_delete(array_words, len, i);
        else
            i++;
}

void delete_subsequent_letters(char array_words[])
{
    for (size_t i = 1; array_words[i]; i++)
        if (array_words[i] == array_words[0])
        {
            size_t j;
            
            for (j = i; j < strlen(array_words) - 1; j++)
            {
                char tmp = array_words[j];
                array_words[j] = array_words[j + 1];
                array_words[j + 1] = tmp;
            }
            array_words[j] = '\0';
            i--;
        }
}

void change_words(char array_words[][STR_LEN], size_t len)
{
    for (size_t i = 0; i < len; i++)
        delete_subsequent_letters(array_words[i]);
}

void str_from_words_array(char new_str[], size_t len, char array_words[][STR_LEN], size_t *new_len)
{
    size_t k = 0;

    for (int i = (int) len - 1; i != -1; i--)
    {
        size_t j = 0;
        while (array_words[i][j])
            new_str[k++] = array_words[i][j++];

        if (i != 0)
            new_str[k++] = ' ';

        (*new_len)++;
    }

    new_str[k] = '\0';
}

bool str_split(char str[], char array_words[][STR_LEN], size_t *len, char delims[])
{
    char *p = strtok(str, delims);

    while (p != NULL) 
    {
        strncpy(array_words[*len], p, MAX_WORD_LEN);
        if (array_words[*len][MAX_WORD_LEN - 1] != '\0')
            return false;

        (*len)++;
        p = strtok(NULL, delims);
    }

    return true;
}
