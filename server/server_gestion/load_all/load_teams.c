/*
** EPITECH PROJECT, 2020
** Visual Studio Live Share (Workspace)
** File description:
** load_teams
*/

#include "server.h"

static void add_node_teams_load_back(char **info, char *path, char **sub, \
team_t **team)
{
    team_t *new_node = malloc(sizeof(team_t));
    team_t *base = *team;

    for (; base && base->next != NULL; base = base->next);
    memset(new_node->name, 0, DEFAULT_NAME_LENGTH);
    memcpy(new_node->name, info[0], strlen(info[0]));
    new_node->path = strdup(path);
    new_node->next = NULL;
    memset(new_node->description, 0, DEFAULT_DESCRIPTION_LENGTH);
    memcpy(new_node->description, info[3], strlen(info[3]));
    new_node->user_subscribe = copy_array(sub);
    new_node->timestamp = atoi(info[2]);
    memset(new_node->uuid, 0, SIZE_ID);
    memcpy(new_node->uuid, info[1], strlen(info[1]));
    new_node->channel = NULL;
    add_channel_load(&new_node);
    base->next = new_node;
}

static void memset_add_node_teams_load(team_t *new_node, char **info, \
char *path)
{
    memset(new_node->name, 0, DEFAULT_NAME_LENGTH);
    memcpy(new_node->name, info[0], strlen(info[0]));
    new_node->path = strdup(path);
    new_node->next = NULL;
    new_node->timestamp = atoi(info[2]);
}

static void add_node_teams_load(team_t **team, char *str, char **sub, \
char *path)
{
    team_t *new_node;
    char **info = str_to_word_array(str, "\t");

    if (info == NULL || size_array(info) != 4)
        return;
    if (*team == NULL) {
        new_node = malloc(sizeof(team_t));
        memset_add_node_teams_load(new_node, info, path);
        memset(new_node->description, 0, DEFAULT_DESCRIPTION_LENGTH);
        memcpy(new_node->description, info[3], strlen(info[3]));
        new_node->user_subscribe = copy_array(sub);
        memset(new_node->uuid, 0, SIZE_ID);
        memcpy(new_node->uuid, info[1], strlen(info[1]));
        new_node->channel = NULL;
        add_channel_load(&new_node);
        *team = new_node;
    } else
        add_node_teams_load_back(info, path, sub, team);
    free_array(info);
}

static void add_teams_load(char *path, team_t **team)
{
    char *name = get_name(path);
    char *str = NULL;
    char **user_subscribed = NULL;

    str = get_all_info(name, path);
    if (str == NULL)
        return;
    str[strlen(str) - 1] = 0;
    user_subscribed = read_after_line1(path, "/default.txt");
    add_node_teams_load(team, str, user_subscribed, path);
    free(name);
    free(str);
    free_array(user_subscribed);
}

void load_all(server_data **server)
{
    char **list_directories = ls_directories("./save/");

    (*server)->team = NULL;
    if (list_directories == NULL)
        return;
    for (int i = 0; list_directories[i]; ++i) {
        add_teams_load(list_directories[i], &(*server)->team);
    }
    team_t *tmp = (*server)->team;
    free_array(list_directories);
}