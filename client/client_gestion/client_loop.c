/*
** EPITECH PROJECT, 2020
** NWP_myteams_2019
** File description:
** client_loop
*/

#include "client.h"

static int check_command(client_data **client, char *buffer)
{
    char *save = NULL;
    int number = 0;

    if (buffer == NULL)
        return 0;
    save = my_strcat((*client)->buffer, buffer);
    free((*client)->buffer);
    (*client)->buffer = NULL;
    (*client)->buffer = strdup(save);
    free(save);
    if ((*client)->buffer[0] == '\n') {
        free((*client)->buffer);
        (*client)->buffer = NULL;
        return 0;
    }
    for (int i = 0; (*client)->buffer[i]; ++i)
        if ((*client)->buffer[i] == '\n')
            return 1;
    return 0;
}

static void true_execute_command(client_data **client, char *buffer)
{
    char *str = NULL;
    int i = 0;

    if (buffer == NULL)
        return;
    if (my_strcmp((*client)->pending_command, (*client)->buffer) != 0) {
        char *save = my_strdup((*client)->buffer);
        free((*client)->buffer);
        (*client)->buffer = my_strcat((*client)->pending_command, save);
        free(save);
    }
    if (check_command(client, buffer) == 0)
        return;
    (*client)->pending_command != NULL ? free((*client)->pending_command) : 0;
    (*client)->pending_command = NULL;
    execute_command(client);
}

static int read_command(client_data **client, ssize_t n)
{
    char buffer[MAX_SIZE] = {0};

    if (FD_ISSET((*client)->master_socket, &(*client)->readfds)) {
        n = read((*client)->master_socket, buffer, MAX_SIZE);
        n <= 0 ? stop = 0 : 0;
        if (!stop)
            return 1;
        save_decrypt_command(client, n, buffer);
        launch_command(client);
    } else if (FD_ISSET(0, &(*client)->readfds)) {
        n = read(0, buffer, DEFAULT_BODY_LENGTH);
        n <= 0 ? stop = 0 : 0;
        if (!stop)
            return 1;
        true_execute_command(client, buffer);
        free_command(client);
    }
    return 0;
}

void client_loop(client_data **client)
{
    handle_fd(client);
    if (stop == 0)
        return;
    if (read_command(client, 0) == 1)
        return;
    (*client)->data != NULL ? send_data(*client) : 0;
}
