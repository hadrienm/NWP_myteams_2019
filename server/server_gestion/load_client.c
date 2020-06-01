/*
** EPITECH PROJECT, 2020
** NWP_myteams_2019
** File description:
** load_login
*/

#include "server.h"

static void add_first_node(client_list_t **client_list, char **info)
{
    client_list_t *new_node = malloc(sizeof(client_list_t));

    if (new_node == NULL)
        return;
    sprintf(new_node->uuid, info[0], SIZE_ID);
    sprintf(new_node->name, info[1], DEFAULT_NAME_LENGTH);
    new_node->next = NULL;
    free_array(info);
    (*client_list) = new_node;
}

void add_node_to_client_list(client_list_t **client_list, char **info)
{
    client_list_t *new_node = NULL;

    if (*client_list == NULL)
        return add_first_node(client_list, info);
    new_node = malloc(sizeof(client_list_t));
    client_list_t *base = (*client_list);
    for (; base && base->next != NULL; base = base->next);
    sprintf(new_node->uuid, info[0], SIZE_ID);
    sprintf(new_node->name, info[1], DEFAULT_NAME_LENGTH);
    new_node->next = NULL;
    free_array(info);
    base->next = new_node;
}

void load_client(client_list_t **client_list)
{
    FILE *file = fopen("./save/client.txt", "r");
    char *line = NULL;
    (*client_list) = NULL;
    char **details = NULL;
    size_t useless = 0;

    if (file == NULL)
        return;
    while (getline(&line, &useless, file) != -1) {
        details = str_to_word_array(line, "\t");
        details[1][strlen(details[1]) - 1] = '\0';
        server_event_user_loaded(details[0], details[1]);
        add_node_to_client_list(client_list, details);
    }
    fclose(file);
    line != NULL ? free(line) : 0;
}
