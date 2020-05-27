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
    void *buffer = malloc(create_size);
    size_t index = 0;
    c.event = false;

    memset(buffer, 0, create_size);
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

static char **push_array(char **list, char *str)
{
    char **tmp = NULL;
    size_t size = 1;
    size_t index = 0;

    for (; list && list[size] != NULL; ++size);
    tmp = malloc(sizeof(char *) * (size + 2));
    for (; list && list[index] != NULL; ++index)
        tmp[index] = strdup(list[index]);
    tmp[index] = strdup(str);
    tmp[index + 1] = NULL;
    free_array(list);
    return tmp;
}

static char **handle_list(char *line, char **list)
{
    char *tmp = malloc(sizeof(char) * SIZE_ID);
    memset(tmp, 0, SIZE_ID);

    for (int j = 0; j < SIZE_ID - 1; ++j)
        tmp[j] = line[j];
    return push_array(list, tmp);
}

char **create_broadcast_subscribe_list(char *path, char * user_uid)
{
    char **list = NULL;
    char *line = NULL;
    FILE * file;
    size_t useless = 0;
    size_t index = 0;

    if (path == NULL)
        return NULL;
    file = fopen(path, "r");
    if (file == NULL)
        return NULL;
    for (; getline(&line, &useless, file) != -1; ++index)
        if (index > 0 && strlen(line) >= SIZE_ID && \
strncmp(line, user_uid, SIZE_ID - 1) != 0)
            list = handle_list(line, list);
    fclose(file);
    return list;
}