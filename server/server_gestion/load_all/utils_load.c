/*
** EPITECH PROJECT, 2020
** Visual Studio Live Share (Workspace)
** File description:
** utils_load
*/

#include "server.h"

char **copy_array(char **array)
{
    char **new_array;
    int i = 0;

    if (array == NULL)
        return NULL;
    new_array = malloc(sizeof(char *) * (size_array(array) + 1));
    for (i = 0; array[i]; ++i)
        new_array[i] = strdup(array[i]);
    new_array[i] = NULL;
    return new_array;
}

char **read_after_line1(char *path, char *path2)
{
    char *str = my_strcat(path, path2);
    FILE *file = fopen(str, "r");
    size_t useless = 0;
    char *line = NULL;
    char **list = NULL;
    free(str);
    str = NULL;

    if (file == NULL)
        return NULL;
    for (size_t i = 0; getline(&line, &useless, file) != -1; ++i) {
        i > 0 ? my_const_strcat(&str, line) : 0;
    }
    fclose(file);
    if (str != NULL)
        list = str_to_word_array(str, "\n");
    free(str);
    free(line);
    return list;
}
