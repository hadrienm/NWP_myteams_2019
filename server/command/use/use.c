/*
** EPITECH PROJECT, 2020
** NWP_myteams_2019
** File description:
** use
*/

#include "server.h"

void free_path(client_t *client)
{
    client->use_path != NULL ? free(client->use_path) : 0;
    client->use_path = NULL;
}

static command_status_t use_set_rfc(int status, char id[SIZE_ID])
{
    command_status_t rfc;

    memset(&rfc, 0, RFC_SIZE);
    memset(rfc.id, 0, SIZE_ID);
    memset(rfc.rfc_message, 0, RFC_MESSAGE_LENGTH);
    rfc.header.name = RFC;
    rfc.header.size = RFC_CONTENT_SIZE;
    if (status == 500)
        sprintf(rfc.rfc_message, "%s", rfc_message[CODE_500]);
    else if (status == 200)
        sprintf(rfc.rfc_message, "%s", rfc_message[CODE_200]);
    else {
        sprintf(rfc.id, "%s", id);
        if (status == 503)
            sprintf(rfc.rfc_message, "%s", rfc_message[CODE_503]);
        else if (status == 504)
            sprintf(rfc.rfc_message, "%s", rfc_message[CODE_504]);
        else
            sprintf(rfc.rfc_message, "%s", rfc_message[CODE_505]);
    }
    return rfc;
}

static command_status_t use_set_rfc_ns(void)
{
    command_status_t rfc;

    memset(&rfc, 0, RFC_SIZE);
    memset(rfc.id, 0, SIZE_ID);
    memset(rfc.rfc_message, 0, RFC_MESSAGE_LENGTH);
    rfc.header.name = RFC;
    rfc.header.size = RFC_CONTENT_SIZE;
    sprintf(rfc.rfc_message, "%s", rfc_message[CODE_501]);
    return rfc;
}

void use_two(ctos_use_t use, client_t *client, server_data **server)
{
    if (strlen(use.channel_uuid) != 0) {
        find_channel(use.channel_uuid, server, &client);
        if (client->use_path == NULL) {
            return send_rfc(&client, use_set_rfc(504, use.channel_uuid), 0);
        } else if (strlen(use.thread_uuid) == 0) {
            send_rfc(&client, use_set_rfc(200, NULL), 0);
        }
    }
    if (strlen(use.thread_uuid) != 0) {
        find_thread(use.thread_uuid, server, &client);
        if (client->use_path == NULL) {
            return send_rfc(&client, use_set_rfc(505, use.thread_uuid), 0);
        } else {
            send_rfc(&client, use_set_rfc(200, NULL), 0);
        }
    }
}

void use(client_t *client, server_data **server)
{
    ctos_use_t use;

    if (client->name == NULL)
        return send_rfc(&client, use_set_rfc(500, NULL), 0);
    memset(&use, 0, sizeof(ctos_use_t));
    memcpy(&use, client->readbuffer, sizeof(ctos_use_t));
    if (strlen(use.team_uuid) == 0) {
        client->use_path != NULL ? free(client->use_path) : 0;
        client->use_path = NULL;
        return send_rfc(&client, use_set_rfc(200, NULL), 0);
    }
    find_teams(use.team_uuid, server, &client);
    if (client->use_path == NULL) {
        return send_rfc(&client, use_set_rfc(503, use.team_uuid), 0);
    } else if (!subscribe_read((*server)->team, client->uuid, use.team_uuid)) {
        send_rfc(&client, use_set_rfc_ns(), 0);
        return free_path(client);
    } else
        if (strlen(use.channel_uuid) == 0)
            return send_rfc(&client, use_set_rfc(200, NULL), 0);
    use_two(use, client, server);
}
