/*
** EPITECH PROJECT, 2020
** NWP_myteams_2019
** File description:
** login_check_user
*/

#include "server.h"

bool add_user(client_t *client)
{
    FILE * file;
    file = fopen("./save/client.txt", "a");
    if (file != NULL) {
        fputs(client->uuid, file);
        fputs(client->name, file);
        fputs("\n", file);
        fclose(file);
        return true;
    }
    return false;
}

static void set_login_client(client_t **client, char *line, \
ctos_login_t receive)
{
    (*client)->uuid = malloc(sizeof(char) * SIZE_ID);
    (*client)->name = malloc(sizeof(char) * strlen(receive.name) + 1);
    memset((*client)->uuid, 0, SIZE_ID);
    memset((*client)->name, 0, strlen(receive.name) + 1);
    for (int i = 0, index = 0; line[i] != '\n'; ++i) {
        if (i < SIZE_ID - 1)
            (*client)->uuid[i] = line[i];
        else {
            (*client)->name[index] = line[i];
            ++index;
        }
    }
}

static bool handle_line(client_t **client, char *line, ctos_login_t receive)
{
    char *tmp = alloca(sizeof(char) * (strlen(receive.name) + 1));

    memset(tmp, 0, strlen(receive.name) + 1);
    if (strlen(line) < SIZE_ID)
        return false;
    for (size_t i = 0, j = 0; line[i] != '\n'; ++i) {
        if (j >= strlen(receive.name))
            break;
        if (i >= SIZE_ID - 1) {
            tmp[j] = line[i];
            ++j;
        }
    }
    if (strcmp(tmp, receive.name) == 0) {
        set_login_client(client, line, receive);
        return true;
    }
    return false;
}

bool check_is_user_already_exist(client_t **client, ctos_login_t receive)
{
    FILE *file = fopen("./save/client.txt", "r");
    size_t useless = 0;
    char *line = NULL;

    if (file == NULL)
        return false;
    while (getline(&line, &useless, file) != -1) {
        if (handle_line(client, line, receive) == true) {
            server_event_user_logged_in((*client)->uuid);
            line != NULL ? free(line) : 0;
            fclose(file);
            return true;
        }
    }
    line != NULL ? free(line) : 0;
    fclose(file);
    return false;
}
