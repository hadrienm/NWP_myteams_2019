/*
** EPITECH PROJECT, 2020
** NWP_myteams_2019
** File description:
** link_list
*/

#include "server.h"

static char *handle_line(char *line)
{
    char *tmp = NULL;
    char *id = malloc(sizeof(char) * SIZE_ID);
    char *name = malloc(sizeof(char) * (strlen(line) - SIZE_ID + 2));
    size_t index = 0;

    memset(name, 0, strlen(line) - SIZE_ID + 2);
    memset(id, 0, SIZE_ID);
    for (int i = 0; index < SIZE_ID - 1; ++index, ++i)
        id[i] = line[index];
    for (int i = 0; line[index] != '\0'; ++index, ++i) {
        if (line[index] == '\n')
            break;
        name[i] = line[index];
    }
    my_const_strcat(&tmp, id);
    my_const_strcat(&tmp, " ");
    my_const_strcat(&tmp, name);
    free(id);
    free(name);
    return tmp;
}

static void add_first_user(subscribed_list_t **list, char **details, \
client_t **all)
{
    subscribed_list_t *new_node = malloc(sizeof(subscribed_list_t));

    memset(&new_node->subscribed, 0, sizeof(stoc_subscribed_t));
    memset(&new_node->subscribed.desription, 0, DEFAULT_DESCRIPTION_LENGTH);
    memset(&new_node->subscribed.team_id, 0, SIZE_ID);
    new_node->subscribed.timestamp = 0;
    new_node->subscribed.header.name = SUBSCRIBED;
    new_node->subscribed.header.size = subscribed_content_size;
    sprintf(new_node->subscribed.user_id, "%s", details[0]);
    sprintf(new_node->subscribed.name, "%s", details[1]);
    new_node->subscribed.status = check_users_is_log(details[0], all);
    new_node->next = NULL;
    (*list) = new_node;
}

static void add_node_users_list(subscribed_list_t **list, char **details, \
client_t **all)
{
    subscribed_list_t *new_node = NULL;
    subscribed_list_t *base = NULL;

    if (*list == NULL)
        return add_first_user(list, details, all);
    new_node = malloc(sizeof(subscribed_list_t));
    base = (*list);
    for (; base->next != NULL; base = base->next);
    memset(&new_node->subscribed, 0, sizeof(stoc_subscribed_t));
    memset(&new_node->subscribed.desription, 0, DEFAULT_DESCRIPTION_LENGTH);
    memset(&new_node->subscribed.team_id, 0, SIZE_ID);
    new_node->subscribed.timestamp = 0;
    new_node->subscribed.header.name = SUBSCRIBED;
    new_node->subscribed.header.size = subscribed_content_size;
    sprintf(new_node->subscribed.user_id, "%s", details[0]);
    sprintf(new_node->subscribed.name, "%s", details[1]);
    new_node->subscribed.status = check_users_is_log(details[0], all);
    new_node->next = NULL;
    base->next = new_node;
}

static void handle_users_list(subscribed_list_t **user_list, char *line, \
client_t **all)
{
    char *tmp = handle_line(line);
    char **user_details = str_to_word_array(tmp, " ");

    add_node_users_list(user_list, user_details, all);
    free_array(user_details);
    free(tmp);
}

void subscribed_create_user_link_list(client_t **client, client_t **all, \
subscribed_list_t **users_list, char **list)
{

    for (size_t i = 0; list[i] != NULL; ++i)
        handle_users_list(users_list, list[i], all);
}
