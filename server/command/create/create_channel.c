/*
** EPITECH PROJECT, 2020
** NWP_myteams_2019
** File description:
** create_channel
*/

#include "server.h"

static void add_channel_two(client_t **client, stoc_create_t c, \
server_data **s)
{
    void *buffer = NULL;
    team_t *t = NULL;

    for (t = (*s)->team; t; t = t->next)
        if (strcmp(t->path, (*client)->use_path) == 0)
            break;
    server_event_channel_created(t->uuid, c.team_uuid, c.name);
    send_create(client, 0, c);
    buffer = create_set_broadcast_buffer(c);
    create_subscribe_broadcast(buffer, &(*s)->client, \
create_broadcast_subscribe_list(t, (*client)->uuid));
    free(buffer);
}

static void add_channel_simple_back(stoc_create_t c, team_t **team, \
client_t **client)
{
    channel_t *new_node = malloc(sizeof(team_t));
    channel_t *base = (*team)->channel;

    for (; base && base->next != NULL; base = base->next);
    memset(new_node->name, 0, DEFAULT_NAME_LENGTH);
    memcpy(new_node->name, c.name, strlen(c.name));
    new_node->path = my_strcat((*client)->use_path, "/");
    my_const_strcat(&new_node->path, c.name);
    new_node->next = NULL;
    memset(new_node->description, 0, DEFAULT_DESCRIPTION_LENGTH);
    memcpy(new_node->description, c.description, strlen(c.description));
    memset(new_node->uuid, 0, SIZE_ID);
    memcpy(new_node->uuid, c.team_uuid, strlen(c.team_uuid));
    new_node->timestamp = c.timestamp;
    new_node->thread = NULL;
    base->next = new_node;
}

static void memset_new_node_channel(channel_t **new_node, stoc_create_t c)
{
    memset((*new_node)->uuid, 0, SIZE_ID);
    memset((*new_node)->name, 0, DEFAULT_NAME_LENGTH);
    memset((*new_node)->description, 0, DEFAULT_DESCRIPTION_LENGTH);
    memcpy((*new_node)->uuid, c.team_uuid, strlen(c.team_uuid));
    memcpy((*new_node)->name, c.name, strlen(c.name));
    memcpy((*new_node)->description, c.description, strlen(c.description));
}

static void add_channel_simple(stoc_create_t c, server_data **s, \
client_t **client)
{
    char *path2 = cut_path((*client)->use_path);
    team_t *team = find_team(&(*s)->team, (*client)->use_path);
    channel_t *new_node = NULL;

    if (team == NULL)
        return;
    if ((team)->channel == NULL) {
        new_node = malloc(sizeof(channel_t));
        memset_new_node_channel(&new_node, c);
        new_node->thread = NULL;
        new_node->timestamp = c.timestamp;
        new_node->path = my_strcat((*client)->use_path, "/");
        my_const_strcat(&new_node->path, c.name);
        new_node->next = NULL;
        (team)->channel = new_node;
    } else
        add_channel_simple_back(c, &team, client);
    free(path2);
}

int add_channel(client_t ** client, ctos_create_t create, server_data **s, \
char *new_uuid)
{
    stoc_create_t c = memset_all(create, CHANNEL, client);
    team_t *t;
    char *path = NULL;
    char *str = NULL;

    if (strlen(create.name) == 0 || strlen(create.message) == 0)
        return 0;
    sprintf(c.team_uuid, "%s", new_uuid);
    sprintf(create.uuid, "%s", new_uuid);
    if (!verify_name(create.name))
        return 0;
    path = my_strcat("/", create.name);
    str = my_strcat((*client)->use_path, path);
    if (check_path_exist(str, (*client)->use_path) == true)
        return 2;
    free(str);
    free(path);
    add_channel_simple(c, s, client);
    add_channel_two(client, c, s);
    return 1;
}
