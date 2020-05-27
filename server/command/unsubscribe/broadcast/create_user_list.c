/*
** EPITECH PROJECT, 2020
** NWP_myteams_2019
** File description:
** create_user_list
*/

#include "server.h"

static char **push_array(char **list, char *str)
{
    char **tmp = NULL;
    size_t size = 1;
    size_t index = 0;

    for (; list && list[size] != NULL; ++size);
    tmp = malloc(sizeof(char *) * (size + 2));
    for (; list && list[index] != NULL; ++index)
        tmp[index] = strdup(list[index]);
    tmp[index] = strdup(str);
    tmp[index + 1] = NULL;
    free_array(list);
    return tmp;
}

static char **handle_list(char *line, char **list)
{
    char *tmp = malloc(sizeof(char) * SIZE_ID);
    memset(tmp, 0, SIZE_ID);

    for (int j = 0; j < SIZE_ID - 1; ++j)
        tmp[j] = line[j];
    return push_array(list, tmp);
}

char **create_broadcast_list(char *path)
{
    char **list = NULL;
    char *line = NULL;
    FILE * file;
    size_t useless = 0;
    size_t index = 0;

    if (path == NULL)
        return NULL;
    file = fopen(path, "r");
    if (file == NULL)
        return NULL;
    for (; getline(&line, &useless, file) != -1; ++index)
        if (index > 0)
            list = handle_list(line, list);
    fclose(file);
    return list;
}
