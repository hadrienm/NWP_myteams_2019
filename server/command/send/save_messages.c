/*
** EPITECH PROJECT, 2020
** NWP_myteams_2019
** File description:
** save_messages
*/

#include "server.h"

void save_message(ctos_send_t sender, char *uuid, corresponding_t **cpr_list)
{
    char **uuids = malloc(sizeof(char *) * (3));
    char **details = malloc(sizeof(char *) * (4));

    uuids[0] = strdup(uuid);
    uuids[1] = strdup(sender.uuid);
    uuids[2] = NULL;
    details[0] = strdup(uuid);
    details[1] = malloc(sizeof(char) * (30));
    sprintf(details[1], "%d", (int)time(NULL));
    details[2] = strdup(sender.body);
    details[3] = NULL;
    add_corresponding(cpr_list, uuids, details);
    free_array(uuids);
}
