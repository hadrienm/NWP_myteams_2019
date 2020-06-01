/*
** EPITECH PROJECT, 2020
** NWP_myteams_2019
** File description:
** utils
*/

#include "server.h"

team_t *find_team(team_t **t, char *path)
{
    team_t *base = (*t);

    for (; base; base = base->next)
        if (strcmp(path, base->path) == 0)
            return base;
    return NULL;
}