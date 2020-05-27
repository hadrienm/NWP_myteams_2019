/*
** EPITECH PROJECT, 2020
** NWP_myteams_2019
** File description:
** get_messages
*/

#include "server.h"

static char *check_file_is_exist(char *path1, char *path2)
{
    if (access(path1, F_OK) == -1 && access(path2, F_OK) == -1) {
        return NULL;
    } else if (access(path1, F_OK) == -1) {
        free(path1);
        return path2;
    } else {
        free(path2);
        return path1;
    }
}

char *message_create_path(char id[SIZE_ID], char *user_id)
{
    char *path1 = NULL;
    char *path2 = NULL;
    char *str = NULL;

    my_const_strcat(&path1, "./save/");
    my_const_strcat(&path1, id);
    my_const_strcat(&path1, user_id);
    my_const_strcat(&path1, ".txt");
    my_const_strcat(&path2, "./save/");
    my_const_strcat(&path2, user_id);
    my_const_strcat(&path2, id);
    my_const_strcat(&path2, ".txt");
    str = check_file_is_exist(path1, path2);
    return str;
}

char *list_conversation(char *path)
{
    FILE *file = fopen(path, "r");
    char *line = NULL;
    char *answer = NULL;
    size_t useless = 0;
    int read = 0;

    if (file != NULL) {
        while ((read = getline(&line, &useless, file)) != -1) {
            strlen(line) >= SIZE_ID - 1 ? my_const_strcat(&answer, line) : 0;
        }
        fclose(file);
    }
    line != NULL ? free(line) : 0;
    return answer;
}

size_t size_of_list(messages_list_t *list)
{
    size_t size = 0;

    messages_list_t *tmp = list;
    while (tmp != NULL) {
        tmp = tmp->next;
        ++size;
    }
    return size;
}
