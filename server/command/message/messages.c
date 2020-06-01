/*
** EPITECH PROJECT, 2020
** NWP_myteams_2019
** File description:
** messages
*/

#include "server.h"

void messages(client_t *client, server_data **server)
{
    ctos_messages_t messages;

    memset(&messages, 0, sizeof(messages));
    memcpy(&messages, client->readbuffer, sizeof(ctos_messages_t));
    if (client->uuid == NULL) {
        send_message_rfc(500, &client, messages.id);
    } else if (strlen(messages.id) == 0) {
        send_message_rfc(401, &client, messages.id);
    } else {
        messages_success(&client, messages.id, (*server)->crp_list);
    }
}
