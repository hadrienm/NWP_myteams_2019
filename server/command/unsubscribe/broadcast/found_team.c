/*
** EPITECH PROJECT, 2020
** NWP_myteams_2019
** File description:
** found_team
*/

#include "server.h"

static bool handle_file(FILE * file, char team_id[SIZE_ID])
{
    char *line = NULL;
    size_t useless = 0;

    if (file != NULL) {
        getline(&line, &useless, file);
        if (strncmp(line, team_id, SIZE_ID - 1) == 0) {
            free(line);
            fclose(file);
            return true;
        }
        return false;
    }
    line != NULL ? free(line) : 0;
}

char *found_path_team(char team_id[SIZE_ID])
{
    char **folder_list = ls_directories("./save/");
    char *tmp = NULL;
    FILE * file;

    for (int i = 0; folder_list && folder_list[i] != NULL; ++i) {
        my_const_strcat(&tmp, folder_list[i]);
        my_const_strcat(&tmp, "/default.txt");
        file = fopen(tmp, "r");
        if (handle_file(file, team_id) == true)
            return tmp;
        free(tmp);
        tmp = NULL;
    }
    free_array(folder_list);
}

static char **delete_user(char **array, int i)
{
    char **save = NULL;
    int n = 0;
    int k = 0;

    if (array == NULL)
        return NULL;
    save = malloc(sizeof(char *) * (size_array(array)));
    for (; array[n]; ++n) {
        if (n == i)
            continue;
        save[k] = strdup(array[n]);
        ++k;
    }
    save[k] = NULL;
    return save;
}

static int is_subscribe(char *user_id, team_t *t)
{
    char **save;

    for (int i = 0; t->user_subscribe && t->user_subscribe[i]; ++i) {
        if (strncmp(t->user_subscribe[i], user_id, SIZE_ID - 1) == 0) {
            save = delete_user(t->user_subscribe, i);
            free_array(t->user_subscribe);
            t->user_subscribe = copy_array(save);
            free_array(save);
            return 0;
        }
    }
    return 1;
}

int found_team(char team_id[SIZE_ID], char *user_id, server_data **server)
{
    for (team_t *t = (*server)->team; t; t = t->next) {
        if (strncmp(team_id, t->uuid, SIZE_ID - 1) != 0)
            continue;
        return is_subscribe(user_id, t);
    }
    return 2;
}
