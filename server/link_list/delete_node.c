/*
** EPITECH PROJECT, 2020
** NWP_myteams_2019
** File description:
** delete_node
*/

#include "server.h"

static void delete_first_node(client_t **client)
{
    client_t *new_list = (*client);

    new_list = (*client)->next;
    (*client)->uuid != NULL ? free((*client)->uuid) : 0;
    (*client)->readbuffer != NULL ? free((*client)->readbuffer) : 0;
    (*client)->name != NULL ? free((*client)->name) : 0;
    (*client)->description != NULL ? free((*client)->description) : 0;
    free((*client));
    (*client) = new_list;
}

static void delete_node(client_t *node, client_t **client)
{
    client_t *new_list = (*client);
    client_t *tmp;

    if (new_list == NULL)
        return;
    if (new_list == node) {
        delete_first_node(client);
        return;
    }
    for (; new_list->next != NULL; new_list = new_list->next)
        if (new_list->next == node)
            break;
    new_list->next->uuid != NULL ? free(new_list->next->uuid) : 0;
    new_list->next->readbuffer != NULL ? free(new_list->next->readbuffer) : 0;
    new_list->next->name != NULL ? free(new_list->next->name) : 0;
    new_list->next->description != NULL ? \
free(new_list->next->description) : 0;
    tmp = new_list->next->next;
    new_list->next = tmp;
}

void free_useless(client_t **client, bool all)
{
    client_t * current = (*client);
    client_t * next;

    while (current != NULL) {
        next = current->next;
        if (all == false && current->status == DISCONNECT && \
current->answer == NULL) {
            close(current->socket);
            delete_node(current, client);
        } else if (all == true) {
            close(current->socket);
            delete_node(current, client);
        }
        current = next;
    }
}