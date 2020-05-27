/*
** EPITECH PROJECT, 2020
** NWP_myteams_2019
** File description:
** suscribe
*/

#include "server.h"

static bool subscribe_add(client_t **client, char *path)
{
    char *str = my_strcat(path, "/default.txt");
    FILE *file = fopen(str, "a");
    int read = 0;
    size_t useless = 0;
    char *line = NULL;

    if (file == NULL) {
        free(str);
        return false;
    }
    fputs((*client)->uuid, file);
    fputs((*client)->name, file);
    fputs("\n", file);
    fclose(file);
    free(str);
    return true;
}

bool subscribe_read(char *path, char *uuid)
{
    char *str = my_strcat(path, "/default.txt");
    FILE *file = fopen(str, "r");
    int read = 0;
    size_t useless = 0;
    char *line = NULL;

    if (file == NULL) {
        free(str);
        return false;
    }
    while ((read = getline(&line, &useless, file)) != -1)
        if (strncmp(line, uuid, SIZE_ID - 1) == 0) {
            fclose(file);
            free(line);
            free(str);
            return true;
        }
    fclose(file);
    free(line);
    free(str);
    return false;
}

static bool subscribe_to_teams(client_t **client, char *uuid, char **folders, \
client_t **all)
{
    for (int i = 0; folders[i]; ++i) {
        if (subscribe_read(folders[i], uuid) == true && \
subscribe_read(folders[i], (*client)->uuid)) {
            return true;
        } else if (subscribe_read(folders[i], uuid) == true) {
            subscribe_add(client, folders[i]);
            return true;
        }
    }
    return false;
}

static void subscribe_error_gestion(client_t **client, \
char team_id[SIZE_ID], command_status_t rfc, client_t **all)
{
    stoc_subscribe_t answer;
    char **list_folders = ls_directories("./save/");

    if (strlen(team_id) == 0) {
        rfc = set_rfc(401, NULL);
    } else if (subscribe_to_teams(client, team_id, \
list_folders, all) == false) {
        rfc = subscribe_set_rfc(503, team_id);
    } else {
        rfc = subscribe_set_rfc(200, NULL);
        answer = set_subscribe((*client)->uuid, team_id);
        server_event_user_join_a_team(team_id, (*client)->uuid);
        free_array(list_folders);
        subscribe_broadcast(answer, team_id, all);
        realloc_buffer(client, rfc_size);
        subscribe_send_rfc(client, rfc, subscribe_size);
        return;
    }
    free_array(list_folders);
    subscribe_send_rfc(client, rfc, 0);
}

void subscribe(client_t *client, client_t **all)
{
    ctos_subscribe_t subscribe;
    command_status_t rfc;

    memset(&subscribe, 0, sizeof(subscribe));
    memcpy(&subscribe, client->readbuffer, sizeof(ctos_subscribe_t));
    if (client->uuid == NULL) {
        rfc = subscribe_set_rfc(500, NULL);
        subscribe_send_rfc(&client, rfc, 0);
    } else {
        subscribe_error_gestion(&client, subscribe.team_uuid, rfc, all);
    }
}
