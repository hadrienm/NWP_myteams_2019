/*
** EPITECH PROJECT, 2020
** NWP_myteams_2019
** File description:
** get_command
*/

#include "client.h"

char *get_command_nwp(char *line)
{
    char *str = NULL;
    int i = 0;

    if (line == NULL)
        return NULL;

    for (; line[i] && line[i] != ' '; ++i);
    str = malloc(sizeof(char) * (i + 1));
    for (i = 0; line[i] && line[i] != ' '; ++i)
        str[i] = line[i];
    str[i] = 0;
    return str;
}

static char **get_arg_fill(char **arg, char *line)
{
    int len = 1;
    int k = 0;
    int j = 0;

    for (int i = 0; line[i]; ++i) {
        if (line[i] != '\"')
            continue;
        k = 0;
        j = 0;
        for (k = i + 1; line[k] && line[k] != '\"'; ++k);
        arg[len] = malloc(sizeof(char) * (k + 1));
        for (k = i + 1; line[k] && line[k] != '\"'; arg[len][j] = \
line[k], ++k, ++j);
        arg[len][j] = 0;
        ++len;
        i = k;
        if (!line[i])
            break;
    }
    arg[len] = NULL;
    return arg;
}

char **get_arg(char *command, char *line)
{
    char **arg = NULL;
    int len = 0;

    if (line == NULL)
        return NULL;
    for (int i = 0; line && line[i]; ++i) {
        if (line[i] != '\"')
            continue;
        int k = 0;
        for (k = i + 1; line[k] && line[k] != '\"'; ++k);
        ++len;
        i = k;
        if (!line[i])
            break;
    }
    arg = malloc(sizeof(char *) * (len + 2));
    arg[0] = strdup(command);
    return get_arg_fill(arg, line);
}

char **get_client_command(char *line)
{
    if (line == NULL) return NULL;
    int number = 0;
    char *str = delete_useless(line, " ");
    for (int i = 0; str[i]; ++i)
        if (str[i] == '"')
            ++number;
    if (number % 2 != 0) {
        free(str);
        return NULL;
    }
    char *command = get_command_nwp(str);
    if (command == NULL) {
        free(command);
        free(str);
        return NULL;
    }
    char **arg = get_arg(command, str);
    free(command);
    free(str);
    return arg;
}