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
    login.header.size = LOGIN_CONTENT_SIZE;
    sprintf(login.user_id, "%s", (*client)->uuid);
    sprintf(login.name, "%s", (*client)->name);
    index = set_user_send(client, login, all);
    login_send_rfc(client, rfc, index);
    set_login_brodcast(login, all, (*client)->socket);
}

static bool user_exist(client_t **client, char name[DEFAULT_NAME_LENGTH], \
client_list_t **client_list)
{
    for (client_list_t *tmp = (*client_list); tmp != NULL; tmp = tmp->next) {
        if (strcmp(tmp->name, name) == 0) {
            (*client)->uuid = strdup(tmp->uuid);
            (*client)->name = strdup(tmp->name);
            (*client)->status = CONNECT;
            return true;
        }
    }
    return false;
}

static void create_new_client(client_t **cli, char name[DEFAULT_NAME_LENGTH], \
client_list_t **client_list)
{
    char **details = malloc(sizeof(char *) * (3));

    (*cli)->name = strdup(name);
    (*cli)->uuid = make_random_uuid();
    details[0] = strdup((*cli)->uuid);
    details[1] = strdup((*cli)->name);
    details[2] = NULL;
    (*cli)->status= CONNECT;
    add_node_to_client_list(client_list, details);
    server_event_user_created((*cli)->uuid, (*cli)->name);
}

void login(client_t *client, server_data **server)
{
    ctos_login_t login;
    command_status_t rfc;

    memset(&login, 0, sizeof(ctos_login_t));
    memcpy(&login, client->readbuffer, sizeof(ctos_login_t));
    if (strlen(login.name) == 0) {
        rfc = set_login_rfc(401);
        login_send_rfc(&client, rfc, 0);
    }
    if (user_exist(&client, login.name, &(*server)->client_list) == false)
        create_new_client(&client, login.name, &(*server)->client_list);
    server_event_user_logged_in(client->uuid);
    set_login(&client, &(*server)->client);
}
