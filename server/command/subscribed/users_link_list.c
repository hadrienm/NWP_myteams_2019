/*
** EPITECH PROJECT, 2020
** NWP_myteams_2019
** File description:
** link_list
*/

#include "server.h"

static char **handle_line(char *line)
{
    char **result = malloc(sizeof(char *) * 3);
    result[0] = malloc(sizeof(char) * SIZE_ID);
    result[1] = malloc(sizeof(char) * (strlen(line) - SIZE_ID + 2));
    result[2] = NULL;
    size_t index = 0;

    memset(result[0], 0, SIZE_ID);
    memset(result[1], 0, strlen(line) - SIZE_ID + 2);
    for (int i = 0; index < SIZE_ID - 1; ++index, ++i)
        result[0][i] = line[index];
    for (int i = 0; line[index] != '\0'; ++index, ++i) {
        if (line[index] == '\n')
            break;
        result[1][i] = line[index];
    }
    return result;
}

static void add_first_user(subscribed_list_t **list, char **details, \
stoc_subscribed_t subscribed)
{
    subscribed_list_t *new_node = malloc(sizeof(subscribed_list_t));

    new_node->subscribed = subscribed;
    new_node->next = NULL;
    (*list) = new_node;
}

static void add_node_users_list(subscribed_list_t **list, char **details, \
stoc_subscribed_t subscribed)
{
    subscribed_list_t *new_node = NULL;
    subscribed_list_t *base = NULL;

    if (*list == NULL)
        return add_first_user(list, details, subscribed);
    new_node = malloc(sizeof(subscribed_list_t));
    base = (*list);
    for (; base->next != NULL; base = base->next);
    new_node->subscribed = subscribed;
    new_node->next = NULL;
    base->next = new_node;
}

static stoc_subscribed_t set_node_subscribed(char **details, client_t *all)
{
    stoc_subscribed_t subscribed;

    memset(&subscribed, 0, sizeof(stoc_subscribed_t));
    memset(subscribed.desription, 0, DEFAULT_DESCRIPTION_LENGTH);
    memset(subscribed.team_id, 0, SIZE_ID);
    memset(subscribed.user_id, 0, SIZE_ID);
    subscribed.header.name = SUBSCRIBED;
    subscribed.header.size = SUBSCRIBED_CONTENT_SIZE;
    subscribed.timestamp = 0;
    subscribed.status = check_users_is_log(details[0], all);
    sprintf(subscribed.user_id, "%s", details[0]);
    sprintf(subscribed.name, "%s", details[1]);
    return subscribed;
}

void subscribed_create_user_link_list(client_t **client, server_data *server, \
subscribed_list_t **users_list, char **list)
{
    char **user_details = NULL;
    stoc_subscribed_t subscribed;

    for (size_t i = 0; list[i] != NULL; ++i) {
        user_details = handle_line(list[i]);
        subscribed = set_node_subscribed(user_details, server->client);
        add_node_users_list(users_list, user_details, subscribed);
        free_array(user_details);
    }
    free_array(list);
}
