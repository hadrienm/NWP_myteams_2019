/*
** EPITECH PROJECT, 2020
** NWP_myteams_2019
** File description:
** set_server
*/

#include "server.h"

void handle_fd(server_data **server)
{
    client_t *tmp = (*server)->client;

    FD_ZERO(&((*server)->readfds));
    FD_ZERO(&((*server)->writefds));
    FD_SET((*server)->master_socket, &((*server)->readfds));
    FD_SET((*server)->master_socket, &((*server)->writefds));

    for (; tmp != NULL; tmp = tmp->next) {
        FD_SET(tmp->socket, &((*server)->readfds));
        if (tmp->answer != NULL)
            FD_SET(tmp->socket, &((*server)->writefds));
    }
}

static void server_send_rfc(client_t **client)
{
    size_t index = 0;
    command_status_t rfc;

    memset(&rfc, 0, sizeof(rfc));
    rfc.header.name = RFC;
    rfc.header.size = RFC_CONTENT_SIZE;
    memset(rfc.rfc_message, 0, RFC_MESSAGE_LENGTH);
    memset(rfc.id, 0, SIZE_ID);
    sprintf(rfc.rfc_message, "%s", rfc_message[CODE_201]);
    (*client)->answer = malloc(RFC_SIZE);
    memset((*client)->answer, 0, RFC_SIZE);
    (*client)->answer_size = RFC_SIZE;
    memcpy((*client)->answer + index, &rfc.header.name, sizeof(int));
    index += sizeof(int);
    memcpy((*client)->answer + index, &rfc.header.size, sizeof(size_t));
    index += sizeof(size_t);
    memcpy((*client)->answer + index, &rfc.rfc_message, RFC_MESSAGE_LENGTH);
    index += RFC_MESSAGE_LENGTH;
    memcpy((*client)->answer + index, &rfc.id, SIZE_ID);
}

static void send_rfc_server_message(server_data **server, int new_socket)
{
    for (client_t *tmp = (*server)->client; tmp != NULL; tmp = tmp->next) {
        if (tmp->socket == new_socket) {
            server_send_rfc(&tmp);
            break;
        }
    }
}

void handle_new_connection(server_data **server)
{
    int new_socket = 0;
    size_t len = sizeof((*server)->address);

    if (FD_ISSET((*server)->master_socket, &(*server)->readfds)) {
        if ((new_socket = accept((*server)->master_socket, \
(struct sockaddr *)&(*server)->address, (socklen_t *)&len)) < 0) {
            printf("accept failed\n");
            return;
        }
        add_node_back(&((*server)->client), new_socket);
        send_rfc_server_message(server, new_socket);
    }
}