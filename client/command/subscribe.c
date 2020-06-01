/*
** EPITECH PROJECT, 2020
** NWP_myteams_2019
** File description:
** suscribe
*/

#include "client.h"

void subscribe_decrypt(client_data **client)
{
    char team_id[SIZE_ID];
    char user_id[SIZE_ID];
    size_t index = HEADER_SIZE;

    memcpy(&team_id, (*client)->read_buffer + index, SIZE_ID);
    index += SIZE_ID;
    memcpy(&user_id, (*client)->read_buffer + index, SIZE_ID);
    client_print_subscribed(user_id, team_id);
}

void subscribe(client_data **client)
{
    ctos_subscribe_t subscribe;

    memset(&subscribe, 0, sizeof(subscribe));
    subscribe.header.name = SUBSCRIBE;
    subscribe.header.size = sizeof(subscribe) - sizeof(subscribe.header);
    memset(subscribe.team_uuid, 0, SIZE_ID);
    if (size_array((*client)->command) > 1)
        sprintf(subscribe.team_uuid, "%s", (*client)->command[1]);
    write((*client)->master_socket, &subscribe, sizeof(subscribe));
    free((*client)->command);
    (*client)->command = NULL;
}