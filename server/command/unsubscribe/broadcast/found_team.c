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

static bool delete_user(FILE *file, char *user_id, char *path)
{
    char *line = NULL;
    char *command = NULL;
    char *number = NULL;
    size_t useless = 0;

    for (int index = 2; getline(&line, &useless, file) != -1; ++index) {
        if (strncmp(line, user_id, strlen(user_id) - 1) == 0) {
            number = malloc(sizeof(char) * (determine_length_int(index) + 1));
            memset(number, 0, determine_length_int(index) + 1);
            my_const_strcat(&command, "sed -i '");
            sprintf(number, "%d", index);
            my_const_strcat(&command, number);
            my_const_strcat(&command, "d' ");
            my_const_strcat(&command, path);
            FILE *file2 = popen(command, "w");
            pclose(file2);
            free(number);
            return true;
        }
    }
    return false;
}

static int hande_line(char team_id[SIZE_ID], char *user_id, char *tmp, \
FILE *file)
{
    char *line = NULL;
    size_t useless = 0;

    getline(&line, &useless, file);
    if (strncmp(line, team_id, SIZE_ID - 1) == 0) {
        if (delete_user(file, user_id, tmp) == true) {
            fclose(file);
            return 0;
        }
        fclose(file);
        return 1;
    }
    return 2;
}

int found_team(char team_id[SIZE_ID], char *user_id)
{
    char **folder_list = ls_directories("./save/");
    char *tmp = NULL;
    FILE * file;
    int status = 0;

    for (int i = 0; folder_list && folder_list[i] != NULL; ++i) {
        my_const_strcat(&tmp, folder_list[i]);
        my_const_strcat(&tmp, "/default.txt");
        file = fopen(tmp, "r");
        if (file == NULL)
            return false;
        status = hande_line(team_id, user_id, tmp, file);
        if (status == 1 || status == 0)
            return status;
    }
    free_array(folder_list);
    free(tmp);
    return 2;
}
