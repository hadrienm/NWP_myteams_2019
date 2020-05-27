/*
** EPITECH PROJECT, 2020
** NWP_myteams_2019
** File description:
** send
*/

#include "server.h"

command_status_t set_rfc(int status, char user_id[SIZE_ID])
{
    command_status_t rfc;

    memset(&rfc, 0, sizeof(rfc));
    rfc.header.name = RFC;
    rfc.header.size = rfc_content_size;
    memset(rfc.id, 0, SIZE_ID);
    if (status == 200) {
        sprintf(rfc.rfc_message, "%s", rfc_message[CODE_200]);
    } else if (status == 502) {
        sprintf(rfc.rfc_message, "%s", rfc_message[CODE_502]);
        sprintf(rfc.id, "%s", user_id);
    } else if (status == 500) {
        sprintf(rfc.rfc_message, "%s", rfc_message[CODE_500]);
    } else {
        sprintf(rfc.rfc_message, "%s", rfc_message[CODE_401]);
    }
    return rfc;
}

void user_send_rfc(client_t **client, command_status_t rfc, size_t index)
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
}

void user_send_success(stoc_user_t user, command_status_t rfc, \
client_t **client)
{
    size_t size = rfc_size + user_size;
    size_t index = 0;

    (*client)->answer = malloc(size);
    memset((*client)->answer, 0, size);
    memcpy((*client)->answer, &user.header.name, sizeof(int));
    index += sizeof(int);
    memcpy((*client)->answer + index, &user.header.size, sizeof(size_t));
    index += sizeof(size_t);
    memcpy((*client)->answer + index, &user.id, SIZE_ID);
    index += SIZE_ID;
    memcpy((*client)->answer + index, &user.name, DEFAULT_NAME_LENGTH);
    index += DEFAULT_NAME_LENGTH;
    memcpy((*client)->answer + index, &user.status, sizeof(int));
    index += sizeof(int);
    (*client)->answer_size = size;
    user_send_rfc(client, rfc, index);
}
