/*
** EPITECH PROJECT, 2020
** NWP_myteams_2019
** File description:
** unsubscribe_error
*/

#include "server.h"

void unsubscribe_send_rfc(client_t **client, command_status_t rfc, size_t index)
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

command_status_t unsubscribe_set_rfc(int status, char team_id[SIZE_ID])
{
    command_status_t rfc;

    memset(&rfc, 0, sizeof(rfc));
    rfc.header.name = RFC;
    rfc.header.size = rfc_content_size;
    memset(rfc.id, 0, SIZE_ID);
    if (status == 200) {
        sprintf(rfc.rfc_message, "%s", rfc_message[CODE_200]);
    } else if (status == 503) {
        sprintf(rfc.rfc_message, "%s", rfc_message[CODE_503]);
        sprintf(rfc.id, "%s", team_id);
    } else if (status == 500) {
        sprintf(rfc.rfc_message, "%s", rfc_message[CODE_500]);
    } else {
        sprintf(rfc.rfc_message, "%s", rfc_message[CODE_401]);
    }
    return rfc;
}

void set_unsubscribe_success(client_t **client, char team_id[SIZE_ID], \
client_t **all)
{
    stoc_unsubscribe_t unsubscribe;
    size_t size = unsubscribe_size;
    command_status_t rfc = unsubscribe_set_rfc(200, NULL);

    memset(&unsubscribe, 0, size);
    memset(unsubscribe.team_id, 0, SIZE_ID);
    memset(unsubscribe.user_id, 0, SIZE_ID);
    unsubscribe.header.name = UNSUBSCRIBE;
    unsubscribe.header.size = unsubscribe_content_size;
    sprintf(unsubscribe.team_id, "%s", team_id);
    sprintf(unsubscribe.user_id, "%s", (*client)->uuid);
    (*client)->answer_size = size;
    unsubscribe_set_broadcast(unsubscribe, team_id, (*client)->uuid, all);
    realloc_buffer(client, rfc_size);
    unsubscribe_send_rfc(client, rfc, unsubscribe_size);
}