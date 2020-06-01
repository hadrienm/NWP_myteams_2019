/*
** EPITECH PROJECT, 2020
** NWP_myteams_2019
** File description:
** help
*/

#include "server.h"

static void help_get_argument(char arg[DEFAULT_BODY_LENGTH], char **answer)
{
    int j = 0;

    for (; command_name[j] != NULL; ++j) {
        if (strcasecmp(arg, command_name[j] + 1) == 0)
            break;
    }
    if (j < 14)
        my_const_strcat(&(*answer), command_description[j]);
}

static void set_help(client_t **client, bool status, \
char answer[DEFAULT_BODY_LENGTH])
{
    stoc_help_t help;
    size_t index = 0;
    command_status_t rfc;

    memset(&help, 0, HELP_SIZE);
    memset(help.body_answer, 0, DEFAULT_BODY_LENGTH);
    help.header.name = HELP;
    help.header.size = HELP_CONTENT_SIZE;
    if (status == true) {
        rfc = set_help_rfc(200);
        sprintf(help.body_answer, "%s", answer);
        help_send(client, help);
        index = HELP_SIZE;
    } else {
        rfc = set_help_rfc(402);
    }
    send_rfc(client, rfc, index);
}

static void help_enough_argument(char buffer[DEFAULT_BODY_LENGTH], \
char **answer, client_t **client)
{
    for (int i = 0; command_name[i] != NULL; ++i) {
        my_const_strcat(answer, command_name[i]);
        my_const_strcat(answer, "\n");
    }
    memcpy(buffer, *answer, strlen(*answer));
    set_help(client, true, buffer);
}

void help(client_t *client, server_data **server)
{
    ctos_help_t help;
    char *answer = malloc(sizeof(char) * (DEFAULT_BODY_LENGTH + 1));
    char buffer[DEFAULT_BODY_LENGTH] = {0};

    memset(answer, 0, DEFAULT_BODY_LENGTH + 1);
    memset(&help, 0, sizeof(ctos_help_t));
    memcpy(&help, client->readbuffer, sizeof(ctos_help_t));
    if (strlen(help.arg) == 0) {
        help_enough_argument(buffer, &answer, &client);
    } else {
        help_get_argument(help.arg, &answer);
        if (strlen(answer) == 0)
            set_help(&client, false, buffer);
        else {
            memcpy(buffer, answer, strlen(answer));
            set_help(&client, true, buffer);
        }
    }
    free(answer);
}
