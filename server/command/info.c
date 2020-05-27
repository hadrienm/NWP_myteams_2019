/*
** EPITECH PROJECT, 2020
** NWP_myteams_2019
** File description:
** info
*/

#include "server.h"

char *get_info_user(char *uuid)
{
    FILE *file = fopen("./save/client.txt", "r");
    size_t useless = 0;
    char *line = NULL;
    char *str = NULL;

    if (file == NULL)
        return NULL;
    while (getline(&line, &useless, file) != -1) {
        if (line == NULL)
            break;
        if (strlen(line) > SIZE_ID - 1 && \
strncmp(line, uuid, SIZE_ID - 1) == 0) {
            str = separate_line(line);
        }
    }
    line != NULL ? free(line) : 0;
    fclose(file);
    return str;
}

static void info_error(client_t **client)
{
    command_status_t status;
    int size = sizeof(int) + sizeof(size_t) + RFC_MESSAGE_LENGTH + SIZE_ID;
    size_t index = 0;

    memset(&status, 0, sizeof(status));
    status.header.name = RFC;
    status.header.size = RFC_MESSAGE_LENGTH + SIZE_ID;
    sprintf(status.rfc_message, "%s", rfc_message[CODE_500]);
    memset(status.id, 0, SIZE_ID);
    (*client)->answer = malloc(size);
    memset((*client)->answer, 0, size);
    memcpy((*client)->answer, &status.header.name, sizeof(int));
    index += sizeof(int);
    memcpy((*client)->answer + index, &status.header.size, sizeof(size_t));
    index += sizeof(size_t);
    memcpy((*client)->answer + index, &status.rfc_message, RFC_MESSAGE_LENGTH);
    index += RFC_MESSAGE_LENGTH;
    memcpy((*client)->answer + index, &status.id, SIZE_ID);
}

static char *get_info_folder(char *path)
{
    char *str = my_strcat(path, "/default.txt");
    FILE *file = fopen(str, "r");
    int read = 0;
    size_t useless = 0;
    char *line = NULL;
    int i = 0;
    char *answer = NULL;

    if (file != NULL) {
        read = getline(&line, &useless, file);
        if (line == NULL) {
            fclose(file);
            return NULL;
        }
        answer = strdup(line);
        answer[strlen(answer) - 1] = 0;
        fclose(file);
    }
    return answer;
}

void info(client_t *client, client_t **client_list)
{
    if (client->name == NULL)
        return info_error(&client);
    ctos_info_t info;
    char *str = NULL;

    memset(&info, 0, sizeof(ctos_info_t));
    memcpy(&info, client->readbuffer, sizeof(ctos_info_t));
    if (client->use_path == NULL)
        str = get_info_user(client->uuid);
    else
        str = get_info_folder(client->use_path);
    free(str);
}