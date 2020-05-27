/*
** EPITECH PROJECT, 2020
** Visual Studio Live Share (Workspace)
** File description:
** delete
*/

#include "server.h"

static void delete_first_node(users_list_t **users)
{
    users_list_t *new_list = (*users);

    new_list = (*users)->next;
    free((*users));
    (*users) = new_list;
}

void free_users_list(users_list_t **list)
{
    users_list_t * current = (*list);
    users_list_t * next;

    while (current != NULL) {
        next = current->next;
        delete_first_node(list);
        current = next;
    }
}
