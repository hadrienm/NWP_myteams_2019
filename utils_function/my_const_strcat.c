/*
** EPITECH PROJECT, 2020
** NWP_myteams_2019
** File description:
** my_strcat
*/

#include "my_teams.h"

char *my_strcat(char *str, char *str2)
{
    char *value = NULL;
    int len = 0;
    int i = 0;

    if (str == NULL && str2 == NULL)
        return NULL;
    str ? len += strlen(str) : 0;
    str2 ? len += strlen(str2) : 0;
    value = malloc(sizeof(char) * (len + 1));
    for (i = 0; str && str[i]; ++i)
        value[i] = str[i];
    for (int j = 0; str2 && str2[j]; ++j, ++i)
        value[i] = str2[j];
    value[i] = 0;
    return value;
}

void my_const_strcat(char **str, const char *str2)
{
    size_t len = 0;
    char *tmp = NULL;
    int index = 0;

    ((*str) == NULL) ? (len = strlen(str2)) : \
(len = strlen(*str) + strlen(str2));
    tmp = alloca(sizeof(char) * (len + 1));
    memset(tmp, '\0', len + 1);
    if (*str != NULL)
        for (int a = 0; (*str)[a] != '\0'; ++a, ++index)
            tmp[index] = (*str)[a];
    for (int a = 0; str2[a] != '\0'; ++a, ++index) {
        tmp [index] = str2[a];
    }
    free(*str);
    (*str) = strdup(tmp);
}
