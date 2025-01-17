/*
** EPITECH PROJECT, 2020
** NWP_myteams_2019
** File description:
** send_suscribe
*/

#include "server.h"

command_status_t subscribe_set_rfc(int status, char team_id[SIZE_ID])
{
    command_status_t rfc;

    memset(&rfc, 0, sizeof(rfc));
    rfc.header.name = RFC;
    rfc.header.size = RFC_CONTENT_SIZE;
    memset(rfc.id, 0, SIZE_ID);
    if (status == 200) {
        sprintf(rfc.rfc_message, "%s", rfc_message[CODE_200]);
    } else if (status == 503) {
        sprintf(rfc.rfc_message, "%s", rfc_message[CODE_503]);
        sprintf(rfc.id, "%s", team_id);
    } else {
        if (status == 500)
            sprintf(rfc.rfc_message, "%s", rfc_message[CODE_500]);
        else
            sprintf(rfc.rfc_message, "%s", rfc_message[CODE_401]);
    }
    return rfc;
}

stoc_subscribe_t set_subscribe(char *user_id, char team_id[SIZE_ID])
{
    stoc_subscribe_t subscribe;

    memset(&subscribe, 0, sizeof(subscribe));
    memset(subscribe.team_id, 0, SIZE_ID);
    memset(subscribe.user_id, 0, SIZE_ID);
    subscribe.header.name = SUBSCRIBE;
    subscribe.header.size = SUBSCRIBE_CONTENT_SIZE;
    sprintf(subscribe.team_id, "%s", team_id);
    sprintf(subscribe.user_id, "%s", user_id);
    return subscribe;
}

void subscribe_send_rfc(client_t **client, command_status_t rfc, size_t index)
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

void realloc_buffer(client_t **client, size_t size)
{
    char *save = NULL;

    save = malloc((*client)->answer_size + size);
    memset(save, 0, (*client)->answer_size + size);
    memcpy(save, (*client)->answer, (*client)->answer_size);
    free((*client)->answer);
    (*client)->answer_size += size;
    (*client)->answer = malloc((*client)->answer_size);
    memcpy((*client)->answer, save, (*client)->answer_size);
    free(save);
}

bool subscribe_read(team_t *team, char *uuid, char *team_uuid)
{
    team_t *t = team;

    for (; t; t = t->next) {
        if (strncmp(t->uuid, team_uuid, SIZE_ID - 1) == 0)
            break;
    }
    if (t == NULL)
        return false;
    for (int i = 0; t->user_subscribe && t->user_subscribe[i]; ++i) {
        if (strncmp(t->user_subscribe[i], uuid, SIZE_ID - 1) == 0)
            return true;
    }
    return false;
}
