/*
** EPITECH PROJECT, 2020
** NWP_myteams_2019
** File description:
** link_list
*/

#include "server.h"

size_t list_link_size(list_list_t *list)
{
    size_t size = 0;

    for (list_list_t *tmp = list; tmp != NULL; tmp = tmp->next, ++size);
    return size;
}

static void add_first_list(list_list_t **list, char **details, location_t \
which)
{
    list_list_t *new_node = malloc(sizeof(list_list_t));

    memset(&new_node->list, 0, sizeof(stoc_list_t));
    memset(new_node->list.name, 0, DEFAULT_NAME_LENGTH);
    memset(new_node->list.team_uuid, 0, SIZE_ID);
    memset(new_node->list.body, 0, DEFAULT_BODY_LENGTH);
    new_node->list.header.name = LIST;
    new_node->list.header.size = LIST_CONTENT_SIZE;
    sprintf(new_node->list.team_uuid, "%s", details[1]);
    sprintf(new_node->list.name, "%s", details[0]);
    new_node->list.time = atoi(details[2]);
    sprintf(new_node->list.body, "%s", details[3]);
    if (details[4] != NULL)
        sprintf(new_node->list.user_uuid, "%s", details[4]);
    else
        memset(new_node->list.user_uuid, 0, SIZE_ID);
    new_node->list.function = which;
    new_node->next = NULL;
    (*list) = new_node;
}

static void complement(char **details, list_list_t *new_node, location_t which)
{
    memset(new_node->list.name, 0, DEFAULT_NAME_LENGTH);
    memset(new_node->list.team_uuid, 0, SIZE_ID);
    memset(new_node->list.body, 0, DEFAULT_BODY_LENGTH);
    new_node->list.header.name = LIST;
    new_node->list.header.size = LIST_CONTENT_SIZE;
    sprintf(new_node->list.team_uuid, "%s", details[1]);
    sprintf(new_node->list.name, "%s", details[0]);
    new_node->list.time = atoi(details[2]);
    sprintf(new_node->list.body, "%s", details[3]);
    if (details[4] != NULL)
        sprintf(new_node->list.user_uuid, "%s", details[4]);
    else
        memset(new_node->list.user_uuid, 0, SIZE_ID);
    new_node->list.function = which;
}

void add_node_list(list_list_t **list, char **details, location_t which)
{
    list_list_t *new_node = NULL;
    list_list_t *base = NULL;

    if (*list == NULL)
        return add_first_list(list, details, which);
    new_node = malloc(sizeof(list_list_t));
    base = (*list);
    for (; base->next != NULL; base = base->next);
    memset(&new_node->list, 0, sizeof(stoc_list_t));
    complement(details, new_node, which);
    new_node->next = NULL;
    base->next = new_node;
}

void create_link_list(char *str, list_list_t **link_list, client_t **client)
{
    char **line = str_to_word_array(str, "\n");
    char **details = NULL;
    location_t which = determine_use((*client)->use_path);

    for (size_t i = 0; line[i] != NULL; ++i) {
        if (strlen(line[i]) < SIZE_ID - 1)
            continue;
        details = str_to_word_array(line[i], "\t");
        add_node_list(link_list, details, which);
        free_array(details);
    }
    free_array(line);
}
