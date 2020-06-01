/*
** EPITECH PROJECT, 2020
** NWP_myteams_2019
** File description:
** info
*/

#include "client.h"

void info_decrypt(client_data **client)
{
    char uuid[SIZE_ID] = {0};
    char name[DEFAULT_NAME_LENGTH] = {0};
    char description[DEFAULT_BODY_LENGTH] = {0};
    int timestamp = 0;
    time_t time;
    size_t index = HEADER_SIZE;

    memcpy(&description, (*client)->read_buffer + index, DEFAULT_BODY_LENGTH);
    index += DEFAULT_BODY_LENGTH;
    memcpy(&name, (*client)->read_buffer + index, DEFAULT_NAME_LENGTH);
    index += DEFAULT_NAME_LENGTH;
    memcpy(&uuid, (*client)->read_buffer + index, SIZE_ID);
    index += SIZE_ID;
    memcpy(&timestamp, (*client)->read_buffer + index, sizeof(int));
    time = (time_t)timestamp;
    if (strlen(description) == 0)
        dprintf(1, "info: %s %s\n", name, uuid);
    else if (timestamp == 0)
        dprintf(1, "info: %s %s %s\n", name, uuid, description);
    else
        dprintf(1, "info: %s %s %s %s", name, uuid, description, ctime(&time));
}

void info(client_data **client)
{
    ctos_info_t info;

    memset(&info, 0, sizeof(info));
    info.header.name = INFO;
    info.header.size = 0;
    write((*client)->master_socket, &info, sizeof(info));
    free((*client)->command);
    (*client)->command = NULL;
}
