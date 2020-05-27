/*
** EPITECH PROJECT, 2020
** NWP_myteams_2019
** File description:
** main
*/

#include "client.h"

volatile int stop = 1;

static inline void ctrlhandler(int handler)
{
    (void)handler;
    stop = 0;
}

size_t size_array(char **array)
{
    int i = 0;

    if (array == NULL)
        return 0;
    for (; array[i]; ++i);
    return i;
}

int errorcase(char *str, client_data * client)
{
    free_struct(client);
    printf("%s\n", str);
    return 84;
}

void error(char *str)
{
    printf("%s\n", str);
}

int main(int ac, char **av)
{
    client_data *client = NULL;

    init_client(&client);
    signal(SIGINT, ctrlhandler);
    if (!client)
        return errorcase("malloc issue\n", client);
    if (handle_args(client, av, ac) == 84)
        return errorcase("bad args\n", client);
    if (connect_client(&client) == 84)
        return errorcase("couldn't connect\n", client);
    while (stop)
        client_loop(&client);
    free_struct(client);
    return 0;
}
