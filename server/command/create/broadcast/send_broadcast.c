/*
** EPITECH PROJECT, 2020
** NWP_myteams_2019
** File description:
** send_broadcast
*/

#include "server.h"

static void realloc_client_answer(client_t **tmp, void *buffer)
{
    void *save = NULL;
    size_t size = CREATE_SIZE;

    save = malloc((*tmp)->answer_size + size);
    memset(save, 0, (*tmp)->answer_size + size);
    memcpy(save, (*tmp)->answer, (*tmp)->answer_size);
    memcpy(save + (*tmp)->answer_size, buffer, size);
    free((*tmp)->answer);
    (*tmp)->answer = malloc(size + (*tmp)->answer_size);
    memset((*tmp)->answer, 0, size + (*tmp)->answer_size);
    memcpy((*tmp)->answer, save, size + (*tmp)->answer_size);
    (*tmp)->answer_size += size;
}

static void create_subscribe_broadcast_two(client_t *tmp, void *buffer, \
char **array, int i)
{
    size_t size = CREATE_SIZE;

    if (tmp->answer == NULL && tmp->status == CONNECT && \
my_strcmp(array[i], tmp->uuid) == 0) {
        tmp->answer = malloc(size);
        memcpy(tmp->answer, buffer, size);
        tmp->answer_size = size;
    } else if (tmp->answer != NULL && tmp->status == CONNECT && \
my_strcmp(array[i], tmp->uuid) == 0)
        realloc_client_answer(&tmp, buffer);
}

void create_subscribe_broadcast(void *buffer, client_t **all, \
char **client_team_list)
{
    size_t size = CREATE_SIZE;

    if (client_team_list == NULL)
        return;
    for (client_t *tmp = *all; tmp != NULL; tmp = tmp->next) {
        for (int i = 0; client_team_list[i]; ++i)
            create_subscribe_broadcast_two(tmp, buffer, client_team_list, i);
    }
}

void create_broadcast(client_t **client, client_t **all, void *buffer)
{
    void * save = NULL;

    for (client_t *tmp = *all; tmp != NULL; tmp = tmp->next) {
        if (tmp->answer == NULL && tmp->status == CONNECT && \
(*client) != tmp) {
            tmp->answer = malloc(CREATE_SIZE);
            memcpy(tmp->answer, buffer, CREATE_SIZE);
            tmp->answer_size = CREATE_SIZE;
        } else if (tmp->answer != NULL && tmp->status == CONNECT && \
(*client) != tmp) {
            save = malloc(tmp->answer_size + CREATE_SIZE);
            memcpy(save, tmp->answer, tmp->answer_size);
            memcpy(save + tmp->answer_size, buffer, CREATE_SIZE);
            free(tmp->answer);
            tmp->answer = malloc(CREATE_SIZE + tmp->answer_size);
            memcpy(tmp->answer, save, CREATE_SIZE + tmp->answer_size);
            tmp->answer_size += CREATE_SIZE;
        }
    }
    free(buffer);
}

void *create_set_buffer_thread_message(team_t *t, thread_t *th)
{
    stoc_create_t c;
    size_t index = 0;

    memset(&c, 0, sizeof(stoc_create_t));
    memset(c.user_uuid, 0, SIZE_ID);
    memset(c.team_uuid, 0, SIZE_ID);
    memset(c.thread_uuid, 0, SIZE_ID);
    memset(c.description, 0, DEFAULT_BODY_LENGTH);
    c.header.name = CREATE;
    c.header.size = CREATE_CONTENT_SIZE;
    c.local = REPLIES;
    sprintf(c.team_uuid, "%s", t->uuid);
    sprintf(c.thread_uuid, "%s", th->uuid);
    c.timestamp = th->timestamp;
    sprintf(c.description, "%s", th->description);
    sprintf(c.user_uuid, "%s", th->sender);
    return create_set_broadcast_buffer(c);
}
