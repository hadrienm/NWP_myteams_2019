/*
** EPITECH PROJECT, 2020
** Visual Studio Live Share (Workspace)
** File description:
** broadcast_logout
*/

#include "server.h"

static void send_logout_broadcast(void *buffer, size_t size, int socket, \
client_t **all)
{
    void * save = NULL;

    for (client_t *tmp = *all; tmp != NULL; tmp = tmp->next) {
        if (tmp->answer == NULL && tmp->status == CONNECT && \
socket != tmp->socket) {
            tmp->answer = malloc(size);
            memcpy(tmp->answer, buffer, size);
            tmp->answer_size = size;
        } else if (tmp->answer != NULL && tmp->status == CONNECT && \
socket != tmp->socket) {
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

void set_logout_broadcast(stoc_logout_t logout, client_t **all, int socket)
{
    size_t size = LOGOUT_SIZE;
    size_t index = 0;
    void *buffer;

    buffer = malloc(size);
    memset(buffer, 0, size);
    memcpy(buffer, &logout.header.name, sizeof(int));
    index += sizeof(int);
    memcpy(buffer + index, &logout.header.size, sizeof(size_t));
    index += sizeof(size_t);
    memcpy(buffer + index, &logout.user_id, SIZE_ID);
    index += SIZE_ID;
    memcpy(buffer + index, &logout.name, DEFAULT_NAME_LENGTH);
    index += DEFAULT_NAME_LENGTH;
    send_logout_broadcast(buffer, size, socket, all);
    free(buffer);
}
