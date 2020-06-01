/*
** EPITECH PROJECT, 2020
** NWP_myteams_2019
** File description:
** find_channel_path
*/

#include "server.h"

channel_t *find_channel_path(team_t **team, char *path)
{
    for (team_t *t = (*team); t; t = t->next) {
        for (; t->channel && strcmp(t->channel->path, path) != 0; \
t->channel = t->channel->next);
        if (t->channel && strcmp(t->channel->path, path) == 0)
            return t->channel;
    }
    return NULL;
}

bool check_path_exist(char *str, char *path)
{
    char **list = ls_directories(path);

    for (size_t i = 0; list && list[i] != NULL; ++i) {
        if (strcmp(list[i], str) == 0) {
            free_array(list);
            return true;
        }
    }
    free_array(list);
    return false;
}

bool verify_name(char *str)
{
    if (!str)
        return false;
    for (int i = 0; str[i]; ++i)
        if (str[i] == '/')
            return false;
    return true;
}
