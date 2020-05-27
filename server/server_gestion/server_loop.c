/*
** EPITECH PROJECT, 2020
** NWP_myteams_2019
** File description:
** server_loop
*/

#include "server.h"

static void delete_useless_part_of_command(ctos_header_t header, \
server_data **server, client_t **tmp, char *save)
{
    if ((*tmp)->read_size >= sizeof(ctos_header_t) + header.size) {
        command[header.name]((*tmp), &(*server)->client);
        if ((*tmp)->read_size - sizeof(ctos_header_t) - header.size > 0) {
            save = malloc(sizeof(char) * ((*tmp)->read_size - \
sizeof(ctos_header_t) - header.size + 1));
            memset(save, 0, (*tmp)->read_size - sizeof(ctos_header_t) \
- header.size + 1);
            (*tmp)->read_size -= sizeof(ctos_header_t) + header.size;
            memcpy(save, (*tmp)->readbuffer + sizeof(ctos_header_t) + \
header.size, (*tmp)->read_size);
            free((*tmp)->readbuffer);
            (*tmp)->readbuffer = malloc(sizeof(char) * (*tmp)->read_size + 1);
            memset((*tmp)->readbuffer, 0, (*tmp)->read_size + 1);
            memcpy((*tmp)->readbuffer, save, (*tmp)->read_size);
            free(save);
        } else {
            (*tmp)->read_size = 0;
            free((*tmp)->readbuffer);
            (*tmp)->readbuffer = NULL;
        }
    }
}

static void launch_command(server_data **server)
{
    ctos_header_t header;
    char *save = NULL;

    for (client_t *tmp = (*server)->client; tmp != NULL; tmp = tmp->next) {
        if (tmp->read_size >= sizeof(ctos_header_t)) {
            memset(&header, 0, sizeof(ctos_header_t));
            memcpy(&header, tmp->readbuffer, sizeof(ctos_header_t));
            delete_useless_part_of_command(header, server, &tmp, save);
        }
    }
}

static int handle_select(server_data **server)
{
    int max = (*server)->master_socket;

    for (client_t *tmp = (*server)->client; tmp != NULL; tmp = tmp->next)
        tmp->socket > max ? max = tmp->socket : 0;
    if (select(max + 1, &(*server)->readfds, \
&(*server)->writefds, NULL, NULL) < 0) {
        printf("ERROR in select\n");
        return 84;
    }
    return EXIT_SUCCESS;
}

static void write_all(server_data **server)
{
    for (client_t *tmp = (*server)->client; tmp != NULL; tmp = tmp->next) {
        if (FD_ISSET(tmp->socket, &((*server)->writefds)) && \
tmp->answer != NULL) {
            write(tmp->socket, tmp->answer, tmp->answer_size);
            free(tmp->answer);
            tmp->answer = NULL;
            tmp->answer_size = 0;
        }
    }
}

void server_loop(server_data *server)
{
    free_useless(&server->client, false);
    handle_fd(&server);
    if (handle_select(&server) != 84) {
        write_all(&server);
        handle_new_connection(&server);
        get_binary(&server);
        launch_command(&server);
    }
}
