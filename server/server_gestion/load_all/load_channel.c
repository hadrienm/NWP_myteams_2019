/*
** EPITECH PROJECT, 2020
** Visual Studio Live Share (Workspace)
** File description:
** load_channel
*/

#include "server.h"

static void add_node_channel_load_back(char **info, char *path, team_t **team)
{
    channel_t *new_node = malloc(sizeof(team_t));
    channel_t *base = (*team)->channel;

    for (; base && base->next != NULL; base = base->next);
    memset(new_node->name, 0, DEFAULT_NAME_LENGTH);
    memcpy(new_node->name, info[0], strlen(info[0]));
    new_node->path = strdup(path);
    new_node->next = NULL;
    memset(new_node->description, 0, DEFAULT_DESCRIPTION_LENGTH);
    memcpy(new_node->description, info[3], strlen(info[3]));
    memset(new_node->uuid, 0, SIZE_ID);
    memcpy(new_node->uuid, info[1], strlen(info[1]));
    new_node->timestamp = atoi(info[2]);
    new_node->thread = NULL;
    add_thread_load(&new_node);
    base->next = new_node;
}

static void add_node_channel_load(char **info, team_t **team, char *path)
{
    channel_t *new_node;

    if (info == NULL || size_array(info) != 4)
        return;
    if ((*team)->channel == NULL) {
        new_node = malloc(sizeof(channel_t));
        memset(new_node->uuid, 0, SIZE_ID);
        memset(new_node->name, 0, DEFAULT_NAME_LENGTH);
        memset(new_node->description, 0, DEFAULT_DESCRIPTION_LENGTH);
        memcpy(new_node->uuid, info[1], strlen(info[1]));
        memcpy(new_node->name, info[0], strlen(info[0]));
        memcpy(new_node->description, info[3], strlen(info[3]));
        new_node->thread = NULL;
        new_node->timestamp = atoi(info[2]);
        new_node->path = strdup(path);
        new_node->next = NULL;
        add_thread_load(&new_node);
        (*team)->channel = new_node;
    } else
        add_node_channel_load_back(info, path, team);
    free_array(info);
}

void add_channel_load(team_t **team)
{
    char **list_directories = ls_directories((*team)->path);
    char *str = NULL;
    char *name = NULL;
    char **info;

    if (list_directories == NULL)
        return;
    for (int i = 0; list_directories[i]; ++i) {
        name = get_name(list_directories[i]);
        str = get_all_info(name, list_directories[i]);
        if (str != NULL) {
            info = str_to_word_array(str, "\t");
            add_node_channel_load(info, team, list_directories[i]);
            free(str);
        }
        free(name);
    }
    free_array(list_directories);
}