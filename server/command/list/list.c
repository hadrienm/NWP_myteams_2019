/*
** EPITECH PROJECT, 2020
** NWP_myteams_2019
** File description:
** list
*/

#include "server.h"

static bool verify_line(char *str)
{
    char **array = NULL;

    if (!str)
        return false;
    array = str_to_word_array(str, "\t");
    if (array == NULL || size_array(array) != 4) {
        free_array(array);
        return false;
    }
    if (strlen(array[0]) > DEFAULT_NAME_LENGTH || \
strlen(array[1]) != SIZE_ID || strlen(array[3]) > DEFAULT_BODY_LENGTH) {
        free_array(array);
        return false;
    }
    for (int i = 0; array[2][i]; ++i)
        if (array[2][i] > '9' || array[2][i] < '0') {
            free_array(array);
            return false;
        }
    return true;
}

static bool verify_all_file(char *line)
{
    char **array = NULL;

    if (line == NULL)
        return true;
    array = str_to_word_array(line, "\n");
    if (array == NULL)
        return false;
    for (int i = 0; array[i]; ++i)
        if (verify_line(array[i]) == false) {
            free_array(array);
            return false;
        }
    free_array(array);
    return true;
}

int count_in_str(char *str, char c)
{
    int count = 0;
    if (str == NULL)
        return 0;
    for (int i = 0; str[i]; ++i)
        if (str[i] == c)
            ++count;
    return count;
}

location_t determine_use(char *str)
{
    int n = 0;

    if (str == NULL)
        return TEAM;
    n = count_in_str(str, '/');
    switch (n) {
    case 2:
        return CHANNEL;
    case 3:
        return THREAD;
    case 4:
        return REPLIES;
    default:
        return TEAM;
    }
}

void list(client_t *client, client_t **client_list)
{
    ctos_list_t list;
    command_status_t rfc;
    char *str = NULL;

    if (client->uuid == NULL) {
        rfc = list_set_rfc(500, NULL);
        return list_send_rfc(&client, rfc, 0);
    }
    memset(&list, 0, sizeof(list));
    memcpy(&list, client->readbuffer, sizeof(ctos_list_t));
    if (count_in_str(client->use_path, '/') == 4)
        str = list_replies(client->use_path);
    else if (client->use_path == NULL)
        str = list_all_folders("./save/");
    else
        str = list_all_folders(client->use_path);
    if (str != NULL)
        send_list_success(&client, str);
    else
        list_send_rfc(&client, list_set_rfc(200, NULL), 0);
    free(str);
}