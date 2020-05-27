/*
** EPITECH PROJECT, 2020
** NWP_myteams_2019
** File description:
** unsubscribe
*/

#include "client.h"

void unsubscribe_decrypt(stoc_header_t *header, size_t readed, \
client_data **client)
{
    char team_id[SIZE_ID];
    char user_id[SIZE_ID];
    size_t index = 0;

    void *k = malloc(header->size);
    read((*client)->master_socket, k, header->size);
    memcpy(&user_id, k, SIZE_ID);
    index += SIZE_ID;
    memcpy(&team_id, k + index, SIZE_ID);
    client_print_unsubscribed(user_id, team_id);
    free(k);
}

void unsubscribe(client_data **client)
{
    ctos_unsubscribe_t unsubscribe;

    memset(&unsubscribe, 0, sizeof(unsubscribe));
    unsubscribe.header.name = UNSUBSCRIBE;
    unsubscribe.header.size = sizeof(unsubscribe) - sizeof(unsubscribe.header);
    if (size_array((*client)->command) > 1)
        sprintf(unsubscribe.team_uuid, "%s", (*client)->command[1]);
    write((*client)->master_socket, &unsubscribe, sizeof(ctos_unsubscribe_t));
    free((*client)->command);
    (*client)->command = NULL;
}
