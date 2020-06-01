/*
** EPITECH PROJECT, 2020
** Visual Studio Live Share (Workspace)
** File description:
** users_send
*/

#include "server.h"

command_status_t users_set_rfc(int status)
{
    command_status_t rfc;

    memset(&rfc, 0, sizeof(rfc));
    rfc.header.name = RFC;
    rfc.header.size = RFC_CONTENT_SIZE;
    memset(rfc.id, 0, SIZE_ID);
    if (status == 200)
        sprintf(rfc.rfc_message, "%s", rfc_message[CODE_200]);
    else if (status == 500)
        sprintf(rfc.rfc_message, "%s", rfc_message[CODE_500]);
    return rfc;
}

void users_send_rfc(client_t **client, command_status_t rfc, size_t index)
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

static size_t set_buffer(client_t **client, size_t i, users_list_t *tmp)
{
    memcpy((*client)->answer + i, &tmp->users.header.name, sizeof(int));
    i += sizeof(int);
    memcpy((*client)->answer + i, &tmp->users.header.size, sizeof(size_t));
    i += sizeof(size_t);
    memcpy((*client)->answer + i, &tmp->users.id, SIZE_ID);
    i += SIZE_ID;
    memcpy((*client)->answer + i, &tmp->users.name, DEFAULT_NAME_LENGTH);
    i += DEFAULT_NAME_LENGTH;
    memcpy((*client)->answer + i, &tmp->users.status, sizeof(int));
    i += sizeof(int);
    return i;
}

static size_t send_users_answere(client_t **client, users_list_t **list)
{
    stoc_users_t users;
    size_t list_size = size_of_users_list(list);
    size_t size = USERS_SIZE * list_size + RFC_SIZE;
    size_t index = 0;

    (*client)->answer = malloc(size);
    memset((*client)->answer, 0, size);
    for (users_list_t *tmp = *list; tmp != NULL; tmp = tmp->next)
        index = set_buffer(client, index, tmp);
    (*client)->answer_size = size;
    return index;
}

void send_succes_list(client_t **client, server_data *server)
{
    command_status_t rfc;
    users_list_t *users_list = NULL;
    size_t index = 0;

    rfc = users_set_rfc(200);
    create_users_list(client, server, &users_list);
    index = send_users_answere(client, &users_list);
    users_send_rfc(client, rfc, index);
    free_users_list(&users_list);
}
