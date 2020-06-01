/*
** EPITECH PROJECT, 2020
** NWP_myteams_2019
** File description:
** send_list
*/

#include "server.h"

command_status_t list_set_rfc(int status, char team_id[SIZE_ID])
{
    command_status_t rfc;

    memset(&rfc, 0, sizeof(rfc));
    rfc.header.name = RFC;
    rfc.header.size = RFC_CONTENT_SIZE;
    memset(rfc.id, 0, SIZE_ID);
    if (status == 200) {
        sprintf(rfc.rfc_message, "%s", rfc_message[CODE_200]);
    } else if (status == 500)
        sprintf(rfc.rfc_message, "%s", rfc_message[CODE_500]);
    return rfc;
}

void list_send_rfc(client_t **client, command_status_t rfc, size_t index)
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

static size_t list_set_buffer(size_t index, client_t **client, list_list_t \
*tmp)
{
    memcpy((*client)->answer + index, &tmp->list.header.name, sizeof(int));
    index += sizeof(int);
    memcpy((*client)->answer + index, &tmp->list.header.size, sizeof(size_t));
    index += sizeof(size_t);
    memcpy((*client)->answer + index, &tmp->list.team_uuid, SIZE_ID);
    index += SIZE_ID;
    memcpy((*client)->answer + index, &tmp->list.user_uuid, SIZE_ID);
    index += SIZE_ID;
    memcpy((*client)->answer + index, &tmp->list.body, DEFAULT_BODY_LENGTH);
    index += DEFAULT_BODY_LENGTH;
    memcpy((*client)->answer + index, &tmp->list.name, DEFAULT_NAME_LENGTH);
    index += DEFAULT_NAME_LENGTH;
    memcpy((*client)->answer + index, &tmp->list.time, sizeof(int));
    index += sizeof(int);
    memcpy((*client)->answer + index, &tmp->list.function, sizeof(location_t));
    index += sizeof(location_t);
    return index;
}

void send_list_success(client_t **client, char *str)
{
    command_status_t rfc = list_set_rfc(200, NULL);
    list_list_t *link_list = NULL;
    size_t link_size = 0;
    size_t size = 0;
    size_t index = 0;

    create_link_list(str, &link_list, client);
    link_size = list_link_size(link_list);
    size = LIST_SIZE * link_size + RFC_SIZE;
    (*client)->answer = malloc(size);
    memset((*client)->answer, 0, size);
    for (list_list_t *tmp = link_list; tmp != NULL; tmp = tmp->next)
        index = list_set_buffer(index, client, tmp);
    (*client)->answer_size = size;
    list_send_rfc(client, rfc, index);
}