/*
** EPITECH PROJECT, 2020
** NWP_myteams_2019
** File description:
** create_teams
*/

#include "server.h"

static void add_team_simple_back(ctos_create_t create, team_t **team, \
char temp[20], char *new_uuid)
{
    team_t *new_node = malloc(sizeof(team_t));
    team_t *base = *team;

    for (; base && base->next != NULL; base = base->next);
    memset(new_node->name, 0, DEFAULT_NAME_LENGTH);
    memcpy(new_node->name, create.name, strlen(create.name));
    new_node->path = my_strcat("./save/", create.name);
    new_node->next = NULL;
    memset(new_node->description, 0, DEFAULT_DESCRIPTION_LENGTH);
    memcpy(new_node->description, create.message, strlen(create.message));
    new_node->user_subscribe = NULL;
    new_node->timestamp = atoi(temp);
    memset(new_node->uuid, 0, SIZE_ID);
    memcpy(new_node->uuid, new_uuid, strlen(new_uuid));
    new_node->channel = NULL;
    base->next = new_node;
}

static void add_team_simple(ctos_create_t create, team_t **team, \
char temp[20], char *new_uuid)
{
    team_t *new_node = NULL;

    if (*team == NULL) {
        new_node = malloc(sizeof(team_t));
        memset(new_node->name, 0, DEFAULT_NAME_LENGTH);
        memcpy(new_node->name, create.name, strlen(create.name));
        new_node->path = my_strcat("./save/", create.name);
        new_node->next = NULL;
        new_node->timestamp = atoi(temp);
        memset(new_node->description, 0, DEFAULT_DESCRIPTION_LENGTH);
        memcpy(new_node->description, create.message, strlen(create.message));
        new_node->user_subscribe = NULL;
        memset(new_node->uuid, 0, SIZE_ID);
        memcpy(new_node->uuid, new_uuid, strlen(new_uuid));
        new_node->channel = NULL;
        *team = new_node;
    } else
        add_team_simple_back(create, team, temp, new_uuid);
}

int add_teams(client_t ** client, ctos_create_t create, server_data **s, \
char *new_uuid)
{
    stoc_create_t c = memset_all(create, TEAM, client);
    char temp[20] = {0};
    char *str = NULL;

    if (strlen(create.name) == 0 || strlen(create.message) == 0)
        return 0;
    sprintf(c.team_uuid, "%s", new_uuid);
    sprintf(create.uuid, "%s", new_uuid);
    if (!verify_name(create.name))
        return 0;
    str = my_strcat("./save/", create.name);
    if (check_path_exist(str, "./save") == true)
        return 2;
    sprintf(temp, "%d", (int)time(NULL));
    free(str);
    add_team_simple(create, &(*s)->team, temp, new_uuid);
    server_event_team_created(create.uuid, create.name, (*client)->uuid);
    send_create(client, 0, c);
    create_broadcast(client, &(*s)->client, create_set_broadcast_buffer(c));
    return 1;
}
