/*
** EPITECH PROJECT, 2020
** NWP_myteams_2019
** File description:
** user
*/

#include "server.h"

static int check_user_is_log(char *user_id, client_t *all)
{
    for (client_t *tmp = all; tmp != NULL; tmp = tmp->next) {
        if (strncmp(tmp->uuid, user_id, SIZE_ID - 1) == 0)
            return 1;
    }
    return 0;
}

static stoc_user_t user_create_answer(client_list_t *tmp, client_t *all)
{
    int is_log = check_user_is_log(tmp->uuid, all);
    stoc_user_t user;

    memset(&user, 0, sizeof(user));
    memset(user.id, 0, SIZE_ID);
    memset(user.name, 0, DEFAULT_NAME_LENGTH);
    user.header.name = USER;
    user.header.size = USER_CONTENT_SIZE;
    sprintf(user.id, "%s", tmp->uuid);
    sprintf(user.name, "%s", tmp->name);
    user.status = is_log;
    return user;
}

static bool get_user(char *uuid, client_t **client, server_data **server)
{
    stoc_user_t answer;
    command_status_t rfc;

    for (client_list_t *tmp = (*server)->client_list; tmp != NULL; \
tmp = tmp->next) {
        if (strcmp(tmp->uuid, uuid) == 0) {
            rfc = set_rfc(200, uuid);
            answer = user_create_answer(tmp, (*server)->client);
            user_send_success(answer, rfc, client);
            return true;
        }
    }
    return false;
}

void user(client_t *client, server_data **server)
{
    ctos_user_t user;
    command_status_t rfc;

    memset(&user, 0, sizeof(user));
    memcpy(&user, client->readbuffer, sizeof(ctos_user_t));
    if (client->uuid == NULL) {
        rfc = set_rfc(500, user.uuid);
    } else if (strlen(user.uuid) == 0) {
        rfc = set_rfc(401, user.uuid);
    } else {
        if (get_user(user.uuid, &client, server) == true) {
            return;
        } else
            rfc = set_rfc(502, user.uuid);
    }
    user_send_rfc(&client, rfc, 0);
}
