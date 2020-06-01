/*
** EPITECH PROJECT, 2020
** NWP_myteams_2019
** File description:
** send_unsubscribe_broadcast
*/

#include "server.h"

static void realloc_client_answer(client_t **tmp, void *buffer)
{
    char *save = NULL;
    size_t size = sizeof(int) * 2 + sizeof(size_t) + \
RFC_MESSAGE_LENGTH + SIZE_ID * 2;

    save = malloc((*tmp)->answer_size + size);
    memcpy(save, (*tmp)->answer, (*tmp)->answer_size);
    memcpy(save + (*tmp)->answer_size, buffer, size);
    free((*tmp)->answer);
    (*tmp)->answer = malloc(size + (*tmp)->answer_size);
    memcpy((*tmp)->answer, save, size + (*tmp)->answer_size);
    (*tmp)->answer_size += size;
}

static void check_client_unsusbcribe_broadcast(char **client_team_list, \
void *buffer, client_t **tmp, int i)
{
    size_t size = UNSUBSCRIBE_SIZE;

    if ((*tmp)->answer == NULL && (*tmp)->status == CONNECT && \
strncmp(client_team_list[i], (*tmp)->uuid, SIZE_ID - 1) == 0) {
        (*tmp)->answer = malloc(size);
        memcpy((*tmp)->answer, buffer, size);
        (*tmp)->answer_size = size;
    } else if ((*tmp)->answer != NULL && (*tmp)->status == CONNECT && \
strncmp(client_team_list[i], (*tmp)->uuid, SIZE_ID - 1) == 0) {
        realloc_client_answer(tmp, buffer);
    }
}

void send_unsubscribe_brodcast(void *buffer, char team_list[SIZE_ID], \
client_t **all, char **client_team_list)
{
    for (client_t *tmp = *all; tmp != NULL; tmp = tmp->next)
        for (int i = 0; client_team_list[i]; ++i)
            check_client_unsusbcribe_broadcast(client_team_list, \
buffer, &tmp, i);
}