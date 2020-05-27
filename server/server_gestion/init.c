/*
** EPITECH PROJECT, 2020
** NWP_myteams_2019
** File description:
** init
*/

#include "server.h"

static void handle_line(char *line)
{
    char *tmp_name = malloc(sizeof(char) * (strlen(line) - SIZE_ID + 1));
    char *tmp_id = malloc(sizeof(char) * SIZE_ID);
    int index = 0;

    memset(tmp_id, 0, SIZE_ID);
    memset(tmp_name, 0, strlen(line) - SIZE_ID + 1);
    for (int i = 0; i < SIZE_ID - 1; ++i, ++index)
        tmp_id[i] = line[index];
    for (int i = 0; line[index] != '\0'; ++i, ++index) {
        if (line[index] == '\n')
            break;
        tmp_name[i] = line[index];
    }
    server_event_user_loaded(tmp_id, tmp_name);
    free(tmp_name);
    free(tmp_id);
}

void load_client(void)
{
    FILE *file = fopen("./save/client.txt", "r");
    int read = 0;
    size_t useless = 0;
    char *line = NULL;

    if (file == NULL)
        return;
    while ((read = getline(&line, &useless, file)) != -1) {
        if (strlen(line) > SIZE_ID)
            handle_line(line);
    }
    fclose(file);
    line != NULL ? free(line) : 0;
}

bool init_server_data(server_data **server)
{
    (*server) = malloc(sizeof(server_data));
    if ((*server) == NULL)
        return false;
    (*server)->port = 0;
    (*server)->master_socket = 0;
    (*server)->client = NULL;
    return true;
}

int init_server(server_data *server)
{
    server->master_socket = socket(AF_INET, SOCK_STREAM, 0);
    if (server->master_socket == -1) {
        printf("Failed to create TCP socket\n");
        return 84;
    }
    bzero(&(server->address), sizeof(server->address));
    (server->address).sin_family = AF_INET;
    (server->address).sin_port = htons(server->port);
    (server->address).sin_addr.s_addr = htonl(INADDR_ANY);

    if (bind(server->master_socket, (struct sockaddr *)\
&(server->address), sizeof(server->address)) == -1) {
        printf("Bind failed\n");
        return 84;
    }
    if (listen(server->master_socket, 1024) != 0) {
        printf("Listen failed\n");
        return 84;
    }
    return 0;
}
