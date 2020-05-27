/*
** EPITECH PROJECT, 2020
** NWP_myteams_2019
** File description:
** create
*/

#include "client.h"

static void print_create_int(void *buffer, int index, char *array[5])
{
    location_t local;
    int timestamp;

    memcpy(&local, buffer + index, sizeof(int));
    index += sizeof(int);
    memcpy(&timestamp, buffer + index, sizeof(int));
    if (local == TEAM)
        client_print_team_created(array[0], array[3], array[4]);
    else if (local == CHANNEL)
        client_print_channel_created(array[0], array[3], array[4]);
    else if (local == THREAD)
        client_print_thread_created(array[0], array[1], timestamp, array[3], \
array[4]);
    else
        client_print_reply_created(array[2], array[1], timestamp, array[4]);
}

static void print_create(void *buffer, size_t index)
{
    char team_uuid[SIZE_ID];
    char user_uuid[SIZE_ID];
    char thread_uuid[SIZE_ID];
    char name[DEFAULT_NAME_LENGTH];
    char description[DEFAULT_BODY_LENGTH];

    memcpy(&team_uuid, buffer + index, SIZE_ID);
    index += SIZE_ID;
    memcpy(&user_uuid, buffer + index, SIZE_ID);
    index += SIZE_ID;
    memcpy(&thread_uuid, buffer + index, SIZE_ID);
    index += SIZE_ID;
    memcpy(&name, buffer + index, DEFAULT_NAME_LENGTH);
    index += DEFAULT_NAME_LENGTH;
    memcpy(&description, buffer + index, DEFAULT_BODY_LENGTH);
    index += DEFAULT_BODY_LENGTH;
    print_create_int(buffer, index, (char *[5]){team_uuid, user_uuid, \
thread_uuid, name, description});
}

void create_decrypt(stoc_header_t *header, size_t readed, client_data **client)
{
    bool event;
    void *k = malloc(header->size);

    read((*client)->master_socket, k, header->size);
    memcpy(&event, k, sizeof(bool));
    if (event)
        event_create(k, sizeof(bool));
    else
        print_create(k, sizeof(bool));
    free(k);
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
