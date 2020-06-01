/*
** EPITECH PROJECT, 2020
** NWP_myteams_2019
** File description:
** logout
*/

#include "server.h"

void logout(client_t *client, server_data **server)
{
    command_status_t rfc;

    if (client->uuid == NULL) {
        rfc = set_logout_rfc(500);
        set_logout(&client, &(*server)->client);
    } else {
        set_logout(&client, &(*server)->client);
        server_event_user_logged_out(client->uuid);
        client->status = DISCONNECT;
    }
}
