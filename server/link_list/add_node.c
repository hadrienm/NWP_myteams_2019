/*
** EPITECH PROJECT, 2020
** NWP_myteams_2019
** File description:
** node
*/

#include "server.h"

void add_first_node(client_t ** client, int new_socket)
{
    client_t *new_node = malloc(sizeof(client_t));

    if (new_node == NULL)
        return;
    new_node->next = NULL;
    new_node->uuid = NULL;
    new_node->readbuffer = NULL;
    new_node->name = NULL;
    new_node->description = NULL;
    new_node->answer = NULL;
    new_node->answer_size = 0;
    new_node->use_path = NULL;
    new_node->socket = new_socket;
    new_node->status = UNDEFINED;
    new_node->read_size = 0;
    new_node->readbuffer = NULL;
    (*client) = new_node;
}

void add_node_back(client_t ** client, int new_socket)
{
    client_t * new_node = NULL;

    if (*client == NULL)
        return add_first_node(client, new_socket);
    new_node = malloc(sizeof(client_t));
    client_t *base = (*client);
    for (; base && base->next != NULL; base = base->next);
    new_node->next = NULL;
    new_node->uuid = NULL;
    new_node->readbuffer = NULL;
    new_node->read_size = 0;
    new_node->readbuffer = NULL;
    new_node->name = NULL;
    new_node->description = NULL;
    new_node->answer = NULL;
    new_node->answer_size = 0;
    new_node->socket = new_socket;
    new_node->status = UNDEFINED;
    new_node->use_path = NULL;
    base->next = new_node;
}
