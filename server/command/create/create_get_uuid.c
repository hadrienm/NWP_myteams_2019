/*
** EPITECH PROJECT, 2020
** NWP_myteams_2019
** File description:
** create_get_uuid
*/

#include "server.h"

static char *uuid_array(char **array, char *line)
{
    char *str = NULL;

    array = str_to_word_array(line, "\t");
    if (array == NULL)
        return NULL;
    str = strdup(array[0]);
    free_array(array);
    return str;
}

char *get_uuid_parent_folder(char *path)
{
    FILE *file;
    char *str = my_strcat(path, "/default.txt");
    file = fopen(str, "r");
    char **array = NULL;
    char *line = NULL;
    size_t useless = 0;

    if (file != NULL) {
        int n = getline(&line, &useless, file);
        if (n <= 0 || line == NULL) {
            fclose(file);
            return NULL;
        }
    } else
        return NULL;
    free(str);
    str = uuid_array(array, line);
    free(line);
    fclose(file);
    return str;
}

static char *cut_path(char *path)
{
    int len = 0;
    char *str = NULL;
    int i = 0;

    if (path == NULL)
        return NULL;
    len = strlen(path) - 1;
    if (len <= 0)
        return NULL;
    for (; len != 0 && path[len] != '/'; --len);
    if (len <= 0)
        return NULL;
    str = malloc(sizeof(char) * (len + 1));
    for (; i < len; ++i)
        str[i] = path[i];
    str[i] = 0;
    return str;
}

char *get_uuid_team(char *path)
{
    char *save = NULL;
    char *str = strdup(path);
    char *save2 = NULL;

    while (count_in_str(str, '/') > 2) {
        save = strdup(str);
        free(str);
        save2 = cut_path(save);
        if (save2 == NULL)
            return NULL;
        str = strdup(save2);
        free(save2);
        free(save);
    }
    return str;
}