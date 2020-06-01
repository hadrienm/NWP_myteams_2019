/*
** EPITECH PROJECT, 2020
** NWP_myteams_2019
** File description:
** send_help
*/

#include "server.h"

void help_send(client_t **client, stoc_help_t help)
{
    size_t index = 0;
    size_t size = RFC_SIZE + HELP_SIZE;

    (*client)->answer = malloc(size);
    memset((*client)->answer, 0, size);
    memcpy((*client)->answer, &help.header.name, sizeof(int));
    index += sizeof(int);
    memcpy((*client)->answer + index, &help.header.size, sizeof(size_t));
    index += sizeof(size_t);
    memcpy((*client)->answer + index, &help.body_answer, DEFAULT_BODY_LENGTH);
    (*client)->answer_size = size;
}

command_status_t set_help_rfc(int status)
{
    command_status_t rfc;

    memset(&rfc, 0, RFC_SIZE);
    memset(rfc.rfc_message, 0, RFC_MESSAGE_LENGTH);
    memset(rfc.id, 0, SIZE_ID);
    rfc.header.name = RFC;
    rfc.header.size = RFC_CONTENT_SIZE;
    if (status == 200) {
        sprintf(rfc.rfc_message, "%s", rfc_message[CODE_200]);
    } else {
        sprintf(rfc.rfc_message, "%s", rfc_message[CODE_402]);
    }
    return rfc;
}