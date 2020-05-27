/*
** EPITECH PROJECT, 2020
** NWP_myteams_2019
** File description:
** get_binary
*/

#include "server.h"

static void realloc_read_buffer(client_t **client, char *line, size_t size)
{
    char *save = malloc(sizeof(char) * ((*client)->read_size + size + 1));
    memset(save, 0, (*client)->read_size + size + 1);
    memcpy(save, (*client)->readbuffer, (*client)->read_size);
    memcpy(save + (*client)->read_size, line, size);
    free((*client)->readbuffer);
    (*client)->readbuffer = malloc(sizeof(char) * ((*client)->read_size + \
size + 1));
    memset((*client)->readbuffer, 0, (*client)->read_size + size + 1);
    memcpy((*client)->readbuffer, save, (*client)->read_size + size + 1);
    free(save);
}

static void save_command(size_t this_read, char *tmp_read, client_t **tmp)
{
    this_read <= 0 ? (*tmp)->status = DISCONNECT : 0;
    if ((*tmp)->read_size == 0) {
        (*tmp)->read_size = this_read;
        (*tmp)->readbuffer = malloc(sizeof(char) * (this_read + 1));
        memset((*tmp)->readbuffer, 0, this_read + 1);
        memcpy((*tmp)->readbuffer, tmp_read, this_read);
    } else
        realloc_read_buffer(&(*tmp), tmp_read, this_read);
}

void get_binary(server_data **server)
{
    char *tmp_read = malloc(sizeof(char) * (MAX_SIZE + 1));
    size_t this_read = 0;

    for (client_t *tmp = (*server)->client; tmp != NULL; tmp = tmp->next) {
        memset(tmp_read, 0, MAX_SIZE + 1);
        if (FD_ISSET(tmp->socket, &((*server)->readfds))) {
            this_read = read(tmp->socket, (char *)tmp_read, MAX_SIZE);
            save_command(this_read, tmp_read, &tmp);
        }
    }
    free(tmp_read);
}
