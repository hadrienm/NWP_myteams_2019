/*
** EPITECH PROJECT, 2020
** NWP_myteams_2019
** File description:
** str_to_word_array
*/

#include <stddef.h>
#include <stdlib.h>
#include <string.h>

static int isin(char *c, char *str, int n)
{
    for (int i = 0; str[i] != '\0'; ++i, ++n) {
        if (c[n] == '\0')
            return 0;
        if (c[n] != str[i])
            return 0;
    }
    return 1;
}

static char **word_array(char *str, char *delimiter, int n)
{
    int j = 0;
    int k = 0;
    int m = 0;

    if (str == NULL || str[0] == '\0' || strcmp(str, delimiter) == 0)
        return NULL;
    char **array = malloc(sizeof(char *) * (n + 1));
    for (int i = 0; i <= (int)strlen(str) && str[i] != '\0';) {
        for (j = i; str[j] != '\0' && !(isin(str, delimiter, j)); ++j);
        array[k] = malloc(sizeof(char) * (j + 2));
        for (j = i, m = 0; str[j] != '\0' && \
!(isin(str, delimiter, j)); ++j, ++m)
            array[k][m] = str[j];
        j += (strlen(delimiter));
        array[k][m] = '\0';
        ++k;
        i = j;
        if (i <= (int)strlen(str) && str[i] == '\0') break;
    }
    array[k] = NULL;
    return array;
}

char *delete_useless(char *str, char *delimiter)
{
    char *str2 = NULL;
    int n = 0;
    int i = 0;
    int j = 0;

    for (i = 0; isin(str, delimiter, i) && str[i] != '\0'; ++i);
    for (j = (int)strlen(str) - 1; j >= 0 && isin(str, delimiter, j); --j);
    n = (j - i) + 1;
    if (n <= 0)
        return NULL;
    str2 = malloc(sizeof(char) * (n + 1));
    if (str2 == NULL)
        return NULL;
    int end = 0;
    for (int k = i; k <= j && str[k] != '\0'; ++k, ++end)
        str2[end] = str[k];
    str2[end] = '\0';
    return str2;
}

char **str_to_word_array(char *str, char *delimiter)
{
    int n = 0;
    char *str2 = delete_useless(str, " ");
    for (int i = 0; str[i]; ++i) {
        if (isin(str, delimiter, i))
            ++n;
    }
    char **value = word_array(str2, delimiter, n+1);
    free(str2);
    return value;
}