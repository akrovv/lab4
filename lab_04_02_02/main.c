#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <stddef.h>
#include <string.h>
#include <ctype.h>

#define STR_INPUT_ERROR 1
#define STR_WORD_SIZE_ERROR 2
#define STR_EMPTY_ERROR 3

#define MAX_STR_LEN 512
#define STR_LEN 256
#define MAX_WORD_LEN 16

bool is_occurrence_word(char word[], size_t len2, char array_words2[][STR_LEN]);
bool str_split(char str[], char array_words[][STR_LEN], size_t *len, char delims[]);
void str_print(size_t len1, char array_words1[][STR_LEN], size_t len2, char array_words2[][STR_LEN]);

int main(void) 
{
    char str1[MAX_STR_LEN];
    char str2[MAX_STR_LEN];

    char delims[] = " ,;:-.!?\n";

    char array_words1[STR_LEN][STR_LEN];
    char array_words2[STR_LEN][STR_LEN];

    size_t len1;
    size_t len2;

    if (fgets(str1, MAX_STR_LEN, stdin) == NULL || strlen(str1) > STR_LEN)
        return STR_INPUT_ERROR;

    if (fgets(str2, MAX_STR_LEN, stdin) == NULL || strlen(str2) > STR_LEN)
        return STR_INPUT_ERROR;

    if (!str_split(str1, array_words1, &len1, delims))
        return STR_WORD_SIZE_ERROR;

    if (!str_split(str2, array_words2, &len2, delims))
        return STR_WORD_SIZE_ERROR;

    if (!len1 || !len2)
        return STR_EMPTY_ERROR;

    str_print(len1, array_words1, len2, array_words2);

    return EXIT_SUCCESS;
}

bool str_split(char str[], char array_words[][STR_LEN], size_t *len, char delims[])
{
    size_t k = 0;

    for (size_t i = 0; str[i]; i++)
    {
        char word[MAX_WORD_LEN + 1] = "";

        for (size_t j = 0; str[i] && !strchr(delims, str[i]); i++, j++)
        {
            if (j > MAX_WORD_LEN)
                return false;
            word[j] = str[i];
        }
        if (*word)
        {
            strncpy(array_words[k], word, MAX_WORD_LEN);
            k++;
        }
    }

    *len = k;

    return true;
}

bool is_previous(size_t words_pos, char array_words[][STR_LEN])
{
    if (words_pos == 0)
        return false;

    for (int i = (int)words_pos - 1; i != -1; i--)
        if (!strcmp(array_words[i], array_words[words_pos]))
            return true;
    
    return false;
}

bool is_occurrence_word(char word[], size_t len2, char array_words2[][STR_LEN])
{
    for (size_t j = 0; j < len2; j++)
        if (!strcmp(word, array_words2[j]))
            return true;
    
    return false;
}

void str_print(size_t len1, char array_words1[][STR_LEN], size_t len2, char array_words2[][STR_LEN])
{
    for (size_t i = 0; i < len1; i++)
        if (!is_previous(i, array_words1))
        {
            if (is_occurrence_word(array_words1[i], len2, array_words2))
                printf("Result:%s yes\n", array_words1[i]);
            else
                printf("Result:%s no\n", array_words1[i]);
        }
}
