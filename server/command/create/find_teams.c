/*
** EPITECH PROJECT, 2020
** NWP_myteams_2019
** File description:
** find_teams
*/

#include "server.h"

static team_t *find_team_for_replies_three(channel_t *ch, char *path, \
team_t *t)
{
    for (thread_t *th = ch->thread; th; th = th->next)
        if (strcmp(th->path, path) == 0)
            return t;
    return NULL;
}

static team_t *find_team_for_replies_two(channel_t *ch, char *path, team_t *t)
{
    team_t *team = NULL;

    for (channel_t *ch = t->channel; ch; ch = ch->next) {
        team = find_team_for_replies_three(ch, path, t);
        if (team != NULL)
            return team;
    }
    return NULL;
}

team_t *find_team_for_replies(server_data **s, char *path)
{
    team_t *team = NULL;

    for (team_t *t = (*s)->team; t; t = t->next) {
        team = find_team_for_replies_two(t->channel, path, t);
        if (team != NULL)
            return team;
    }
    return NULL;
}
