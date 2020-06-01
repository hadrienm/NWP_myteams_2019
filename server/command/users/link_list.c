/*
** EPITECH PROJECT, 2020
** Visual Studio Live Share (Workspace)
** File description:
** link_list
*/

#include "server.h"

static void add_first_user(users_list_t **list, client_list_t *tmp, \
client_t *all)
{
    users_list_t *new_node = malloc(sizeof(users_list_t));

    if (new_node == NULL)
        return;
    memset(&new_node->users, 0, sizeof(users_list_t));
    new_node->users.header.name = USERS;
    new_node->users.header.size = USERS_CONTENT_SIZE;
    sprintf(new_node->users.id, "%s", tmp->uuid);
    sprintf(new_node->users.name, "%s", tmp->name);
    new_node->users.status = check_users_is_log(tmp->uuid, all);
    new_node->next = NULL;
    (*list) = new_node;
}

static void add_node_users_list(users_list_t **list, client_list_t *tmp, \
client_t *all)
{
    users_list_t *new_node = NULL;
    users_list_t *base = NULL;

    if (*list == NULL)
        return add_first_user(list, tmp, all);
    new_node = malloc(sizeof(users_list_t));
    if (new_node == NULL)
        return;
    base = (*list);
    for (; base->next != NULL; base = base->next);
    memset(&new_node->users, 0, sizeof(users_list_t));
    new_node->users.header.name = USERS;
    new_node->users.header.size = USERS_CONTENT_SIZE;
    sprintf(new_node->users.id, "%s", tmp->uuid);
    sprintf(new_node->users.name, "%s", tmp->name);
    new_node->users.status = check_users_is_log(tmp->uuid, all);
    new_node->next = NULL;
    base->next = new_node;
}

void create_users_list(client_t **client, server_data *svr, \
users_list_t **users_list)
{
    for (client_list_t *tmp = svr->client_list; tmp != NULL; tmp = tmp->next)
        add_node_users_list(users_list, tmp, svr->client);
}
