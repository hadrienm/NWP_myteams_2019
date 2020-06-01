/*
** EPITECH PROJECT, 2020
** NWP_myteams_2019
** File description:
** list
*/

#include "client.h"

static int list_int(char *buffer, int index, stoc_list_t l)
{
    int timestamp;
    location_t location;

    memcpy(&timestamp, buffer + index, sizeof(int));
    index += sizeof(int);
    memcpy(&location, buffer + index, sizeof(location_t));
    switch (location) {
    case TEAM:
        return client_print_teams(l.team_uuid, l.name, l.body);
    case CHANNEL:
        return client_team_print_channels(l.team_uuid, l.name, l.body);
    case THREAD:
        return client_channel_print_threads(l.team_uuid, l.user_uuid, \
(time_t)timestamp, l.name, l.body);
    case REPLIES:
        return client_thread_print_replies(l.team_uuid, l.user_uuid, \
(time_t)timestamp, l.body);
    default:
        break;
    }
}

void list_decrypt(client_data **client)
{
    stoc_list_t l;
    char team_id[SIZE_ID];
    char uuid[SIZE_ID];
    char body[DEFAULT_BODY_LENGTH];
    char name[DEFAULT_NAME_LENGTH];
    size_t index = HEADER_SIZE;

    memcpy(&l.team_uuid, (*client)->read_buffer + index, SIZE_ID);
    index += SIZE_ID;
    memcpy(&l.user_uuid, (*client)->read_buffer + index, SIZE_ID);
    index += SIZE_ID;
    memcpy(&l.body, (*client)->read_buffer + index, DEFAULT_BODY_LENGTH);
    index += DEFAULT_BODY_LENGTH;
    memcpy(&l.name, (*client)->read_buffer + index, DEFAULT_NAME_LENGTH);
    index += DEFAULT_NAME_LENGTH;
    list_int((*client)->read_buffer, index, l);
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