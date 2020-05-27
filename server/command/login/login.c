/*
** EPITECH PROJECT, 2020
** NWP_myteams_2019
** File description:
** login
*/

#include "server.h"

static void set_login(client_t **client, client_t **all)
{
    stoc_login_t login;
    command_status_t rfc = set_login_rfc(200);
    size_t index = 0;

    memset(&login, 0, sizeof(login));
    login.header.name = LOGIN;
    login.header.size = login_content_size;
    sprintf(login.user_id, "%s", (*client)->uuid);
    sprintf(login.name, "%s", (*client)->name);
    index = set_user_send(client, login, all);
    login_send_rfc(client, rfc, index);
    set_login_brodcast(login, all, (*client)->socket);
}

void login(client_t *client, client_t **all)
{
    ctos_login_t login;
    command_status_t rfc;

    memset(&login, 0, sizeof(ctos_login_t));
    memcpy(&login, client->readbuffer, sizeof(ctos_login_t));
    if (strlen(login.name) != 0) {
        if (check_is_user_already_exist(&client, login) == false) {
            client->name = strdup(login.name);
            client->uuid = make_random_uuid();
            add_user(client);
            server_event_user_created(client->uuid, client->name);
            server_event_user_logged_in(client->uuid);
        }
        client->status = CONNECT;
        set_login(&client, all);
    } else {
        rfc = set_login_rfc(401);
        login_send_rfc(&client, rfc, 0);
    }
}
