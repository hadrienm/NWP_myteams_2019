/*
** EPITECH PROJECT, 2020
** NWP_myteams_2019
** File description:
** link_list_messages
*/

#include "server.h"

static void add_first_message(messages_list_t **list, char **details)
{
    messages_list_t *new_node = malloc(sizeof(messages_list_t));

    if (new_node == NULL)
        return;
    memset(&new_node->message, 0, sizeof(stoc_messages_t));
    new_node->message.header.name = MESSAGES;
    new_node->message.header.size = sizeof(int) + SIZE_ID + \
DEFAULT_BODY_LENGTH;
    sprintf(new_node->message.id , "%s", details[0]);
    sprintf(new_node->message.message , "%s", details[2]);
    new_node->message.timestamp = atoi(details[1]);
    new_node->next = NULL;
    (*list) = new_node;
}

static void add_node_messages_list(messages_list_t **list, char **details)
{
    messages_list_t *new_node = NULL;
    messages_list_t *base = NULL;

    if (*list == NULL) {
        add_first_message(list, details);
        return;
    }
    new_node = malloc(sizeof(messages_list_t));
    if (new_node == NULL)
        return;
    base = (*list);
    for (; base->next != NULL; base = base->next);
    memset(&new_node->message, 0, sizeof(stoc_messages_t));
    new_node->message.header.name = MESSAGES;
    new_node->message.header.size = sizeof(int) + SIZE_ID + \
DEFAULT_BODY_LENGTH;
    sprintf(new_node->message.id , "%s", details[0]);
    sprintf(new_node->message.message , "%s", details[2]);
    new_node->message.timestamp = atoi(details[1]);
    new_node->next = NULL;
    base->next = new_node;
}

void init_message_list(messages_list_t **messages_list, char *line)
{
    char **messages_array = str_to_word_array(line, "\n");
    char **message_details = NULL;

    for (int i = 0; messages_array[i] != NULL; ++i) {
        message_details = str_to_word_array(messages_array[i], "\t");
        add_node_messages_list(messages_list, message_details);
        free(message_details);
    }
    free_array(messages_array);
}

static void delete_first_node(messages_list_t **message)
{
    messages_list_t *new_list = (*message);

    new_list = (*message)->next;
    free((*message));
    (*message) = new_list;
}

void free_message_list(messages_list_t **list)
{
    messages_list_t * current = (*list);
    messages_list_t * next;

    while (current != NULL) {
        next = current->next;
        delete_first_node(list);
        current = next;
    }
}