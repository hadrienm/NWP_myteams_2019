/*
** EPITECH PROJECT, 2020
** NWP_myteams_2019
** File description:
** list_info
*/

#include "server.h"

static char *list_replies2(char *answer, char *path, char *line)
{
    char *save = NULL;
    char *save2 = NULL;
    char *save3 = NULL;

    save = strdup(answer);
    free(answer);
    save3 = get_name(path);
    save2 = my_strcat(save, save3);
    free(save3);
    save3 = my_strcat(save2, "\t");
    free(save);
    answer = my_strcat(save3, line);
    free(save2);
    free(save3);
    return answer;
}

char *list_replies(char *path)
{
    char *str = my_strcat(path, "/conversation.txt");
    FILE *file = fopen(str, "r");
    int read = 0;
    size_t useless = 0;
    char *line = NULL;
    char *save = NULL;
    char *answer = get_all_info(get_name(path), path);
    char *save2 = NULL;

    if (answer == NULL)
        return NULL;
    if (file != NULL) {
        while ((read = getline(&line, &useless, file)) != -1)
            answer = list_replies2(answer, path, line);
        fclose(file);
    }
    if (answer != NULL)
        answer[strlen(answer) - 1] = 0;
    return answer;
}

static char *list_all_folders2(char *list, char *answer, char *list_folder)
{
    char *save = strdup(answer);
    char *save2 = NULL;
    char *info = NULL;

    free(answer);
    info = get_all_info(list, list_folder);
    save2 = my_strcat(save, info);
    answer = my_strcat(save2, "\n");
    free(save);
    free(info);
    free(save2);
    return answer;
}

char *list_all_folders(char *path)
{
    char **list_folder = ls_directories(path);
    char *answer = NULL;
    char *save = NULL;

    if (list_folder == NULL)
        return NULL;
    for (int i = 0; list_folder[i]; ++i) {
        char *list = get_name(list_folder[i]);
        if (answer == NULL) {
            answer = get_all_info(list, list_folder[i]);
            my_const_strcat(&answer, "\n");
        } else
            answer = list_all_folders2(list, answer, list_folder[i]);
        free(list);
    }
    free_array(list_folder);
    return answer;
}