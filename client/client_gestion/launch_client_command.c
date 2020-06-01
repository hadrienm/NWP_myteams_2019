/*
** EPITECH PROJECT, 2020
** NWP_myteams_2019
** File description:
** launch_client_command
*/

#include "client.h"

static int new_command_len(int len, size_t index, char *buffer, char **str)
{
    char *answer = NULL;

    if (len == 0)
        return -1;
    answer = malloc(sizeof(char) * (len + 2));
    for (len = index; buffer[len]; ++len) {
        if (buffer[len] == '\n')
            break;
        answer[len - index] = buffer[len];
    }
    answer[len - index] = 0;
    *str = strdup(answer);
    free(answer);
    return len + 1;
}

static int get_new_command(char **str, char *buffer, int index)
{
    free(*str);
    *str = NULL;
    char *answer = NULL;
    int len = 0;
    int mangetesmorts = 0;

    if (buffer == NULL)
        return -1;
    for (int i = 0; buffer[i]; ++i)
        if (buffer[i] == '\n')
            mangetesmorts = 1;
    if (mangetesmorts == 0)
        return -1;
    if (index >= (int)strlen(buffer))
        return -1;
    for (int i = index; buffer[i]; ++i, ++len)
        if (buffer[i] == '\n')
            break;
    return new_command_len(len, index, buffer, str);
}

static void command_is_right(client_data **client, int i)
{
    for (int j = 0; command_name[j]; ++j) {
        if (strcasecmp(command_name[j], (*client)->command[0]) == 0) {
            command[j](client);
            (*client)->buffer = my_cut((*client)->buffer, i);
            break;
        }
    }
}

static void error_case(client_data **client, int i)
{
    if ((*client)->command != NULL) {
        free_command(client);
        (*client)->buffer = my_cut((*client)->buffer, i);
        printf("Command unknown.\r\n");
    }
}

void execute_command(client_data **client)
{
    int i = 0;
    char *str = NULL;

    while (i != -1) {
        i = 0;
        i = get_new_command(&str, (*client)->buffer, i);
        if (i == -1 || str == NULL) {
            (*client)->pending_command = my_strdup((*client)->buffer);
            (*client)->buffer != NULL ? free((*client)->buffer) : 0;
            (*client)->buffer = NULL;
            break;
        }
        (*client)->command = get_client_command(str);
        if ((*client)->command == NULL) {
            free((*client)->buffer);
            (*client)->buffer = NULL;
            return error("Command unknown.\r");
        }
        command_is_right(client, i);
        error_case(client, i);
    }
}
