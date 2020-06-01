/*
** EPITECH PROJECT, 2020
** NWP_myteams_2019
** File description:
** delete
*/

#include "server.h"

static void delete_client(client_list_t **client_list)
{
    client_list_t *current = (*client_list);
    client_list_t *next;

    while (current != NULL) {
        next = current->next;
        free(current);
        current = next;
    }
}

static void delete_message(cpr_message_list_t **msg_list)
{
    cpr_message_list_t *current = (*msg_list);
    cpr_message_list_t *next;

    while (current != NULL) {
        next = current->next;
        free(current);
        current = next;
    }
}

static void delete_corresponding(corresponding_t **cpr_list)
{
    corresponding_t *current = (*cpr_list);
    corresponding_t *next;

    while (current != NULL) {
        next = current->next;
        delete_message(&current->msg_list);
        free(current);
        current = next;
    }
}

void free_server_data(server_data **server)
{
    delete_client(&(*server)->client_list);
    delete_corresponding(&(*server)->crp_list);
    free(*server);
}
