/*
** EPITECH PROJECT, 2020
** NWP_myteams_2019
** File description:
** ls_utils
*/

#include "server.h"

bool verify_if_folder_exist(char *path)
{
    if (access(path, F_OK) != 0)
        if (ENOENT == errno)
            return false;
    return true;
}

char *read_directory(char *str2)
{
    char *str = NULL;
    char buff[1024] = {0};
    int k = 0;

    FILE *file = popen(str2, "r");
    while (!feof(file) && (fread(buff, 1, 1, file)) > 0) {
        if (k == 0 && strcmp(buff, "\n") == 0) {
            ++k;
            continue;
        }
        if (k == 0)
            continue;
        char *str3 = my_strcat(str, NULL);
        free(str);
        str = my_strcat(str3, buff);
        free(str3);
        memset(&buff, 0, 1024);
    }
    pclose(file);
    return str;
}

char **ls_directories(char *path)
{
    if (!verify_if_folder_exist(path))
        return NULL;
    char buff[1024] = {0};
    char *str = my_strcat("find \"", path);
    char *str2 = my_strcat(str, "\" -maxdepth 1 -type d");
    char **value = NULL;
    free(str);
    str = NULL;
    int k = 0;

    str = read_directory(str2);
    free(str2);
    if (str == NULL)
        return NULL;
    value = str_to_word_array(str, "\n");
    free(str);
    return value;
}

char **ls_files(char *path)
{
    char buff[1024];
    char *str = my_strcat("ls ", path);
    char *str2 = my_strcat(str, " -d */");
    char **value = NULL;
    free(str);

    FILE *file = popen(str2, "r");
    while (!feof(file) && (fread(buff, 1, 1, file)) > 0) {
        char *str3 = my_strcat(str, NULL);
        free(str);
        str = my_strcat(str3, buff);
        free(str3);
    }
    pclose(file);
    free(str2);
    value = str_to_word_array(str, "\n");
    free(str);
    return value;
}

char **list_files(void)
{
    char buff[1024] = {0};
    char *str = NULL;
    char **value = NULL;
    FILE *file = popen("find ./save/ -maxdepth 1 -type f", "r");

    while (!feof(file) && (fread(buff, 1, 1, file)) > 0)
        my_const_strcat(&str, buff);
    pclose(file);
    if (str == NULL)
        return NULL;
    value = str_to_word_array(str, "\n");
    free(str);
    return value;
}
