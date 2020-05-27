/*
** EPITECH PROJECT, 2020
** NWP_myteams_2019
** File description:
** event_create.
*/

#include "client.h"

static void event_create_int(void *k, int index, char *array[5])
{
    location_t local;
    int timestamp;

    memcpy(&local, k + index, sizeof(int));
    index += sizeof(int);
    memcpy(&timestamp, k + index, sizeof(int));
    if (local == TEAM)
        client_event_team_created(array[0], array[3], array[4]);
    else if (local == CHANNEL)
        client_event_channel_created(array[0], array[3], array[4]);
    else if (local == THREAD)
        client_event_thread_created(array[0], array[1], timestamp, array[3], \
array[4]);
    else
        client_event_thread_message_received(array[0], array[2], \
array[1], array[4]);
}

void event_create(void *k, int index)
{
    char team_uuid[SIZE_ID];
    char user_uuid[SIZE_ID];
    char thread_uuid[SIZE_ID];
    char name[DEFAULT_NAME_LENGTH];
    char description[DEFAULT_BODY_LENGTH];

    memcpy(&team_uuid, k + index, SIZE_ID);
    index += SIZE_ID;
    memcpy(&user_uuid, k + index, SIZE_ID);
    index += SIZE_ID;
    memcpy(&thread_uuid, k + index, SIZE_ID);
    index += SIZE_ID;
    memcpy(&name, k + index, DEFAULT_NAME_LENGTH);
    index += DEFAULT_NAME_LENGTH;
    memcpy(&description, k + index, DEFAULT_BODY_LENGTH);
    index += DEFAULT_BODY_LENGTH;
    event_create_int(k, index, (char *[5]){team_uuid, user_uuid, thread_uuid, \
name, description});
}