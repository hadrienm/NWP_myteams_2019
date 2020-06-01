/*
** EPITECH PROJECT, 2020
** NWP_myteams_2019
** File description:
** utils_client
*/

#include "client.h"

char *my_cut(char *str, int n)
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

int count_how_many(char *str, char c)
{
    int how_many = 0;

    if (str == NULL)
        return 0;
    for (int i = 0; str[i]; ++i)
        if (str[i] == c)
            ++how_many;
    return how_many;
}

char *my_strdup(char *str)
{
    if (str == NULL)
        return NULL;
    return strdup(str);
}

char **get_command(char *buffer)
{
    char **tmp;

    tmp = str_to_word_array(buffer, "\n");
    return tmp;
}

bool send_data(client_data * client)
{
    if (FD_ISSET(client->master_socket, &client->writefds)) {
        if (write(client->master_socket, client->data, client->data_size) \
!= client->data_size) {
            return false;
        } else {
            client->data = NULL;
        }
        return true;
    }
    return false;
}