/*
** EPITECH PROJECT, 2020
** NWP_myteams_2019
** File description:
** send
*/

#include "server.h"

static bool found_user(char uuid[SIZE_ID], client_t *all)
{
    for (client_t *tmp = all; tmp != NULL; tmp = tmp->next)
        if (strcmp(uuid, tmp->uuid) == 0)
            return true;
    return false;
}

void send_c(client_t *client, client_t **all)
{
    ctos_send_t sender;
    command_status_t rfc;

    memset(&sender, 0, sizeof(ctos_login_t));
    memcpy(&sender, client->readbuffer, sizeof(ctos_send_t));
    if (client->uuid == NULL) {
        rfc = set_send_rfc(500, NULL);
    } else if (strlen(sender.body) == 0 || strlen(sender.uuid) == 0) {
        rfc = set_send_rfc(401, NULL);
    } else if (found_user(sender.uuid, *all) == false) {
        rfc = set_send_rfc(502, sender.uuid);
    } else {
        set_send_s(&client, sender, all);
        write_message_inside_file(sender, client->uuid);
        server_event_private_message_sended(client->uuid, sender.uuid, \
sender.body);
        return;
    }
    send_rfc(&client, rfc, 0);
}
