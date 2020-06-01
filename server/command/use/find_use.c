/*
** EPITECH PROJECT, 2020
** NWP_myteams_2019
** File description:
** find_use
*/

#include "server.h"

static bool teams_read(char *path, char *uuid)
{
    FILE *file = fopen(path, "r");
    int read = 0;
    size_t useless = 0;
    char *line = NULL;

    if (file != NULL) {
        getline(&line, &useless, file);
        if (strncmp(line, uuid, SIZE_ID - 1) == 0) {
            free(line);
            fclose(file);
            return true;
        }
        fclose(file);
    }
    line != NULL ? free(line) : 0;
    return false;
}

void find_teams(char *uuid, server_data **server, client_t **client)
{
    for (team_t *t = (*server)->team; t; t = t->next) {
        if (strncmp(t->uuid, uuid, SIZE_ID - 1) == 0) {
            (*client)->use_path != NULL ? free((*client)->use_path) : 0;
            (*client)->use_path = strdup(t->path);
            return;
        }
    }
    (*client)->use_path != NULL ? free((*client)->use_path) : 0;
    (*client)->use_path = NULL;
}

void find_channel(char *uuid, server_data **server, client_t **client)
{
    team_t *t = NULL;

    for (t = (*server)->team; t; t = t->next)
        if (strncmp(t->path, (*client)->use_path, strlen(t->path) - 1) == 0)
            break;
    if (t == NULL) {
        (*client)->use_path != NULL ? free((*client)->use_path) : 0;
        (*client)->use_path = NULL;
    }
    for (channel_t *ch = t->channel; ch; ch = ch->next) {
        if (strncmp(ch->uuid, uuid, SIZE_ID - 1) == 0) {
            (*client)->use_path != NULL ? free((*client)->use_path) : 0;
            (*client)->use_path = strdup(ch->path);
            return;
        }
    }
    (*client)->use_path != NULL ? free((*client)->use_path) : 0;
    (*client)->use_path = NULL;
}

void find_thread(char *uuid, server_data **server, client_t **client)
{
    team_t *t;
    channel_t *ch;

    for (t = (*server)->team; t; t = t->next) {
        for (ch = t->channel; ch && strcmp(ch->path, \
(*client)->use_path) != 0; ch = ch->next);
        if (ch && strcmp(ch->path, (*client)->use_path) == 0)
                break;
    }
    if (ch == NULL)
        return free_path(*client);
    for (thread_t *th = ch->thread; th; th = th->next)
        if (strncmp(th->uuid, uuid, SIZE_ID - 1) == 0) {
            free_path(*client);
            (*client)->use_path = strdup(th->path);
            return;
        }
    free_path(*client);
}
