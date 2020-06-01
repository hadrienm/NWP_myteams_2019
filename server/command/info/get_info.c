/*
** EPITECH PROJECT, 2020
** NWP_myteams_2019
** File description:
** get_info
*/

#include "server.h"

void info_user(server_data **s, client_t **client, stoc_info_t info)
{
    sprintf(info.name, "%s", (*client)->name);
    sprintf(info.uuid, "%s", (*client)->uuid);
    send_info(client, info);
}

void info_team(server_data **s, client_t **client, stoc_info_t info)
{
    team_t *t = (*s)->team;

    for (; t; t = t->next)
        if (strcmp(t->path, (*client)->use_path) == 0)
            break;
    if (!t)
        return;
    sprintf(info.name, "%s", t->name);
    sprintf(info.description, "%s", t->description);
    sprintf(info.uuid, "%s", t->uuid);
    send_info(client, info);
}

void info_channel(server_data **s, client_t **client, stoc_info_t info)
{
    channel_t *ch = find_channel_path(&(*s)->team, (*client)->use_path);

    if (!ch)
        return;
    sprintf(info.name, "%s", ch->name);
    sprintf(info.description, "%s", ch->description);
    sprintf(info.uuid, "%s", ch->uuid);
    send_info(client, info);
}

void info_thread(server_data **s, client_t **client, stoc_info_t info)
{
    thread_t *t = find_thread_for_replies(&(*s)->team, (*client)->use_path);

    if (!t)
        return;
    sprintf(info.name, "%s", t->name);
    sprintf(info.description, "%s", t->description);
    sprintf(info.uuid, "%s", t->uuid);
    info.timestamp = t->timestamp;
    send_info(client, info);
}
