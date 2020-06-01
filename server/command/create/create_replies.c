/*
** EPITECH PROJECT, 2020
** NWP_myteams_2019
** File description:
** create_replies
*/

#include "server.h"

thread_t *find_thread_for_replies(team_t **t, char *path)
{
    thread_t *th = NULL;

    for (channel_t *ch = (*t)->channel; ch; ch = ch->next) {
        for (th = ch->thread; th && strcmp(th->path, path) != 0; \
th = th->next);
        if (th && strcmp(th->path, path) == 0)
            return th;
    }
    return NULL;
}

static void add_replies_simple(stoc_create_t c, thread_t **t, \
server_data **s, client_t **client)
{
    replies_t *base = (*t)->reply;
    replies_t *new_node = malloc(sizeof(replies_t));

    if ((*t)->reply == NULL) {
        memset(new_node->user_uuid, 0, SIZE_ID);
        memset(new_node->body, 0, DEFAULT_BODY_LENGTH);
        new_node->timestamp = c.timestamp;
        memcpy(new_node->user_uuid, (*client)->uuid, strlen((*client)->uuid));
        new_node->next = NULL;
        memcpy(new_node->body, c.description, strlen(c.description));
        (*t)->reply = new_node;
    } else {
        for (; base && base->next != NULL; base = base->next);
        memset(new_node->user_uuid, 0, SIZE_ID);
        memset(new_node->body, 0, DEFAULT_BODY_LENGTH);
        new_node->timestamp = c.timestamp;
        memcpy(new_node->user_uuid, (*client)->uuid, strlen((*client)->uuid));
        new_node->next = NULL;
        memcpy(new_node->body, c.description, strlen(c.description));
        base->next = new_node;
    }
}

static void replies_broadcast(client_t **client, stoc_create_t c, \
server_data **s)
{
    void *buffer = NULL;
    char *path = cut_path((*client)->use_path);
    char *path_team = cut_path(path);
    team_t *t = find_team(&(*s)->team, path_team);

    send_create(client, 0, c);
    buffer = create_set_broadcast_buffer(c);
    create_subscribe_broadcast(buffer, &(*s)->client, \
create_broadcast_subscribe_list(t, (*client)->uuid));
    free(path_team);
    free(path);
    free(buffer);
}

int add_message(client_t ** client, ctos_create_t create, server_data **s, \
char *uuid)
{
    stoc_create_t c = memset_all(create, REPLIES, client);
    char *str = NULL;
    team_t *t = find_team_for_replies(s, (*client)->use_path);
    thread_t *th = NULL;

    if (strlen(create.message) == 0)
        return 0;
    if (!t)
        return 1;
    th = find_thread_for_replies(&t, (*client)->use_path);
    if (!th)
        return 1;
    sprintf(c.team_uuid, "%s", t->uuid);
    sprintf(c.thread_uuid, "%s", th->uuid);
    add_replies_simple(c, &th, s, client);
    server_event_thread_new_message(t->uuid, (*client)->uuid, create.message);
    replies_broadcast(client, c, s);
    return 1;
}
