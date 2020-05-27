/*
** EPITECH PROJECT, 2020
** NWP_myteams_2019
** File description:
** send_sucess
*/

#include "server.h"

static void send_message_to_reicever(char uuid[SIZE_ID], client_t **all, \
void *buffer)
{
    size_t index = 0;

    for (client_t *tmp = *all; tmp != NULL; tmp = tmp->next) {
        if (strcmp(uuid, tmp->uuid) == 0) {
            tmp->answer = malloc(send_size);
            memcpy(tmp->answer, buffer, send_size);
            tmp->answer_size = send_size;
            return;
        }
    }
}

static void *set_send_buffer(stoc_send_t send)
{
    size_t index = 0;
    void *buffer = malloc(send_size);

    memset(buffer, 0, send_size);
    memcpy(buffer + index, &send.header.name, sizeof(int));
    index += sizeof(int);
    memcpy(buffer + index, &send.header.size, sizeof(size_t));
    index += sizeof(size_t);
    memcpy(buffer + index, &send.user_id, SIZE_ID);
    index += SIZE_ID;
    memcpy(buffer + index, &send.message_body, DEFAULT_BODY_LENGTH);
    index += DEFAULT_BODY_LENGTH;
    return buffer;
}

void set_send_s(client_t **client, ctos_send_t sender, client_t **all)
{
    stoc_send_t send;
    size_t size = rfc_size;
    command_status_t rfc = set_send_rfc(200, NULL);
    void *buffer;

    memset(&send, 0, sizeof(send));
    send.header.name = SEND;
    send.header.size = send_content_size;
    memset(send.user_id, 0, SIZE_ID);
    memset(send.message_body, 0, DEFAULT_BODY_LENGTH);
    sprintf(send.user_id, "%s", (*client)->uuid);
    sprintf(send.message_body, "%s", sender.body);
    buffer = set_send_buffer(send);
    send_message_to_reicever(sender.uuid, all, buffer);
    send_rfc(client, rfc, 0);
}
