/*
** EPITECH PROJECT, 2020
** Visual Studio Live Share (Workspace)
** File description:
** load_all
*/

#include "server.h"

static void add_node_replies_load_back(char **info, thread_t **thread)
{
    replies_t *new_node = malloc(sizeof(replies_t));
    replies_t *base = (*thread)->reply;

    for (; base && base->next != NULL; base = base->next);
    memset(new_node->user_uuid, 0, SIZE_ID);
    memset(new_node->body, 0, DEFAULT_BODY_LENGTH);
    new_node->timestamp = atoi(info[2]);
    memcpy(new_node->user_uuid, info[4], strlen(info[4]));
    new_node->next = NULL;
    memcpy(new_node->body, info[3], strlen(info[3]));
    base->next = new_node;
}

static void add_node_replies_load(char **info, thread_t **thread)
{
    replies_t *new_node = NULL;

    if (info == NULL || size_array(info) != 5)
        return;
    if ((*thread)->reply == NULL) {
        new_node = malloc(sizeof(replies_t));
        memset(new_node->user_uuid, 0, SIZE_ID);
        memset(new_node->body, 0, DEFAULT_BODY_LENGTH);
        new_node->timestamp = atoi(info[2]);
        memcpy(new_node->user_uuid, info[4], strlen(info[4]));
        new_node->next = NULL;
        memcpy(new_node->body, info[3], strlen(info[3]));
        (*thread)->reply = new_node;
    } else {
        add_node_replies_load_back(info, thread);
    }
}

void add_replies_load(thread_t **thread, char *path)
{

    (*thread)->reply = NULL;
    (*thread)->path = strdup(path);
    char **all_replies = NULL;
    char **info_reply = NULL;
    char *str = list_replies(path);

    if (str == NULL)
        return;
    all_replies = str_to_word_array(str, "\n");
    if (all_replies == NULL)
        return free(str);
    for (int i = 0; all_replies[i]; ++i) {
        info_reply = str_to_word_array(all_replies[i], "\t");
        add_node_replies_load(info_reply, thread);
        free_array(info_reply);
    }
    free(str);
    free_array(all_replies);
}