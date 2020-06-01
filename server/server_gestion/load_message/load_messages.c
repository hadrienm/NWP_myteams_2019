/*
** EPITECH PROJECT, 2020
** NWP_myteams_2019
** File description:
** load_messages
*/

#include "server.h"

static char **create_uuid_array(char *path)
{
    char **value = malloc(sizeof(char *) * 3);
    value[0] = malloc(sizeof(char) * SIZE_ID);
    value[1] = malloc(sizeof(char) * SIZE_ID);
    value[2] = NULL;
    bool status = false;
    size_t index = 0;

    memset(value[0], 0, SIZE_ID);
    memset(value[1], 0, SIZE_ID);
    for (size_t i = 0; path[i] != '\0'; ++index, ++i) {
        if (path[i] == '/' && status == false)
            status = true;
        else if (path[i] == '/' && status == true)
            break;
    }
    index += 1;
    for (size_t i = 0; i < SIZE_ID - 1; ++i, ++index)
        value[0][i] = path[index];
    for (size_t i = 0; i < SIZE_ID - 1; ++i, ++index)
        value[1][i] = path[index];
    return value;
}

static void add_first_message_to_list(cpr_message_list_t **list, \
char **details)
{
    cpr_message_list_t *new_node = malloc(sizeof(cpr_message_list_t));

    sprintf(new_node->message.uuid, details[0], SIZE_ID);
    new_node->message.timestamp = atoi(details[1]);
    sprintf(new_node->message.message, details[2], DEFAULT_BODY_LENGTH);
    new_node->next = NULL;
    free_array(details);
    (*list) = new_node;
}

void add_message_to_list(cpr_message_list_t **msg_list, char **details)
{
    cpr_message_list_t *new_node = NULL;

    for (size_t i = 0; details[2][i] != '\0'; ++i)
        details[2][i] == '\n' ? details[2][i] = '\0' : 0;
    if ((*msg_list) == NULL)
        return add_first_message_to_list(msg_list, details);
    new_node = malloc(sizeof(cpr_message_list_t));
    cpr_message_list_t *base = (*msg_list);
    for (; base->next != NULL; base = base->next);
    sprintf(new_node->message.uuid, details[0], SIZE_ID);
    new_node->message.timestamp = atoi(details[1]);
    sprintf(new_node->message.message, details[2], DEFAULT_BODY_LENGTH);
    new_node->next = NULL;
    free_array(details);
    base->next = new_node;
}

static void read_file(char *path, corresponding_t **cpr_list)
{
    char **details = NULL;
    char **uuid = NULL;
    FILE *file;
    char *line =NULL;
    size_t useless = 0;

    file = fopen(path, "r");
    if (file == NULL)
        return;
    uuid = create_uuid_array(path);
    while (getline(&line, &useless, file) != -1) {
        if (strlen(line) > SIZE_ID) {
            details = str_to_word_array(line, "\t");
            add_corresponding(cpr_list, uuid, details);
        }
    }
    free_array(uuid);
    fclose(file);
}

void load_messages(corresponding_t **cpr_list)
{
    (*cpr_list) = NULL;
    char **list = list_files();

    for (size_t i = 0; list && list[i] != NULL; ++i) {
        if (strlen(list[i]) > SIZE_ID * 2 - 2) {
            read_file(list[i], cpr_list);
        }
    }
}
