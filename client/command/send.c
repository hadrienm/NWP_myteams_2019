/*
** EPITECH PROJECT, 2020
** NWP_myteams_2019
** File description:
** send
*/

#include "client.h"

void send_decrypt(stoc_header_t *header, size_t readed, client_data **client)
{
    char user_id[SIZE_ID];
    char message[DEFAULT_BODY_LENGTH];
    size_t index = 0;

    void *k = malloc(header->size);
    read((*client)->master_socket, k, header->size);
    memcpy(&user_id, k, SIZE_ID);
    index += SIZE_ID;
    memcpy(&message, k + index, DEFAULT_BODY_LENGTH);
    free(k);
    client_event_private_message_received(user_id, message);
}

void send_c(client_data **client)
{
    ctos_send_t send;

    memset(&send, 0, sizeof(send));
    send.header.name = SEND;
    send.header.size = sizeof(send) - sizeof(send.header);
    memset(send.uuid, 0, SIZE_ID);
    memset(send.body, 0, DEFAULT_BODY_LENGTH);
    if (size_array((*client)->command) > 2) {
        if (strlen((*client)->command[1]) > SIZE_ID)
            printf("402 Bad arguments\r\n");
        else
            sprintf(send.uuid, "%s", (*client)->command[1]);
        if (strlen((*client)->command[2]) > DEFAULT_BODY_LENGTH)
            printf("404 Too long message\r\n");
        else
            sprintf(send.body, "%s", (*client)->command[2]);
    }
    if (strlen(send.body) > 0 && strlen(send.uuid) > 0)
        write((*client)->master_socket, &send, sizeof(send));
    free((*client)->command);
    (*client)->command = NULL;
}
