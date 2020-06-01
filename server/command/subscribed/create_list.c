/*
** EPITECH PROJECT, 2020
** NWP_myteams_2019
** File description:
** create_list
*/

#include "server.h"

static bool is_subscribe_to_team(char *user_uid, char **user_list)
{
    if (user_list == NULL)
        return false;
    for (size_t i = 0; user_list[i] != NULL; ++i) {
        if (strncmp(user_uid, user_list[i], SIZE_ID - 1) == 0)
            return true;
    }
}

char **subscribed_create_teams_list(server_data *server, char *uuid)
{
    char *str = NULL;
    char **value = NULL;
    char buff[30] = {0};

    for (team_t *tmp = server->team; tmp != NULL; tmp = tmp->next) {
        if (is_subscribe_to_team(uuid, tmp->user_subscribe) == true) {
            my_const_strcat(&str, tmp->uuid);
            my_const_strcat(&str, "\t");
            sprintf(buff, "%d", (int)time(NULL));
            my_const_strcat(&str, buff);
            my_const_strcat(&str, "\t");
            my_const_strcat(&str, tmp->name);
            my_const_strcat(&str, "\n");
        }
    }
    if (str == NULL)
        return NULL;
    value = str_to_word_array(str, "\n");
    free(str);
    return value;
}

bool check_team(char team_id[SIZE_ID], server_data *server)
{
    for (team_t *tmp = server->team; tmp != NULL; tmp = tmp->next)
        if (strncmp(team_id, tmp->uuid, SIZE_ID - 1) == 0)
            return true;
    return false;
}

char **subscribed_create_users_list(char team_id[SIZE_ID], server_data *server)
{
    for (team_t *tmp = server->team; tmp != NULL; tmp = tmp->next)
        if (strncmp(team_id, tmp->uuid, SIZE_ID - 1) == 0)
            return copy_array(tmp->user_subscribe);
}
