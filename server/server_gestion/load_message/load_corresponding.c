/*
** EPITECH PROJECT, 2020
** NWP_myteams_2019
** File description:
** load_corresping
*/

#include "server.h"

static void add_first_corresponding(corresponding_t **cpr_list, char **uuid, \
char **details)
{
    corresponding_t *new_node = NULL;

    new_node = malloc(sizeof(corresponding_t));
    sprintf(new_node->uuid1, "%s", uuid[0]);
    sprintf(new_node->uuid2, "%s", uuid[1]);
    new_node->msg_list = NULL;
    add_message_to_list(&new_node->msg_list, details);
    new_node->next = NULL;
    (*cpr_list) = new_node;
}

void add_corresponding(corresponding_t **cpr_list, char **uuid, char **details)
{
    corresponding_t *new_node = NULL;

    if (*cpr_list == NULL)
        return add_first_corresponding(cpr_list, uuid, details);
    for (corresponding_t *tmp = *cpr_list; tmp != NULL; tmp = tmp->next)
        if ((strcmp(uuid[0], tmp->uuid1) == 0 || strcmp(uuid[0], \
tmp->uuid2) == 0) && (strcmp(uuid[1], tmp->uuid1) == 0 || strcmp(uuid[1], \
tmp->uuid2) == 0))
            return add_message_to_list(&tmp->msg_list, details);
    corresponding_t *base = (*cpr_list);
    for (; base->next != NULL; base = base->next);
    new_node = malloc(sizeof(corresponding_t));
    sprintf(new_node->uuid1, "%s", uuid[0]);
    sprintf(new_node->uuid2, "%s", uuid[1]);
    new_node->msg_list = NULL;
    add_message_to_list(&new_node->msg_list, details);
    new_node->next = NULL;
    base->next = new_node;
}
