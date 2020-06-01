/*
** EPITECH PROJECT, 2020
** NWP_myteams_2019
** File description:
** unsubscribe_broadcast
*/

#include "server.h"

static void *create_unsubscribe_broadcast_buffer(stoc_unsubscribe_t unsub)
{
    void *buffer = NULL;
    size_t index = 0;
    size_t size = UNSUBSCRIBE_SIZE;

    buffer = malloc(size);
    memset(buffer, 0, size);
    memcpy(buffer, &unsub.header.name, sizeof(int));
    index += sizeof(int);
    memcpy(buffer + index, &unsub.header.size, sizeof(size_t));
    index += sizeof(size_t);
    memcpy(buffer + index, &unsub.team_id, SIZE_ID);
    index += SIZE_ID;
    memcpy(buffer + index, &unsub.user_id, SIZE_ID);
    return buffer;
}

static char **push_array(char **list, char *str)
{
    char **tmp = NULL;
    size_t size = 1;
    size_t index = 0;

    if (size_array(list) == 0) {
        free_array(list);
        list = NULL;
    }
    for (; list && list[size] != NULL; ++size);
    tmp = malloc(sizeof(char *) * (size + 2));
    for (; list && list[index] != NULL; ++index)
        tmp[index] = strdup(list[index]);
    tmp[index] = strdup(str);
    tmp[index + 1] = NULL;
    free_array(list);
    return tmp;
}

void unsubscribe_set_broadcast(stoc_unsubscribe_t unsub, \
char team_id[SIZE_ID], char *user_id, server_data **server)
{
    char **list = NULL;
    char *path = found_path_team(team_id);
    void *buffer = create_unsubscribe_broadcast_buffer(unsub);

    for (team_t *t = (*server)->team; t; t = t->next)
        if (strncmp(team_id, t->uuid, SIZE_ID - 1) == 0)
            list = copy_array(t->user_subscribe);
    list = push_array(list, user_id);
    send_unsubscribe_brodcast(buffer, team_id, &(*server)->client, list);
    free(path);
    free(buffer);
    free_array(list);
}
