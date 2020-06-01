/*
** EPITECH PROJECT, 2020
** NWP_myteams_2019
** File description:
** main
*/

#include "server.h"

static volatile int stop = 1;

void ctrlhandler(int handler)
{
    (void)handler;
    stop = 0;
}

static int create_save(void)
{
    bool check = mkdir("./save", 0777);

    if (check && errno != EEXIST)
        return 84;
    return EXIT_SUCCESS;
}

static int launch_server(server_data **server, char **av, int ac)
{
    if (init_server_data(server) == false)
        return 84;
    signal(SIGINT, ctrlhandler);
    if (handle_args(*server, av, ac) == 84)
        return 84;
    if (init_server(*server) == 84)
        return 84;
    if (create_save() == 84)
        return 84;
    load_client(&(*server)->client_list);
    load_messages(&(*server)->crp_list);
    load_all(server);
    return 0;
}

static void close_server(server_data **server)
{
    push_client_list((*server)->client_list);
    push_corresponding_list((*server)->crp_list);
    free_useless(&(*server)->client, true);
    close((*server)->master_socket);
    make_save(*server);
    delete_load(server);
    free_server_data(server);
}

int main(int ac, char **av)
{
    server_data *server = NULL;

    if (launch_server(&server, av, ac) == 84)
        return 84;
    while (stop)
        server_loop(server);
    close_server(&server);
    return 0;
}
