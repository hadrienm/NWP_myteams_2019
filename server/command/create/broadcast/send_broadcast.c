/*
** EPITECH PROJECT, 2020
** NWP_myteams_2019
** File description:
** send_broadcast
*/

#include "server.h"

static void realloc_client_answer(client_t **tmp, void *buffer)
{
    char *save = NULL;
    size_t size = subscribe_size;

    save = malloc((*tmp)->answer_size + size);
    memcpy(save, (*tmp)->answer, (*tmp)->answer_size);
    memcpy(save + (*tmp)->answer_size, buffer, size);
    free((*tmp)->answer);
    (*tmp)->answer = malloc(size + (*tmp)->answer_size);
    memcpy((*tmp)->answer, save, size + (*tmp)->answer_size);
    (*tmp)->answer_size += size;
}

static void create_subscribe_broadcast_two(client_t *tmp, void *buffer, \
char **array, int i)
{
    size_t size = create_size;

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
    size_t size = create_size;

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
            tmp->answer = malloc(create_size);
            memcpy(tmp->answer, buffer, create_size);
            tmp->answer_size = create_size;
        } else if (tmp->answer != NULL && tmp->status == CONNECT && \
(*client) != tmp) {
            save = malloc(tmp->answer_size + create_size);
            memcpy(save, tmp->answer, tmp->answer_size);
            memcpy(save + tmp->answer_size, buffer, create_size);
            free(tmp->answer);
            tmp->answer = malloc(create_size + tmp->answer_size);
            memcpy(tmp->answer, save, create_size + tmp->answer_size);
            tmp->answer_size += create_size;
        }
    }
    free(buffer);
}
