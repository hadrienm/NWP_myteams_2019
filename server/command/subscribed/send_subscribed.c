/*
** EPITECH PROJECT, 2020
** NWP_myteams_2019
** File description:
** send_subscribed
*/

#include "server.h"

static size_t size_of_subscribed_list(subscribed_list_t *list)
{
    size_t size = 0;
    subscribed_list_t *tmp = list;

    while (tmp != NULL) {
        ++size;
        tmp = tmp->next;
    }
    return size;
}

void subscribed_send_rfc(client_t **client, command_status_t rfc, size_t index)
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

command_status_t subscribed_set_rfc(int status, char team_id[SIZE_ID])
{
    command_status_t rfc;

    memset(&rfc, 0, sizeof(rfc));
    rfc.header.name = RFC;
    rfc.header.size = RFC_CONTENT_SIZE;
    memset(rfc.id, 0, SIZE_ID);
    if (status == 200) {
        sprintf(rfc.rfc_message, "%s", rfc_message[CODE_200]);
    } else if (status == 500) {
        sprintf(rfc.rfc_message, "%s", rfc_message[CODE_500]);
    } else {
        if (status == 503) {
            sprintf(rfc.rfc_message, "%s", rfc_message[CODE_503]);
            sprintf(rfc.id, "%s", team_id);
        }
    }
    return rfc;
}

static size_t set_buffer(client_t **client, size_t i, subscribed_list_t *tmp)
{
    memcpy((*client)->answer + i, &tmp->subscribed.header.name, sizeof(int));
    i += sizeof(int);
    memcpy((*client)->answer + i, &tmp->subscribed.header.size, \
sizeof(size_t));
    i += sizeof(size_t);
    memcpy((*client)->answer + i, &tmp->subscribed.team_id, SIZE_ID);
    i += SIZE_ID;
    memcpy((*client)->answer + i, &tmp->subscribed.user_id, SIZE_ID);
    i += SIZE_ID;
    memcpy((*client)->answer + i, &tmp->subscribed.desription, \
DEFAULT_DESCRIPTION_LENGTH);
    i += DEFAULT_DESCRIPTION_LENGTH;
    memcpy((*client)->answer + i, &tmp->subscribed.name, DEFAULT_NAME_LENGTH);
    i += DEFAULT_NAME_LENGTH;
    memcpy((*client)->answer + i, &tmp->subscribed.timestamp, sizeof(int));
    i += sizeof(int);
    memcpy((*client)->answer + i, &tmp->subscribed.status, sizeof(int));
    i += sizeof(int);
    return i;
}

size_t send_subscribed_answere(client_t **client, subscribed_list_t *list)
{
    stoc_users_t users;
    size_t list_size = size_of_subscribed_list(list);
    size_t size = SUBSCRIBED_SIZE * list_size + RFC_SIZE;
    size_t index = 0;

    (*client)->answer = malloc(size);
    memset((*client)->answer, 0, size);
    for (subscribed_list_t *tmp = list; tmp != NULL; tmp = tmp->next)
        index = set_buffer(client, index, tmp);
    (*client)->answer_size = size;
    return index;
}