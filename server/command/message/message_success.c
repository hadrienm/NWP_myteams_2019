/*
** EPITECH PROJECT, 2020
** NWP_myteams_2019
** File description:
** message_sucess
*/

#include "server.h"

static void send_rfc_success(size_t size, client_t **client, size_t index)
{
    command_status_t rfc;
    char id[SIZE_ID] = {0};

    memset(&rfc, 0, sizeof(rfc));
    rfc.header.name = RFC;
    rfc.header.size = SIZE_ID + RFC_MESSAGE_LENGTH;
    memset(rfc.rfc_message, 0, RFC_MESSAGE_LENGTH);
    sprintf(rfc.rfc_message, "%s", rfc_message[CODE_200]);
    sprintf(rfc.id, "%s", id);
    memcpy((*client)->answer + index, &rfc.header.name, sizeof(int));
    index += sizeof(int);
    memcpy((*client)->answer + index, &rfc.header.size, sizeof(size_t));
    index += sizeof(size_t);
    memcpy((*client)->answer + index, &rfc.rfc_message, RFC_MESSAGE_LENGTH);
    index += RFC_MESSAGE_LENGTH;
    memcpy((*client)->answer + index, &rfc.id, SIZE_ID);
    (*client)->answer_size = size;
}

static size_t set_buffer(client_t **client, size_t i, messages_list_t *tmp)
{
    memcpy((*client)->answer + i, &tmp->message.header.name, sizeof(int));
    i += sizeof(int);
    memcpy((*client)->answer + i, &tmp->message.header.size, sizeof(size_t));
    i += sizeof(size_t);
    memcpy((*client)->answer + i, &(tmp->message.id), SIZE_ID);
    i += SIZE_ID;
    memcpy((*client)->answer + i, &(tmp->message.message), \
DEFAULT_BODY_LENGTH);
    i += DEFAULT_BODY_LENGTH;
    memcpy((*client)->answer + i, &(tmp->message.timestamp), sizeof(int));
    i += sizeof(int);
    return i;
}

static void send_mesages_answere(char *answere, client_t **client, \
messages_list_t **list)
{
    stoc_messages_t messages;
    size_t list_size = size_of_list(*list);
    size_t size = (sizeof(int) * 2 + sizeof(size_t) + SIZE_ID + \
DEFAULT_BODY_LENGTH) * list_size + sizeof(int) + sizeof(size_t) \
+ RFC_MESSAGE_LENGTH + SIZE_ID;
    size_t i = 0;

    (*client)->answer = malloc(size);
    memset((*client)->answer, 0, size);
    for (messages_list_t *tmp = *list; tmp != NULL; tmp = tmp->next)
        i = set_buffer(client, i, tmp);
    send_rfc_success(size, client, i);
}

void messages_success(client_t **client, char id[SIZE_ID])
{
    messages_list_t *messages_list = NULL;
    char *path = NULL;
    char *list = NULL;

    path = message_create_path(id, (*client)->uuid);
    if (path == NULL) {
        send_message_rfc(502, client, id);
        return;
    }
    list = list_conversation(path);
    init_message_list(&messages_list, list);
    send_mesages_answere(list, client, &messages_list);
    free(list);
    free(path);
    free_message_list(&messages_list);
}