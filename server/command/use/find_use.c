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

void find_teams(client_t ** client, char *str)
{
    char **list_directories = ls_directories("./save/");
    for (int i = 0; list_directories && list_directories[i]; ++i) {
        char *path = my_strcat(list_directories[i], "/default.txt");
        if (teams_read(path, str)) {
            (*client)->use_path != NULL ? free((*client)->use_path) : 0;
            (*client)->use_path = NULL;
            (*client)->use_path = strdup(list_directories[i]);
            free(path);
            free_array(list_directories);
            return;
        } else
            free(path);
    }
    (*client)->use_path != NULL ? free((*client)->use_path) : 0;
    (*client)->use_path = NULL;
    free_array(list_directories);
}

void find_channel(client_t ** client, char *str)
{
    char *save = NULL;
    char **list_directories = NULL;

    if ((*client)->use_path == NULL)
        return;
    list_directories = ls_directories((*client)->use_path);
    for (int i = 0; list_directories && list_directories[i]; ++i) {
        char *path = my_strcat(list_directories[i], "/default.txt");
        if (teams_read(path, str)) {
            save = strdup((*client)->use_path);
            free((*client)->use_path);
            (*client)->use_path = strdup(list_directories[i]);
            free(save);
            free(path);
            return free_array(list_directories);
        } else
            free(path);
    }
    (*client)->use_path != NULL ? free((*client)->use_path) : 0;
    (*client)->use_path = NULL;
    free_array(list_directories);
}

void find_thread(client_t ** client, char *str)
{
    char *save = NULL;
    char **list_directories = NULL;

    if ((*client)->use_path == NULL)
        return;
    list_directories = ls_directories((*client)->use_path);
    for (int i = 0; list_directories && list_directories[i]; ++i) {
        char *path = my_strcat(list_directories[i], "/default.txt");
        if (teams_read(path, str)) {
            save = strdup((*client)->use_path);
            free((*client)->use_path);
            (*client)->use_path = strdup(list_directories[i]);
            free(save);
            free(path);
            return free_array(list_directories);
        } else
            free(path);
    }
    (*client)->use_path != NULL ? free((*client)->use_path) : 0;
    (*client)->use_path = NULL;
    free_array(list_directories);
}
