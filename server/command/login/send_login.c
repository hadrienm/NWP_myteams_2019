/*
** EPITECH PROJECT, 2020
** Visual Studio Live Share (Workspace)
** File description:
** send_login
*/

#include "server.h"

size_t set_user_send(client_t **client, stoc_login_t login, client_t **all)
{
    size_t size = LOGIN_SIZE + RFC_SIZE;
    size_t index = 0;

    (*client)->answer = malloc(size);
    memset((*client)->answer, 0, size);
    memcpy((*client)->answer + index, &login.header.name, sizeof(int));
    index += sizeof(int);
    memcpy((*client)->answer + index, &login.header.size, sizeof(size_t));
    index += sizeof(size_t);
    memcpy((*client)->answer + index, &login.user_id, SIZE_ID);
    index += SIZE_ID;
    memcpy((*client)->answer + index, &login.name, DEFAULT_NAME_LENGTH);
    index += DEFAULT_NAME_LENGTH;
    (*client)->answer_size = size;
    return index;
}

void login_send_rfc(client_t **client, command_status_t rfc, size_t index)
{
    if (index == 0) {
        (*client)->answer = malloc(RFC_SIZE);
        memset((*client)->answer, 0, RFC_SIZE);
        (*client)->answer_size = RFC_SIZE;
    }
    memcpy((*client)->answer + index, &rfc.header.name, sizeof(int));
    index += sizeof(int);
    memcpy((*client)->answer + index, &rfc.header.size, sizeof(size_t));
    index += sizeof(size_t);
    memcpy((*client)->answer + index, &rfc.rfc_message, RFC_MESSAGE_LENGTH);
    index += RFC_MESSAGE_LENGTH;
    memcpy((*client)->answer + index, &rfc.id, SIZE_ID);
}

command_status_t set_login_rfc(int status)
{
    command_status_t rfc;

    memset(&rfc, 0, RFC_SIZE);
    memset(rfc.id, 0, SIZE_ID);
    memset(rfc.rfc_message, 0, RFC_MESSAGE_LENGTH);
    rfc.header.name = RFC;
    rfc.header.size = RFC_CONTENT_SIZE;
    if (status == 200) {
        sprintf(rfc.rfc_message, "%s", rfc_message[CODE_200]);
    } else {
        sprintf(rfc.rfc_message, "%s", rfc_message[CODE_401]);
    }
    return rfc;
}

