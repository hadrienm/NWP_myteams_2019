/*
** EPITECH PROJECT, 2020
** NWP_myteams_2019
** File description:
** unsubscribe
*/

#include "server.h"

int determine_length_int(int c)
{
    int len = 1;

    while (c / 10 != 0) {
        c /= 10;
        ++len;
    }
    return len;
}

static void check_status(ctos_unsubscribe_t unsub, client_t **all, \
client_t **client)
{
    int status = 0;
    command_status_t rfc;

    status = found_team(unsub.team_uuid, (*client)->uuid);
    if (status == 2) {
        rfc = unsubscribe_set_rfc(503, unsub.team_uuid);
        unsubscribe_send_rfc(client, rfc, 0);
    } else if (status == 0) {
        set_unsubscribe_success(client, unsub.team_uuid, all);
        server_event_user_leave_a_team(unsub.team_uuid, (*client)->uuid);
    } else {
        rfc = unsubscribe_set_rfc(200, NULL);
        unsubscribe_send_rfc(client, rfc, 0);
    }
}

void unsubscribe(client_t *client, client_t **all)
{
    ctos_unsubscribe_t unsubscribe;
    command_status_t rfc;

    memset(&unsubscribe, 0, sizeof(ctos_login_t));
    memcpy(&unsubscribe, client->readbuffer, sizeof(ctos_unsubscribe_t));
    if (client->uuid == NULL)
        rfc = unsubscribe_set_rfc(500, NULL);
    else if (strlen(unsubscribe.team_uuid) == 0)
        rfc = unsubscribe_set_rfc(401, NULL);
    else
        return check_status(unsubscribe, all, &client);
    unsubscribe_send_rfc(&client, rfc, 0);
}
