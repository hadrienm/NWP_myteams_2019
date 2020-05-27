/*
** EPITECH PROJECT, 2020
** NWP_myteams_2019
** File description:
** login_broadcast
*/

#include "server.h"

static void send_login_brodcast(void *buffer, size_t size, int socket, \
client_t **all)
{
    void * save = NULL;

    for (client_t *tmp = *all; tmp != NULL; tmp = tmp->next) {
        if (tmp->answer == NULL && tmp->status == CONNECT && \
tmp->socket != socket) {
            tmp->answer = malloc(size);
            memcpy(tmp->answer, buffer, size);
            tmp->answer_size = size;
        } else if (tmp->answer != NULL && tmp->status == CONNECT && \
tmp->socket != socket) {
            save = malloc(tmp->answer_size + size);
            memcpy(save, tmp->answer, tmp->answer_size);
            memcpy(save + tmp->answer_size, buffer, size);
            free(tmp->answer);
            tmp->answer = malloc(size + tmp->answer_size);
            memcpy(tmp->answer, save, size + tmp->answer_size);
            tmp->answer_size += size;
        }
    }
}

void set_login_brodcast(stoc_login_t login, client_t **all, int socket)
{
    size_t size = login_size;
    size_t index = 0;
    void *buffer = NULL;

    buffer = malloc(size);
    memset(buffer, 0, size);
    memcpy(buffer + index, &login.header.name, sizeof(int));
    index += sizeof(int);
    memcpy(buffer + index, &login.header.size, sizeof(size_t));
    index += sizeof(size_t);
    memcpy(buffer + index, &login.user_id, SIZE_ID);
    index += SIZE_ID;
    memcpy(buffer + index, &login.name, DEFAULT_NAME_LENGTH);
    send_login_brodcast(buffer, size, socket, all);
    free(buffer);
}
