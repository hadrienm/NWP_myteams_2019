/*
** EPITECH PROJECT, 2020
** NWP_myteams_2019
** File description:
** create
*/

#include "server.h"

int write_create_in_file(char *str, ctos_create_t create, char temp[10])
{
    FILE * pFile;
    char *str2 = my_strcat(str, "/default.txt");
    pFile = fopen(str2, "a");
    if (pFile != NULL) {
        fputs(create.uuid, pFile);
        fputs("\t", pFile);
        fputs(temp, pFile);
        fputs("\t", pFile);
        fputs(create.message, pFile);
        fputs("\n", pFile);
        fclose(pFile);
    } else {
        free(str2);
        return 0;
    }
    free(str2);
    return 1;
}

int write_timestamp(char *str, char temp[10], \
ctos_create_t create, client_t **client)
{
    FILE * pFile;
    char *str2 = my_strcat(str, "/default.txt");

    pFile = fopen(str2, "a");
    if (pFile != NULL) {
        fputs(create.uuid, pFile);
        fputs("\t", pFile);
        fputs(temp, pFile);
        fputs("\t", pFile);
        fputs(create.message, pFile);
        fputs("\t", pFile);
        fputs((*client)->uuid, pFile);
        fputs("\n", pFile);
        fclose(pFile);
    } else {
        free(str2);
        return 0;
    }
    free(str2);
    return 1;
}

void create_switch_two(int n, client_t *client, server_data **server, \
ctos_create_t create)
{
    char *new_uuid = make_random_uuid();
    int k = 0;

    if (n == 2) {
        k = add_channel(&client, create, server, new_uuid);
        if (k == 2)
            send_rfc(&client, set_create_rfc(506), 0);
        else if (k == 0)
            send_rfc(&client, set_create_rfc(401), 0);
    } else if (n == 3) {
        k = add_thread(&client, create, server, new_uuid);
        if (k == 2)
            send_rfc(&client, set_create_rfc(506), 0);
        else if (k == 0)
            send_rfc(&client, set_create_rfc(401), 0);
    } else {
        add_message(&client, create, server, new_uuid);
    }
    free(new_uuid);
}

void create_switch(client_t *client, ctos_create_t create, \
server_data **server, int n)
{
    char *new_uuid = make_random_uuid();
    int k = 0;

    switch (n) {
    case 0:
        k = add_teams(&client, create, server, new_uuid);
        if (k == 2)
            send_rfc(&client, set_create_rfc(506), 0);
        else if (k == 0)
            send_rfc(&client, set_create_rfc(401), 0);
        break;
    default:
        create_switch_two(n, client, server, create);
    }
    free(new_uuid);
}

void create(client_t *client, server_data **server)
{
    ctos_create_t create;

    if (client->name == NULL)
        return send_rfc(&client, set_create_rfc(500), 0);
    memset(&create, 0, sizeof(create));
    memcpy(&create, client->readbuffer, sizeof(ctos_create_t));
    int n = count_in_str(client->use_path, '/');
    if (n > 4 || n < 0)
        return;
    create_switch(client, create, server, n);
}
