/*
** EPITECH PROJECT, 2020
** NWP_myteams_2019
** File description:
** messages
*/

#include "client.h"

void messages_decrypt(client_data **client)
{
    char id[SIZE_ID];
    char message[DEFAULT_BODY_LENGTH];
    int timestamp;
    size_t index = HEADER_SIZE;

    memcpy(&id, (*client)->read_buffer + index, SIZE_ID);
    index += SIZE_ID;
    memcpy(&message, (*client)->read_buffer + index, DEFAULT_BODY_LENGTH);
    index += DEFAULT_BODY_LENGTH;
    memcpy(&timestamp, (*client)->read_buffer + index, sizeof(int));
    client_private_message_print_messages(id, (time_t)timestamp, message);
}

void messages(client_data **client)
{
    ctos_messages_t messages;

    memset(&messages, 0, sizeof(messages));
    memset(messages.id, 0, SIZE_ID);
    messages.header.name = MESSAGES;
    messages.header.size = sizeof(messages) - sizeof(messages.header);
    if (size_array((*client)->command) > 1)
        sprintf(messages.id, "%s", (*client)->command[1]);
    write((*client)->master_socket, &messages, sizeof(messages));
    free((*client)->command);
    (*client)->command = NULL;
}