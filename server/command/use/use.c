/*
** EPITECH PROJECT, 2020
** NWP_myteams_2019
** File description:
** use
*/

#include "server.h"

static command_status_t use_set_rfc(int status, char id[SIZE_ID])
{
    command_status_t rfc;

    memset(&rfc, 0, rfc_size);
    memset(rfc.id, 0, SIZE_ID);
    memset(rfc.rfc_message, 0, RFC_MESSAGE_LENGTH);
    rfc.header.name = RFC;
    rfc.header.size = rfc_content_size;
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

void use_two(ctos_use_t use, client_t *client)
{
    if (strlen(use.channel_uuid) != 0) {
        find_channel(&client, use.channel_uuid);
        if (client->use_path == NULL)
            return send_rfc(&client, use_set_rfc(504, use.channel_uuid), 0);
        else if (strlen(use.thread_uuid) == 0)
            send_rfc(&client, use_set_rfc(200, NULL), 0);
    }
    if (strlen(use.thread_uuid) != 0) {
        find_thread(&client, use.thread_uuid);
        if (client->use_path == NULL)
            return send_rfc(&client, use_set_rfc(505, use.thread_uuid), 0);
        else
            send_rfc(&client, use_set_rfc(200, NULL), 0);
    }
}

void use(client_t *client, client_t **all)
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
    find_teams(&client, use.team_uuid);
    if (client->use_path == NULL)
        return send_rfc(&client, use_set_rfc(503, use.team_uuid), 0);
    else if (!subscribe_read(client->use_path, client->uuid)) {
        free(client->use_path);
        client->use_path = NULL;
        return;
    } else if (strlen(use.channel_uuid) == 0)
        send_rfc(&client, use_set_rfc(200, NULL), 0);
    use_two(use, client);
}
