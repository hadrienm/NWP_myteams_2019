/*
** EPITECH PROJECT, 2020
** NWP_myteams_2019
** File description:
** use
*/

#include "client.h"

void use_decrypt(stoc_header_t *header, size_t readed, client_data **client)
{
    char answer[RFC_MESSAGE_LENGTH] = {0};

    void *k = malloc(header->size);
    read((*client)->master_socket, k, header->size);
    memcpy(&answer, k, RFC_MESSAGE_LENGTH);
    dprintf(1, "%s", answer);
    free(k);
}

void use(client_data **client)
{
    ctos_use_t use;

    memset(&use, '\0', sizeof(ctos_use_t));
    use.header.name = USE;
    use.header.size = sizeof(use) - sizeof(use.header);
    memset(&use.team_uuid, 0, SIZE_ID);
    memset(&use.channel_uuid, 0, SIZE_ID);
    memset(&use.thread_uuid, 0, SIZE_ID);
    if (size_array((*client)->command) > 3)
        sprintf(use.thread_uuid, "%s", (*client)->command[3]);
    if (size_array((*client)->command) > 2)
        sprintf(use.channel_uuid, "%s", (*client)->command[2]);
    if (size_array((*client)->command) > 1)
        sprintf(use.team_uuid, "%s", (*client)->command[1]);
    write((*client)->master_socket, &use, sizeof(ctos_use_t));
    free((*client)->command);
    (*client)->command = NULL;
}