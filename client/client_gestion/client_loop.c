/*
** EPITECH PROJECT, 2020
** NWP_myteams_2019
** File description:
** client_loop
*/

#include "client.h"

static char *my_cut(char *str, int n)
{
    char *value = NULL;
    int i = 0;

    if (str == NULL || str[0] == 0 || n >= (int)strlen(str))
        return NULL;
    for (i = n; str[i]; ++i);
    value = malloc(sizeof(char) * (i - n + 1));
    for (i = n; str[i]; ++i)
        value[i - n] = str[i];
    value[i - n] = 0;
    return value;
}

static int count_how_many(char *str, char c)
{
    int how_many = 0;

    if (str == NULL)
        return 0;
    for (int i = 0; str[i]; ++i)
        if (str[i] == c)
            ++how_many;

    return how_many;
}

static char *my_strdup(char *str)
{
    if (str == NULL)
        return NULL;
    return strdup(str);
}

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

static char **get_command(char *buffer)
{
    char **tmp;

    tmp = str_to_word_array(buffer, "\n");
    return tmp;
}

static bool send_data(client_data * client)
{
    if (FD_ISSET(client->master_socket, &client->writefds)) {
        if (write(client->master_socket, client->data, client->data_size) \
!= client->data_size)
            return false;
        else
            client->data = NULL;
        return true;
    }
    return false;
}

static int new_command_len(int len, size_t index, char *buffer, char **str)
{
    char *answer = NULL;

    if (len == 0)
        return -1;
    answer = malloc(sizeof(char) * (len + 2));
    for (len = index; buffer[len]; ++len) {
        if (buffer[len] == '\n')
            break;
        answer[len - index] = buffer[len];
    }
    answer[len - index] = 0;
    *str = strdup(answer);
    free(answer);
    return len + 1;
}

static int get_new_command(char **str, char *buffer, int index)
{
    free(*str);
    *str = NULL;
    char *answer = NULL;
    int len = 0;
    int mangetesmorts = 0;

    if (buffer == NULL)
        return -1;
    for (int i = 0; buffer[i]; ++i)
        if (buffer[i] == '\n')
            mangetesmorts = 1;
    if (mangetesmorts == 0)
        return -1;
    if (index >= (int)strlen(buffer))
        return -1;
    for (int i = index; buffer[i]; ++i, ++len)
        if (buffer[i] == '\n')
            break;
    return new_command_len(len, index, buffer, str);
}

static void command_is_right(client_data **client, int i)
{
    for (int j = 0; command_name[j]; ++j) {
        if (strcasecmp(command_name[j], (*client)->command[0]) == 0) {
            command[j](client);
            (*client)->buffer = my_cut((*client)->buffer, i);
            break;
        }
    }
}

static void error_case(client_data **client, int i)
{
    if ((*client)->command != NULL) {
        free_command(client);
        (*client)->buffer = my_cut((*client)->buffer, i);
        printf("Command unknown.\r\n");
    }
}

static void execute_command(client_data **client)
{
    int i = 0;
    char *str = NULL;

    while (i != -1) {
        i = 0;
        i = get_new_command(&str, (*client)->buffer, i);
        if (i == -1 || str == NULL) {
            (*client)->pending_command = my_strdup((*client)->buffer);
            (*client)->buffer != NULL ? free((*client)->buffer) : 0;
            (*client)->buffer = NULL;
            break;
        }
        (*client)->command = get_client_command(str);
        if ((*client)->command == NULL) {
            free((*client)->buffer);
            (*client)->buffer = NULL;
            return error("Command unknown.\r");
        }
        command_is_right(client, i);
        error_case(client, i);
    }
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

static int read_command(void *v, client_data **client, \
stoc_header_t headerd, ssize_t n)
{
    char buffer[DEFAULT_BODY_LENGTH] = {0};

    if (FD_ISSET((*client)->master_socket, &(*client)->readfds)) {
        n = read((*client)->master_socket, v, sizeof(int) + sizeof(size_t));
        n <= 0 ? stop = 0 : 0;
        if (!stop)
            return 1;
        memcpy(&headerd.name, v, sizeof(int));
        memcpy(&headerd.size, v + sizeof(int), sizeof(size_t));
        decrypt_command[headerd.name](&headerd, n, client);
    } else if (FD_ISSET(0, &(*client)->readfds)) {
        n = read(0, buffer, DEFAULT_BODY_LENGTH);
        n <= 0 ? stop = 0 : 0;
        if (!stop)
            return 1;
        true_execute_command(client, buffer);
        free_command(client);
    }
}

void client_loop(client_data ** client)
{
    char buffer[DEFAULT_BODY_LENGTH];
    stoc_header_t headerd;
    void * void_buffer = NULL;
    fd_set readfd;

    memset(&headerd, 0, sizeof(stoc_header_t));
    memset(&buffer, 0, DEFAULT_BODY_LENGTH);
    handle_fd(client);
    if (stop == 0)
        return;
    void_buffer = malloc(sizeof(stoc_header_t));
    select((*client)->master_socket + 1, &(*client)->readfds, NULL, NULL, NULL);
    if (read_command(void_buffer, client, headerd, 0)) {
        free(void_buffer);
        return;
    }
    if ((*client)->data != NULL)
        send_data(*client);
    free(void_buffer);
}
