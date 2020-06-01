/*
** EPITECH PROJECT, 2020
** NWP_myteams_2019
** File description:
** create_thread
*/

#include "server.h"

static void add_thread_three(client_t **client, stoc_create_t c, \
server_data **s, char *path2)
{
    void *buffer = NULL;
    char *path = cut_path((*client)->use_path);
    char **list = NULL;
    team_t *t = find_team(&(*s)->team, path);
    thread_t *th = find_thread_for_replies(&t, path2);

    send_create(client, 0, c);
    buffer = create_set_broadcast_buffer(c);
    list = create_broadcast_subscribe_list(t, (*client)->uuid);
    create_subscribe_broadcast(buffer, &(*s)->client, list);
    free(buffer);
    buffer = create_set_buffer_thread_message(t, th);
    create_subscribe_broadcast(buffer, &(*s)->client, list);
    free_array(list);
    free(path);
    free(buffer);
}

static void add_thread_simple_back(stoc_create_t c, channel_t **ch, \
server_data **s, client_t **client)
{
    thread_t *new_node = malloc(sizeof(thread_t));
    thread_t *base = (*ch)->thread;

    for (; base && base->next != NULL; base = base->next);
    memset(new_node->description, 0, DEFAULT_BODY_LENGTH);
    memset(new_node->uuid, 0, SIZE_ID);
    memset(new_node->name, 0, DEFAULT_NAME_LENGTH);
    memset(new_node->sender, 0, SIZE_ID);
    memcpy(new_node->description, c.description, strlen(c.description));
    memcpy(new_node->name, c.name, strlen(c.name));
    new_node->next = NULL;
    new_node->timestamp = c.timestamp;
    new_node->path = my_strcat((*client)->use_path, "/");
    my_const_strcat(&new_node->path, c.name);
    memcpy(new_node->uuid, c.team_uuid, strlen(c.team_uuid));
    memcpy(new_node->sender, (*client)->uuid, strlen((*client)->uuid));
    init_reply(&new_node);
    base->next = new_node;
}

static void memset_new_node(thread_t **new_node, stoc_create_t c)
{
    memset((*new_node)->description, 0, DEFAULT_BODY_LENGTH);
    memset((*new_node)->uuid, 0, SIZE_ID);
    memset((*new_node)->name, 0, DEFAULT_NAME_LENGTH);
    memset((*new_node)->sender, 0, SIZE_ID);
    memcpy((*new_node)->description, c.description, strlen(c.description));
    memcpy((*new_node)->name, c.name, strlen(c.name));
}

static void add_thread_simple(stoc_create_t c, team_t **team, \
server_data **s, client_t **client)
{
    channel_t *ch = find_channel_path(&(*s)->team, (*client)->use_path);
    thread_t *new_node = NULL;

    if (ch == NULL)
        return;
    if ((ch)->thread == NULL) {
        new_node = malloc(sizeof(thread_t));
        memset_new_node(&new_node, c);
        new_node->next = NULL;
        new_node->timestamp = c.timestamp;
        new_node->path = my_strcat((*client)->use_path, "/");
        my_const_strcat(&new_node->path, c.name);
        memcpy(new_node->uuid, c.team_uuid, strlen(c.team_uuid));
        memcpy(new_node->sender, (*client)->uuid, strlen((*client)->uuid));
        init_reply(&new_node);
        (ch)->thread = new_node;
    } else
        add_thread_simple_back(c, &ch, s, client);
    server_event_thread_created((ch)->uuid, c.team_uuid, (*client)->uuid, \
c.description);
}

int add_thread(client_t ** client, ctos_create_t create, server_data **s, \
char *uuid)
{
    stoc_create_t c = memset_all(create, THREAD, client);
    char *path2 = NULL;
    char *str = NULL;

    if (strlen(create.name) == 0 || strlen(create.message) == 0)
        return 0;
    sprintf(create.uuid, "%s", uuid);
    sprintf(c.team_uuid, "%s", uuid);
    if (!verify_name(create.name))
        return 0;
    path2 = my_strcat("/", create.name);
    str = my_strcat((*client)->use_path, path2);
    if (check_path_exist(str, (*client)->use_path) == true)
        return 2;
    add_thread_simple(c, &(*s)->team, s, client);
    add_thread_three(client, c, s, str);
    free(str);
    free(path2);
    return 1;
}
