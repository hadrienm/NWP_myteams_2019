/*
** EPITECH PROJECT, 2020
** NWP_myteams_2019
** File description:
** event_create.
*/

#include "client.h"

static void event_create_int(void *k, int index, stoc_create_t c)
{
    location_t local;
    int timestamp;

    memcpy(&local, k + index, sizeof(int));
    index += sizeof(int);
    memcpy(&timestamp, k + index, sizeof(int));
    switch (local) {
    case TEAM:
        return (void)client_event_team_created(c.team_uuid, c.name, \
c.description);
    case CHANNEL:
        return (void)client_event_channel_created(c.team_uuid, c.name, \
c.description);
    case THREAD:
        return (void)client_event_thread_created(c.team_uuid, c.user_uuid, \
timestamp, c.name, c.description);
    default:
        return (void)client_event_thread_message_received(c.team_uuid, \
c.thread_uuid, c.user_uuid, c.description);
    }
}

void event_create(void *k, int index)
{
    stoc_create_t c;

    memcpy(&c.team_uuid, k + index, SIZE_ID);
    index += SIZE_ID;
    memcpy(&c.user_uuid, k + index, SIZE_ID);
    index += SIZE_ID;
    memcpy(&c.thread_uuid, k + index, SIZE_ID);
    index += SIZE_ID;
    memcpy(&c.name, k + index, DEFAULT_NAME_LENGTH);
    index += DEFAULT_NAME_LENGTH;
    memcpy(&c.description, k + index, DEFAULT_BODY_LENGTH);
    index += DEFAULT_BODY_LENGTH;
    event_create_int(k, index, c);
}