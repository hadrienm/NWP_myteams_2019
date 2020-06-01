/*
** EPITECH PROJECT, 2020
** NWP_myteams_2019
** File description:
** suscribe
*/

#include "server.h"

static char **add_array(char **arr, char *uuid, char *name)
{
    char *str = my_strcat(uuid, name);
    char **array = NULL;
    int i = 0;

    array = malloc(sizeof(char *) * (size_array(arr) + 2));
    for (; arr && arr[i]; ++i) {
        array[i] = strdup(arr[i]);
    }
    array[i] = strdup(str);
    array[i + 1] = NULL;
    free(str);
    return array;
}

static bool found_user_to_teams(client_t **client, team_t *t)
{
    for (int i = 0; t->user_subscribe && t->user_subscribe[i]; ++i) {
        if (strncmp(t->user_subscribe[i], (*client)->uuid, SIZE_ID - 1) == 0)
            return true;
    }
    return false;
}

static int subscribe_to_teams(client_t **client, char *uuid, server_data \
**server)
{
    char **save = NULL;

    for (team_t *t = (*server)->team; t; t = t->next) {
        if (strncmp(t->uuid, uuid, SIZE_ID - 1) != 0)
            continue;
        if (found_user_to_teams(client, t) == true)
            return 1;
        save = add_array(t->user_subscribe, (*client)->uuid, (*client)->name);
        free_array(t->user_subscribe);
        t->user_subscribe = copy_array(save);
        free_array(save);
        return 0;
    }
    return 2;
}

static void subscribe_error_gestion(client_t **client, \
char team_id[SIZE_ID], command_status_t rfc, server_data **server)
{
    stoc_subscribe_t answer;
    int status = 0;

    if (strlen(team_id) == 0)
        rfc = set_rfc(401, NULL);
    status = subscribe_to_teams(client, team_id, server);
    if (status == 2) {
        rfc = subscribe_set_rfc(503, team_id);
    } else if (status == 1) {
        rfc = subscribe_set_rfc(200, NULL);
    } else {
        rfc = subscribe_set_rfc(200, NULL);
        answer = set_subscribe((*client)->uuid, team_id);
        server_event_user_join_a_team(team_id, (*client)->uuid);
        subscribe_broadcast(answer, team_id, server);
        realloc_buffer(client, RFC_SIZE);
        return subscribe_send_rfc(client, rfc, SUBSCRIBE_SIZE);
    }
    subscribe_send_rfc(client, rfc, 0);
}

void subscribe(client_t *client, server_data **server)
{
    ctos_subscribe_t subscribe;
    command_status_t rfc;

    memset(&subscribe, 0, sizeof(subscribe));
    memcpy(&subscribe, client->readbuffer, sizeof(ctos_subscribe_t));
    if (client->uuid == NULL) {
        rfc = subscribe_set_rfc(500, NULL);
        subscribe_send_rfc(&client, rfc, 0);
    } else {
        subscribe_error_gestion(&client, subscribe.team_uuid, rfc, server);
    }
}
