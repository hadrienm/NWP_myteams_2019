/*
** EPITECH PROJECT, 2020
** NWP_myteams_2019
** File description:
** subscribed
*/

#include "client.h"

static decrypt_subscribed_t set_subscribed_decrypt(client_data **client, \
stoc_header_t *header)
{
    decrypt_subscribed_t sub;
    size_t index = 0;

    void *k = malloc(header->size);
    read((*client)->master_socket, k, header->size);
    memcpy(&sub.team_id, k, SIZE_ID);
    index += SIZE_ID;
    memcpy(&sub.user_id, k + index, SIZE_ID);
    index += SIZE_ID;
    memcpy(&sub.description, k + index, DEFAULT_DESCRIPTION_LENGTH);
    index += DEFAULT_DESCRIPTION_LENGTH;
    memcpy(&sub.name, k + index, DEFAULT_NAME_LENGTH);
    index += DEFAULT_NAME_LENGTH;
    memcpy(&sub.timestamp, k + index, sizeof(int));
    index += sizeof(int);
    memcpy(&sub.status, k + index, sizeof(int));
    index += sizeof(int);
    free(k);
    return sub;
}

void subscribed_decrypt(stoc_header_t *header, size_t readed, \
client_data **client)
{
    decrypt_subscribed_t sub = set_subscribed_decrypt(client, header);

    if (sub.timestamp == 0)
        printf("%s %s %d\n", sub.user_id, sub.name, sub.status);
    else
        printf("%s %s %ld\n", sub.team_id, sub.description, \
(time_t)sub.timestamp);
}

void subscribed(client_data **client)
{
    ctos_subscribed_t subscribed;

    memset(&subscribed, '\0', sizeof(ctos_subscribed_t));
    subscribed.header.name = SUBSCRIBED;
    subscribed.header.size = sizeof(subscribed) - sizeof(subscribed.header);
    memset(subscribed.team_uuid, 0, SIZE_ID);
    if (size_array((*client)->command) > 1)
        sprintf(subscribed.team_uuid, "%s", (*client)->command[1]);
    write((*client)->master_socket, &subscribed, sizeof(ctos_subscribed_t));
    free((*client)->command);
    (*client)->command = NULL;
}
