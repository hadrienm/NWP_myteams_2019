/*
** EPITECH PROJECT, 2020
** NWP_myteams_2019
** File description:
** argument_gestion
*/

#include "client.h"

static void print_help(void)
{
    printf("USAGE: ./myteams_cli ip port\n\ntip is the \
server ip adress on which the server sokcet listens\n\t\
port is the number on which the server socket listens\n");
}

static int verify_if_int(int *point, char *str, int i)
{
    if (str[i] == '.') {
        *point += 1;
        if (!str[i + 1] || str[i + 1] == '.')
            return 84;
    }
    else if (str[i] > '9' || str[i] < '0')
        return 84;
    return 1;
}

static int verify_ip(char *str)
{
    int point = 0;

    if (!str)
        return 84;
    if (str[0] == '.')
        return 84;
    for (int i = 0; str[i]; ++i)
        if (verify_if_int(&point, str, i) == 84)
            return 84;
    if (point != 3)
        return 84;
    return 0;
}

static int verify_port(char *str)
{
    for (int i = 0; str[i] != '\0'; ++i)
        if (str[i] < '0' || str[i] > '9')
            return 84;
    if (atoi(str) <= 0)
        return 84;
    return 0;
}

int handle_args(client_data *c, char **av, int ac)
{
    if (ac != 3 || strcmp("-help", av[1]) == 0) {
        print_help();
        return 84;
    }
    if (verify_ip(av[1]) == 0 && verify_port(av[2]) == 0) {
        c->ip = strdup(av[1]);
        c->port = atoi(av[2]);
    } else {
        print_help();
        return 84;
    }
    return 0;
}