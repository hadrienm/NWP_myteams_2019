/*
** EPITECH PROJECT, 2020
** NWP_myteams_2019
** File description:
** create
*/

#include "client.h"

static void print_create_int(char *buffer, int index, stoc_create_t c)
{
    location_t local;
    int timestamp;

    memcpy(&local, buffer + index, sizeof(int));
    index += sizeof(int);
    memcpy(&timestamp, buffer + index, sizeof(int));
    switch (local) {
    case TEAM:
        return (void)client_print_team_created(c.team_uuid, c.name, \
c.description);
    case CHANNEL:
        return (void)client_print_channel_created(c.team_uuid, c.name, \
c.description);
    case THREAD:
        return (void)client_print_thread_created(c.team_uuid, c.user_uuid, \
timestamp, c.name, c.description);
    default:
        return (void)client_print_reply_created(c.thread_uuid, c.user_uuid, \
timestamp, c.description);
    }
}

static void print_create(char *buffer, size_t index)
{
    stoc_create_t create;

    memcpy(&create.team_uuid, buffer + index, SIZE_ID);
    index += SIZE_ID;
    memcpy(&create.user_uuid, buffer + index, SIZE_ID);
    index += SIZE_ID;
    memcpy(&create.thread_uuid, buffer + index, SIZE_ID);
    index += SIZE_ID;
    memcpy(&create.name, buffer + index, DEFAULT_NAME_LENGTH);
    index += DEFAULT_NAME_LENGTH;
    memcpy(&create.description, buffer + index, DEFAULT_BODY_LENGTH);
    index += DEFAULT_BODY_LENGTH;
    print_create_int(buffer, index, create);
}

void create_decrypt(client_data **client)
{
    bool event;
    size_t index = HEADER_SIZE;

    memcpy(&event, (*client)->read_buffer + index, sizeof(bool));
    index += sizeof(bool);
    if (event)
        print_create((*client)->read_buffer, index);
    else
        event_create((*client)->read_buffer, index);
}

void create(client_data **client)
{
    ctos_create_t create;

    memset(&create, 0, sizeof(create));
    memset(create.name, 0, DEFAULT_NAME_LENGTH);
    memset(create.message, 0, DEFAULT_BODY_LENGTH);
    memset(create.uuid, 0, SIZE_ID);
    create.header.name = CREATE;
    create.header.size = sizeof(create) - sizeof(create.header);
    if (size_array((*client)->command) > 2) {
        sprintf(create.name, "%s", (*client)->command[1]);
        sprintf(create.message, "%s", (*client)->command[2]);
    }
    else if (size_array((*client)->command) > 1) {
        sprintf(create.message, "%s", (*client)->command[1]);
    }
    write((*client)->master_socket, &create, sizeof(create));
    free((*client)->command);
    (*client)->command = NULL;
}
