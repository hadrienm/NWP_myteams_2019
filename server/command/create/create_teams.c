/*
** EPITECH PROJECT, 2020
** NWP_myteams_2019
** File description:
** create_teams
*/

#include "server.h"

int add_teams(client_t ** client, ctos_create_t create, client_t **all, \
char *new_uuid)
{
    stoc_create_t c = memset_all(create, TEAM, client);
    char temp[10];
    char *str = NULL;
    bool check = false;

    sprintf(c.team_uuid, "%s", new_uuid);
    sprintf(create.uuid, "%s", new_uuid);
    if (!verify_name(create.name))
        return 0;
    str = my_strcat("./save/", create.name);
    check = mkdir(str, 0777);
    if (errno == EEXIST) return 2;
    sprintf(temp, "%d", (int)time(NULL));
    if (check || write_create_in_file(str, create, temp) == 0)
        return 0;
    free(str);
    server_event_team_created(create.uuid, create.name, (*client)->uuid);
    send_create(client, 0, c);
    create_broadcast(client, all, create_set_broadcast_buffer(c));
    return 1;
}
