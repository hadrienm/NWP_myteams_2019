/*
** EPITECH PROJECT, 2020
** NWP_myteams_2019
** File description:
** list
*/

#include "client.h"

static int list_int(void *k, int index, char *a[4])
{
    int timestamp;
    location_t location;

    memcpy(&timestamp, k + index, sizeof(int));
    index += sizeof(int);
    memcpy(&location, k + index, sizeof(location_t));
    switch (location) {
    case TEAM:
        return client_print_teams(a[0], a[3], a[2]);
    case CHANNEL:
        return client_team_print_channels(a[0], a[3], a[2]);
    case THREAD:
        return client_channel_print_threads(a[0], a[1], (time_t)timestamp, \
a[3], a[2]);
    case REPLIES:
        return client_thread_print_replies(a[0], a[1], (time_t)timestamp, \
a[2]);
    default:
        break;
    }
}

void list_decrypt(stoc_header_t *header, size_t readed, client_data **client)
{
    char team_id[SIZE_ID];
    char uuid[SIZE_ID];
    char body[DEFAULT_BODY_LENGTH];
    char name[DEFAULT_NAME_LENGTH];
    size_t index = 0;

    void *k = malloc(header->size);
    read((*client)->master_socket, k, header->size);
    memcpy(&team_id, k, SIZE_ID);
    index += SIZE_ID;
    memcpy(&uuid, k + index, SIZE_ID);
    index += SIZE_ID;
    memcpy(&body, k + index, DEFAULT_BODY_LENGTH);
    index += DEFAULT_BODY_LENGTH;
    memcpy(&name, k + index, DEFAULT_NAME_LENGTH);
    index += DEFAULT_NAME_LENGTH;
    list_int(k, index, (char *[4]){team_id, uuid, body, name});
    free(k);
}

void list(client_data **client)
{
    ctos_list_t list;

    memset(&list, 0, sizeof(list));
    list.header.name = LIST;
    list.header.size = 0;
    write((*client)->master_socket, &list, sizeof(list));
    free((*client)->command);
    (*client)->command = NULL;
}