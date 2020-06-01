/*
** EPITECH PROJECT, 2020
** NWP_myteams_2019
** File description:
** create_broadcast
*/

#include "server.h"

static void *create_set_broadcast_buffer_two(stoc_create_t c, size_t index, \
void *buffer)
{
    memcpy(buffer + index, &c.name, DEFAULT_NAME_LENGTH);
    index += DEFAULT_NAME_LENGTH;
    memcpy(buffer + index, &c.description, DEFAULT_BODY_LENGTH);
    index += DEFAULT_BODY_LENGTH;
    memcpy(buffer + index, &c.local, sizeof(int));
    index += sizeof(int);
    memcpy(buffer + index, &c.timestamp, sizeof(int));
}

void *create_set_broadcast_buffer(stoc_create_t c)
{
    void *buffer = malloc(CREATE_SIZE);
    size_t index = 0;
    c.event = false;

    memset(buffer, 0, CREATE_SIZE);
    memcpy(buffer, &c.header.name, sizeof(int));
    index += sizeof(int);
    memcpy(buffer + index, &c.header.size, sizeof(size_t));
    index += sizeof(size_t);
    memcpy(buffer + index, &c.event, sizeof(bool));
    index += sizeof(bool);
    memcpy(buffer + index, &c.team_uuid, SIZE_ID);
    index += SIZE_ID;
    memcpy(buffer + index, &c.user_uuid, SIZE_ID);
    index += SIZE_ID;
    memcpy(buffer + index, &c.thread_uuid, SIZE_ID);
    index += SIZE_ID;
    create_set_broadcast_buffer_two(c, index, buffer);
    return buffer;
}

static char *handle_line(char *line)
{
    char *id = malloc(sizeof(char) * SIZE_ID);
    size_t index = 0;

    memset(id, 0, SIZE_ID);
    for (int i = 0; index < SIZE_ID - 1; ++index, ++i)
        id[i] = line[index];
    return id;
}

char **create_broadcast_subscribe_list(team_t *t, char *user_id)
{
    char **list = NULL;
    char *tmp = NULL;
    size_t index = 0;

    if (t->user_subscribe == NULL)
        return NULL;
    list = malloc(sizeof(char *) * (size_array(t->user_subscribe) + 1));
    for (size_t i = 0; t->user_subscribe[i] != NULL; ++i, ++index) {
        tmp = handle_line(t->user_subscribe[i]);
        list[index] = strdup(tmp);
        free(tmp);
    }
    list[index] = NULL;
    return list;
}
