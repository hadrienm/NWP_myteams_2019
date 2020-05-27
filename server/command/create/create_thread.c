/*
** EPITECH PROJECT, 2020
** NWP_myteams_2019
** File description:
** create_thread
*/

#include "server.h"

static void add_thread_three(client_t **client, stoc_create_t c, client_t **all)
{
    send_create(client, 0, c);
    create_subscribe_broadcast(create_set_broadcast_buffer(c), all, \
create_broadcast_subscribe_list(my_strcat(get_uuid_team((*client)->use_path), \
"/default.txt"), (*client)->uuid));
}

static void add_thread_two(client_t **client, char *uuid, ctos_create_t create)
{
    char *str = get_uuid_parent_folder((*client)->use_path);

    server_event_thread_created(str, uuid, (*client)->uuid, create.message);
    free(str);
}

int add_thread(client_t ** client, ctos_create_t create, client_t **all, \
char *uuid)
{
    stoc_create_t c = memset_all(create, THREAD, client);
    char *path2 = NULL;
    char *str = NULL;
    bool check = false;
    char temp[10];

    sprintf(create.uuid, "%s", uuid);
    sprintf(c.team_uuid, "%s", uuid);
    if (!verify_name(create.name)) return 0;
    path2 = my_strcat("/", create.name);
    str = my_strcat((*client)->use_path, path2);
    check = mkdir(str, 0777);
    if (errno == EEXIST)
        return 2;
    sprintf(temp, "%d", (int)time(NULL));
    if (check || write_timestamp(str, temp, create, client) == 0) return 0;
    free(str);
    free(path2);
    add_thread_two(client, uuid, create);
    add_thread_three(client, c, all);
    return 1;
}