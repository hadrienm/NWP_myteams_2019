/*
** EPITECH PROJECT, 2020
** NWP_myteams_2019
** File description:
** argument_gestion
*/

#include "server.h"

static void print_help(void)
{
    printf("USAGE: ./myteams_server port\n\n\tport is \
the port number on which the server socket listens.\n");
}

int handle_args(server_data *server, char **av, int ac)
{
    int port = 0;

    if (ac != 2 || strcmp("-help", av[1]) == 0) {
        print_help();
        return 84;
    }
    port = atoi(av[1]);
    if (port <= 0)
        return 84;
    server->port = port;
    return 0;
}