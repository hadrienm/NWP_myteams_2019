/*
** EPITECH PROJECT, 2020
** NWP_myteams_2019
** File description:
** message_error
*/

#include "server.h"

static command_status_t set_send_messages(int status, char id[SIZE_ID])
{
    command_status_t rfc;

    memset(&rfc, 0, sizeof(rfc));
    rfc.header.name = RFC;
    rfc.header.size = SIZE_ID + RFC_MESSAGE_LENGTH;
    memset(rfc.rfc_message, 0, RFC_MESSAGE_LENGTH);
    memset(rfc.id, 0, SIZE_ID);
    if (status == 500)
        sprintf(rfc.rfc_message, "%s", rfc_message[CODE_500]);
    else if (status == 401)
        sprintf(rfc.rfc_message, "%s", rfc_message[CODE_401]);
    else if (status == 502) {
        sprintf(rfc.id, "%s", id);
        sprintf(rfc.rfc_message, "%s", rfc_message[CODE_502]);
    }
    return rfc;
}

void send_message_rfc(int status, client_t **client, char id[SIZE_ID])
{
    command_status_t rfc = set_send_messages(status, id);
    size_t size = sizeof(int) + sizeof(size_t) + RFC_MESSAGE_LENGTH + SIZE_ID;
    size_t index = 0;

    (*client)->answer = malloc(size);
    memset((*client)->answer, 0, size);
    memcpy((*client)->answer, &rfc.header.name, sizeof(int));
    index += sizeof(int);
    memcpy((*client)->answer + index, &rfc.header.size, sizeof(size_t));
    index += sizeof(size_t);
    memcpy((*client)->answer + index, &rfc.rfc_message, RFC_MESSAGE_LENGTH);
    index += RFC_MESSAGE_LENGTH;
    memcpy((*client)->answer + index, &rfc.id, SIZE_ID);
    (*client)->answer_size = size;
}