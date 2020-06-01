/*
** EPITECH PROJECT, 2020
** NWP_myteams_2019
** File description:
** push_client
*/

#include "server.h"

void push_client_list(client_list_t *client_list)
{
    FILE *file = fopen("./save/client.txt", "w");

    if (file == NULL)
        return;
    for (client_list_t *tmp = client_list; tmp != NULL; tmp = tmp->next) {
        fputs(tmp->uuid, file);
        fputs("\t", file);
        fputs(tmp->name, file);
        fputs("\n", file);
    }
    fclose(file);
}
