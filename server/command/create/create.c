/*
** EPITECH PROJECT, 2020
** NWP_myteams_2019
** File description:
** create
*/

#include "server.h"

bool verify_name(char *str)
{
    if (!str)
        return false;
    for (int i = 0; str[i]; ++i)
        if (str[i] == '/')
            return false;
    return true;
}

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

void create_switch(client_t *client, ctos_create_t create, \
client_t **all, int n)
{
    char *new_uuid = make_random_uuid();

    switch (n) {
    case 0:
        if (add_teams(&client, create, all, new_uuid) == 2)
            return send_rfc(&client, set_create_rfc(506), 0);
        break;
    case 2:
        if (add_channel(&client, create, all, new_uuid) == 2)
            return send_rfc(&client, set_create_rfc(506), 0);
        break;
    case 3:
        if (add_thread(&client, create, all, new_uuid) == 2)
            return send_rfc(&client, set_create_rfc(506), 0);
        break;
    case 4:
        add_message(&client, create, all);
        break;
    }
    free(new_uuid);
}

void create(client_t *client, client_t **all)
{
    ctos_create_t create;

    if (client->name == NULL)
        return send_rfc(&client, set_create_rfc(500), 0);
    memset(&create, 0, sizeof(create));
    memcpy(&create, client->readbuffer, sizeof(ctos_create_t));
    int n = count_in_str(client->use_path, '/');
    if (n > 4 || n < 0)
        return;
    create_switch(client, create, all, n);
}
