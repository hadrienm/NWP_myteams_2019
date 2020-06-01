/*
** EPITECH PROJECT, 2020
** NWP_myteams_2019
** File description:
** subscribed
*/

#include "server.h"

static bool sub_set_teams(client_t **client, \
server_data **server, subscribed_list_t **link_list)
{
    char **list = NULL;

    list = subscribed_create_teams_list(*server, (*client)->uuid);
    if (list == NULL) {
        subscribe_send_rfc(client, subscribed_set_rfc(200, NULL), 0);
        return false;
    }
    subscribed_create_teams_link_list(client, link_list, list);
    return true;
}

static void subscribed_set_success(client_t **cli, char team_id[SIZE_ID], \
server_data **server, size_t index)
{
    char **list = NULL;
    command_status_t rfc = subscribed_set_rfc(200, NULL);
    subscribed_list_t *link_list = NULL;

    if (strlen(team_id) == 0) {
        if (sub_set_teams(cli, server, &link_list) == false)
            return;
    } else {
        list = subscribed_create_users_list(team_id, *server);
        if (list == NULL)
            return subscribe_send_rfc(cli, subscribed_set_rfc(200, NULL), 0);
        subscribed_create_user_link_list(cli, *server, &link_list, list);
    }
    index = send_subscribed_answere(cli, link_list);
    subscribed_send_rfc(cli, rfc, index);
}

void subscribed(client_t *client, server_data **server)
{
    ctos_subscribed_t subscribed;
    command_status_t rfc;

    memset(&subscribed, 0, sizeof(subscribed));
    memcpy(&subscribed, client->readbuffer, sizeof(ctos_subscribed_t));
    if (client->uuid == NULL) {
        rfc = subscribed_set_rfc(500, NULL);
    } else if (check_team(subscribed.team_uuid, *server) == true || \
strlen(subscribed.team_uuid) == 0) {
        return subscribed_set_success(&client, subscribed.team_uuid, \
server, 0);
    } else {
        rfc = subscribed_set_rfc(503, subscribed.team_uuid);
    }
    subscribed_send_rfc(&client, rfc, 0);
}
