/*
** EPITECH PROJECT, 2020
** NWP_myteams_2019
** File description:
** help
*/

#include "client.h"

void help_decrypt(client_data **client)
{
    char body[DEFAULT_BODY_LENGTH];
    size_t index = HEADER_SIZE;

    memcpy(&body, (*client)->read_buffer + index, HELP_CONTENT_SIZE);
    printf("%s", body);
}

void help(client_data **client)
{
    ctos_help_t help;

    memset(&help, 0, sizeof(ctos_help_t));
    help.header.name = HELP;
    help.header.size = sizeof(help) - sizeof(help.header);
    memset(help.arg, 0, DEFAULT_BODY_LENGTH);
    if (size_array((*client)->command) > 1)
        sprintf(help.arg, "%s", (*client)->command[1]);
    write((*client)->master_socket, &help, sizeof(ctos_help_t));
    free((*client)->command);
    (*client)->command = NULL;
}
