/*
** EPITECH PROJECT, 2020
** NWP_myteams_2019
** File description:
** users
*/

#include "server.h"

char *separate_line(char *line)
{
    char *str = malloc(sizeof(char) * (strlen(line) + 2));
    int i = 0;
    int j = 0;

    for (; line[i] && i < SIZE_ID - 1; ++i)
        str[i] = line[i];
    str[i] = ' ';
    for (j = i + 1; line[i] && line[i] != '\n'; ++i, ++j)
        str[j] = line[i];
    str[j] = 0;
    return str;
}

void users(client_t *client, client_t **all)
{
    ctos_users_t users;
    command_status_t rfc;

    memset(&users, 0, sizeof(users));
    memcpy(&users, client->readbuffer, sizeof(ctos_users_t));
    if (client->name == NULL) {
        rfc = users_set_rfc(500);
        users_send_rfc(&client, rfc, 0);
    } else {
        send_succes_list(&client, all);
    }
}
