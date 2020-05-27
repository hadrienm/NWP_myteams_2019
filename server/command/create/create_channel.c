/*
** EPITECH PROJECT, 2020
** NWP_myteams_2019
** File description:
** create_channel
*/

#include "server.h"

static void add_channel_two(client_t **client, stoc_create_t c, \
char *new_uuid, client_t **all)
{
    char *str = NULL;

    str = get_uuid_parent_folder((*client)->use_path);
    send_create(client, 0, c);
    create_subscribe_broadcast(create_set_broadcast_buffer(c), all, \
create_broadcast_subscribe_list(my_strcat(get_uuid_team((*client)->\
use_path), "/default.txt"), (*client)->uuid));
    free(str);
}

int add_channel(client_t ** client, ctos_create_t create, client_t **all, \
char *new_uuid)
{
    stoc_create_t c = memset_all(create, CHANNEL, client);
    char *path = NULL;
    char *str = NULL;
    bool check = false;
    char temp[10];

    sprintf(c.team_uuid, "%s", new_uuid);
    sprintf(create.uuid, "%s", new_uuid);
    if (!verify_name(create.name)) return 0;
    path = my_strcat("/", create.name);
    str = my_strcat((*client)->use_path, path);
    check = mkdir(str, 0777);
    if (errno == EEXIST) return 2;
    sprintf(temp, "%d", (int)time(NULL));
    if (check || write_create_in_file(str, create, temp) == 0) return 0;
    free(str);
    free(path);
    server_event_channel_created(str, new_uuid, create.name);
    add_channel_two(client, c, new_uuid, all);
    return 1;
}
