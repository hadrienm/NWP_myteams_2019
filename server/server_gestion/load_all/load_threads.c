/*
** EPITECH PROJECT, 2020
** Visual Studio Live Share (Workspace)
** File description:
** load_threads
*/

#include "server.h"

static void add_node_thread_load_back(char **info, char *path, \
channel_t **channel)
{
    thread_t *new_node = malloc(sizeof(thread_t));
    thread_t *base = (*channel)->thread;

    for (; base && base->next != NULL; base = base->next);
    memset(new_node->description, 0, DEFAULT_BODY_LENGTH);
    memset(new_node->uuid, 0, SIZE_ID);
    memset(new_node->name, 0, DEFAULT_NAME_LENGTH);
    memset(new_node->sender, 0, SIZE_ID);
    memcpy(new_node->description, info[3], strlen(info[3]));
    memcpy(new_node->name, info[0], strlen(info[0]));
    new_node->next = NULL;
    new_node->timestamp = atoi(info[2]);
    memcpy(new_node->uuid, info[1], strlen(info[1]));
    memcpy(new_node->sender, info[4], strlen(info[4]) - 1);
    new_node->reply = NULL;
    add_replies_load(&new_node, path);
    base->next = new_node;
}

static void add_node_thread_load(char **info, channel_t **channel, char *path)
{
    thread_t *new_node;

    if (info == NULL || size_array(info) != 5)
        return;
    if ((*channel)->thread == NULL) {
        new_node = malloc(sizeof(thread_t));
        memset(new_node->description, 0, DEFAULT_BODY_LENGTH);
        memset(new_node->uuid, 0, SIZE_ID);
        memset(new_node->name, 0, DEFAULT_NAME_LENGTH);
        memset(new_node->sender, 0, SIZE_ID);
        memcpy(new_node->description, info[3], strlen(info[3]));
        memcpy(new_node->name, info[0], strlen(info[0]));
        new_node->next = NULL;
        new_node->timestamp = atoi(info[2]);
        memcpy(new_node->uuid, info[1], strlen(info[1]));
        memcpy(new_node->sender, info[4], strlen(info[4]) - 1);
        add_replies_load(&new_node, path);
        (*channel)->thread = new_node;
    } else
        add_node_thread_load_back(info, path, channel);
    free_array(info);
}

void add_thread_load(channel_t **channel)
{
    char **list_directories = ls_directories((*channel)->path);
    char *str = NULL;
    char *name = NULL;
    char **info = NULL;

    if (list_directories == NULL)
        return;
    for (int i = 0; list_directories[i]; ++i) {
        name = get_name(list_directories[i]);
        str = get_all_info(name, list_directories[i]);
        if (str != NULL) {
            info = str_to_word_array(str, "\t");
            add_node_thread_load(info, channel, list_directories[i]);
            free(str);
        }
        free(name);
    }
    free_array(list_directories);
}