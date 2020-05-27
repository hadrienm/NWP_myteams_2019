/*
** EPITECH PROJECT, 2020
** NWP_myteams_2019
** File description:
** save_messages
*/

#include "server.h"

static char *check_file_is_exist(char *path1, char *path2)
{
    if (access(path1, F_OK) == -1 && access(path2, F_OK) == -1) {
        free(path2);
        return path1;
    } else if (access(path1, F_OK) == -1) {
        free(path1);
        return path2;
    } else {
        free(path2);
        return path1;
    }
}

static char *create_path(ctos_send_t sender, char *user_id)
{
    char *path1 = NULL;
    char *path2 = NULL;
    char *str = NULL;

    my_const_strcat(&path1, "./save/");
    my_const_strcat(&path1, sender.uuid);
    my_const_strcat(&path1, user_id);
    my_const_strcat(&path1, ".txt");
    my_const_strcat(&path2, "./save/");
    my_const_strcat(&path2, user_id);
    my_const_strcat(&path2, sender.uuid);
    my_const_strcat(&path2, ".txt");
    str = check_file_is_exist(path1, path2);
    return str;
}

static char *create_message(char *user_id, char message[DEFAULT_BODY_LENGTH])
{
    char *str = NULL;
    char buf[80] = {0};

    my_const_strcat(&str, user_id);
    my_const_strcat(&str, "\t");
    sprintf(buf, "%d", (int)time(NULL));
    my_const_strcat(&str, buf);
    my_const_strcat(&str, "\t");
    my_const_strcat(&str, message);
    my_const_strcat(&str, "\n");
    return str;
}

void write_message_inside_file(ctos_send_t sender, char *user_id)
{
    char *path = create_path(sender, user_id);
    char *message = create_message(user_id, sender.body);
    FILE * pFile;

    pFile = fopen(path, "a");
    if (pFile != NULL) {
        fputs(message, pFile);
        fclose(pFile);
    }
    free(message);
    free(path);
}
