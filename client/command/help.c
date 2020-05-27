/*
** EPITECH PROJECT, 2020
** NWP_myteams_2019
** File description:
** help
*/

#include "client.h"

void help_decrypt(stoc_header_t *header, size_t readed, client_data **client)
{
    char body[DEFAULT_BODY_LENGTH];
    void *k = malloc(header->size);

    read((*client)->master_socket, k, header->size);
    memcpy(&body, k, DEFAULT_BODY_LENGTH);
    printf("%s", body);
    free(k);
}

void help(client_data **client)
{
    ctos_help_t help;

    memset(&help, '\0', sizeof(ctos_help_t));
    help.header.name = HELP;
    help.header.size = sizeof(help) - sizeof(help.header);
    memset(help.arg, 0, DEFAULT_BODY_LENGTH);
    if (size_array((*client)->command) > 1)
        sprintf(help.arg, "%s", (*client)->command[1]);
    write((*client)->master_socket, &help, sizeof(ctos_help_t));
    free((*client)->command);
    (*client)->command = NULL;
}
