/*
** EPITECH PROJECT, 2020
** NWP_myteams_2019
** File description:
** team_link_list
*/

#include "server.h"

static void add_first_team(subscribed_list_t **list, char **details, \
client_t **all)
{
    subscribed_list_t *new_node = malloc(sizeof(subscribed_list_t));

    memset(&new_node->subscribed, 0, sizeof(stoc_subscribed_t));
    memset(&new_node->subscribed.desription, 0, DEFAULT_DESCRIPTION_LENGTH);
    memset(&new_node->subscribed.team_id, 0, SIZE_ID);
    new_node->subscribed.timestamp = 0;
    new_node->subscribed.header.name = SUBSCRIBED;
    new_node->subscribed.header.size = subscribed_content_size;
    sprintf(new_node->subscribed.team_id, "%s", details[0]);
    sprintf(new_node->subscribed.desription, "%s", details[2]);
    new_node->subscribed.timestamp = atoi(details[1]);
    new_node->next = NULL;
    (*list) = new_node;
}

static void add_node_team_list(subscribed_list_t **list, char **details, \
client_t **all)
{
    subscribed_list_t *new_node = NULL;
    subscribed_list_t *base = NULL;

    if (*list == NULL)
        return add_first_team(list, details, all);
    new_node = malloc(sizeof(subscribed_list_t));
    base = (*list);
    for (; base->next != NULL; base = base->next);
    memset(&new_node->subscribed, 0, sizeof(stoc_subscribed_t));
    memset(&new_node->subscribed.desription, 0, DEFAULT_DESCRIPTION_LENGTH);
    memset(&new_node->subscribed.team_id, 0, SIZE_ID);
    new_node->subscribed.timestamp = 0;
    new_node->subscribed.header.name = SUBSCRIBED;
    new_node->subscribed.header.size = subscribed_content_size;
    sprintf(new_node->subscribed.team_id, "%s", details[0]);
    sprintf(new_node->subscribed.desription, "%s", details[2]);
    new_node->subscribed.timestamp = atoi(details[1]);
    new_node->next = NULL;
    base->next = new_node;
}

static void handle_teams_list(subscribed_list_t **teams_list, char *line, \
client_t **all)
{
    char **team_details = str_to_word_array(line, "\t");

    add_node_team_list(teams_list, team_details, all);
    free_array(team_details);
}

void subscribed_create_teams_link_list(client_t **client, client_t **all, \
subscribed_list_t **teams_list, char **list)
{
    for (size_t i = 0; list[i] != NULL; ++i)
        handle_teams_list(teams_list, list[i], all);
}
