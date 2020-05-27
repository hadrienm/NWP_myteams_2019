/*
** EPITECH PROJECT, 2020
** NWP_myteams_2019
** File description:
** broadcast_subscribe
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

static void set_subscribe_broadcast(char **client_team_list, int i, \
void *buffer, client_t **tmp)
{
    size_t size = subscribe_size;

    if ((*tmp)->answer == NULL && (*tmp)->status == CONNECT && \
my_strcmp(client_team_list[i], (*tmp)->uuid) == 0) {
        (*tmp)->answer = malloc(size);
        memcpy((*tmp)->answer, buffer, size);
        (*tmp)->answer_size = size;
    } else if ((*tmp)->answer != NULL && (*tmp)->status == CONNECT && \
my_strcmp(client_team_list[i], (*tmp)->uuid) == 0) {
        realloc_client_answer(&(*tmp), buffer);
    }
}

static void send_subscribe_brodcast(void *buffer, char team_list[SIZE_ID], \
client_t **all, char **client_team_list)
{
    for (client_t *tmp = *all; tmp != NULL; tmp = tmp->next)
        for (int i = 0; client_team_list[i]; ++i)
            set_subscribe_broadcast(client_team_list, i, buffer, &tmp);
}

static void *create_subscribe_broadcast_buffer(stoc_subscribe_t sub)
{
    void *buffer = NULL;
    size_t index = 0;
    size_t size = subscribe_size;

    buffer = malloc(size);
    memset(buffer, 0, size);
    memcpy(buffer, &sub.header.name, sizeof(int));
    index += sizeof(int);
    memcpy(buffer + index, &sub.header.size, sizeof(size_t));
    index += sizeof(size_t);
    memcpy(buffer + index, &sub.team_id, SIZE_ID);
    index += SIZE_ID;
    memcpy(buffer + index, &sub.user_id, SIZE_ID);
    return buffer;
}

void subscribe_broadcast(stoc_subscribe_t sub, char team_id[SIZE_ID], \
client_t **all)
{
    char **list = NULL;
    char *path = found_path_team(team_id);
    void *buffer = create_subscribe_broadcast_buffer(sub);

    list = create_broadcast_list(path);
    if (list != NULL)
        send_subscribe_brodcast(buffer, team_id, all, list);
    path != NULL ? free(path) : 0;
    free(buffer);
    free_array(list);
}