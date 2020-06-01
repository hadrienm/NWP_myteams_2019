/*
** EPITECH PROJECT, 2020
** Visual Studio Live Share (Workspace)
** File description:
** utils
*/

#include "server.h"

int check_users_is_log(char *user_id, client_t *all)
{
    for (client_t *tmp = all; tmp != NULL; tmp = tmp->next) {
        if (strncmp(tmp->uuid, user_id, SIZE_ID - 1) == 0)
            return 1;
    }
    return 0;
}

size_t size_of_users_list(users_list_t **list)
{
    size_t i = 0;

    for (users_list_t *tmp = *list; tmp != NULL; ++i, tmp = tmp->next);
    return i;
}
