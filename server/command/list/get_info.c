/*
** EPITECH PROJECT, 2020
** NWP_myteams_2019
** File description:
** get_info
*/

#include "server.h"

char *get_name(char *str)
{
    char *value = NULL;
    int i = 0;
    int j = 0;

    if (str == NULL)
        return NULL;
    i = strlen(str) - 1;
    for (; i != 0; --i)
        if (str[i] == '/')
            break;
    i += 1;
    for (j = i; str[j] != '\0' && str[j] != '\n'; ++j);
    value = malloc(sizeof(char) * (j - i + 1));
    j = i;
    for (i = 0; str[j] != '\0' && str[j] != '\n'; ++j, ++i)
        value[i] = str[j];
    value[i] = 0;
    return value;
}

int list_teams(client_t ** client, ctos_list_t * list)
{
    char **list_folders = ls_directories("./save/");
    char *str = NULL;
    char *save = NULL;

    for (int i = 0; list_folders[i]; ++i) {
        if (str != NULL) {
            save = strdup(str);
            free(str);
            str = get_name(my_strcat(save, list_folders[i]));
            free(save);
            save = my_strcat(str, "|");
            free(str);
            str = strdup(save);
        } else {
            str = get_name(my_strcat(list_folders[i], "|"));
        }
    }
    free_array(list_folders);
}

char *get_description(char *path)
{
    char *str = my_strcat(path, "/default.txt");
    FILE *file = fopen(str, "r");
    size_t useless = 0;
    char *line = NULL;

    if (file != NULL) {
        int n = getline(&line, &useless, file);
        if (n <= 0 || line == NULL) {
            free(str);
            fclose(file);
            return NULL;
        }
    } else {
        free(str);
        return NULL;
    }
    free(str);
    str = strdup(line);
    fclose(file);
    return str;
}

char *get_all_info(char *name, char *path)
{
    char *str = strdup(name);
    my_const_strcat(&str, "\t");
    my_const_strcat(&str, get_description(path));
    return str;
}