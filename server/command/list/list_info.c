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
    char *save = get_name(path);
    char *answer = get_all_info(save, path);

    free(save);
    if (answer == NULL)
        return NULL;
    if (file != NULL) {
        while ((read = getline(&line, &useless, file)) != -1)
            answer = list_replies2(answer, path, line);
        fclose(file);
    }
    if (answer != NULL)
        answer[strlen(answer) - 1] = 0;
    free(line);
    free(str);
    return answer;
}

void list_teams(server_data **s, client_t **client)
{
    char *str = NULL;
    char buff[30];

    for (team_t *t = (*s)->team; t; t = t->next) {
        memset(buff, 0, 30);
        sprintf(buff, "%d", t->timestamp);
        my_const_strcat(&str, t->name);
        my_const_strcat(&str, "\t");
        my_const_strcat(&str, t->uuid);
        my_const_strcat(&str, "\t");
        my_const_strcat(&str, buff);
        my_const_strcat(&str, "\t");
        my_const_strcat(&str, t->description);
        my_const_strcat(&str, "\n");
    }
    if (str)
        send_list_success(client, str);
    free(str);
}