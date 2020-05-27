/*
** EPITECH PROJECT, 2020
** NWP_myteams_2019
** File description:
** create_list
*/

#include "server.h"

static char *get_team_info(char *path)
{
    char *str = my_strcat(path, "/default.txt");
    FILE *file = fopen(str, "r");
    size_t useless = 0;
    char *line = NULL;

    if (file == NULL) {
        free(str);
        return NULL;
    }
    getline(&line, &useless, file);
    fclose(file);
    free(str);
    return line;
}

char **subscribed_create_teams_list(char **folders, char *uuid)
{
    char *tmp = NULL;
    char *info = NULL;
    char **list = NULL;

    if (!folders)
        return NULL;
    for (int i = 0; folders && folders[i]; ++i) {
        if (subscribe_read(folders[i], uuid) == true) {
            info = get_team_info(folders[i]);
            my_const_strcat(&tmp, info);
        }
    }
    if (tmp == NULL)
        return NULL;
    list = str_to_word_array(tmp, "\n");
    free(info);
    free(tmp);
    return list;
}

bool check_team(char team_id[SIZE_ID])
{
    char **list_folders = ls_directories("./save/");
    char *tmp = NULL;

    for (int i = 0; list_folders && list_folders[i] != NULL; ++i) {
        tmp = get_team_info(list_folders[i]);
        if (strncmp(team_id, tmp, SIZE_ID - 1) == 0) {
            free(tmp);
            free_array(list_folders);
            return true;
        }
    }
    free(tmp);
    free(list_folders);
    return false;
}

char **subscribed_create_users_list(char team_id[SIZE_ID])
{
    char *path = found_path_team(team_id);
    FILE *file = fopen(path, "r");
    size_t useless = 0;
    char *line = NULL;
    char *tmp = NULL;
    char **list = NULL;

    if (file == NULL) {
        free(path);
        return NULL;
    }
    for (size_t i = 0; getline(&line, &useless, file) != -1; ++i)
        i > 0 ? my_const_strcat(&tmp, line) : 0;
    fclose(file);
    if (tmp != NULL)
        list = str_to_word_array(tmp, "\n");
    free(path);
    free(tmp);
    return list;
}