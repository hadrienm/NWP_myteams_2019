/*
** EPITECH PROJECT, 2020
** NWP_myteams_2019
** File description:
** send_error
*/

#include "server.h"

void send_rfc(client_t **client, command_status_t rfc, size_t index)
{
    if (index == 0) {
        (*client)->answer = malloc(rfc_size);
        memset((*client)->answer, 0, rfc_size);
        (*client)->answer_size = rfc_size;
    }
    memcpy((*client)->answer + index, &rfc.header.name, sizeof(int));
    index += sizeof(int);
    memcpy((*client)->answer + index, &rfc.header.size, sizeof(size_t));
    index += sizeof(size_t);
    memcpy((*client)->answer + index, &rfc.rfc_message, RFC_MESSAGE_LENGTH);
    index += RFC_MESSAGE_LENGTH;
    memcpy((*client)->answer + index, &rfc.id, SIZE_ID);
    index += SIZE_ID;
}

command_status_t set_send_rfc(int status, char id[SIZE_ID])
{
    command_status_t rfc;

    memset(&rfc, 0, sizeof(rfc));
    memset(rfc.rfc_message, 0, RFC_MESSAGE_LENGTH);
    memset(rfc.id, 0, SIZE_ID);
    rfc.header.name = RFC;
    rfc.header.size = rfc_content_size;
    if (status == 500) {
        sprintf(rfc.rfc_message, "%s", rfc_message[CODE_500]);
    } else if (status == 401) {
        sprintf(rfc.rfc_message, "%s", rfc_message[CODE_401]);
    } else if (status == 502) {
        sprintf(rfc.id, "%s", id);
        sprintf(rfc.rfc_message, "%s", rfc_message[CODE_502]);
    } else {
        sprintf(rfc.rfc_message, "%s", rfc_message[CODE_200]);
    }
    return rfc;
}
