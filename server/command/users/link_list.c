/*
** EPITECH PROJECT, 2020
** Visual Studio Live Share (Workspace)
** File description:
** link_list
*/

#include "server.h"

static void add_first_user(users_list_t **list, char **details, client_t **all)
{
    users_list_t *new_node = malloc(sizeof(users_list_t));

    if (new_node == NULL)
        return;
    memset(&new_node->users, 0, sizeof(users_list_t));
    new_node->users.header.name = USERS;
    new_node->users.header.size = users_content_size;
    sprintf(new_node->users.id, "%s", details[0]);
    sprintf(new_node->users.name, "%s", details[1]);
    new_node->users.status = check_users_is_log(details[0], all);
    new_node->next = NULL;
    (*list) = new_node;
}

static void add_node_users_list(users_list_t **list, char **details, \
client_t **all)
{
    users_list_t *new_node = NULL;
    users_list_t *base = NULL;

    if (*list == NULL)
        return add_first_user(list, details, all);
    new_node = malloc(sizeof(users_list_t));
    if (new_node == NULL)
        return;
    base = (*list);
    for (; base->next != NULL; base = base->next);
    memset(&new_node->users, 0, sizeof(users_list_t));
    new_node->users.header.name = USERS;
    new_node->users.header.size = users_content_size;
    sprintf(new_node->users.id, "%s", details[0]);
    sprintf(new_node->users.name, "%s", details[1]);
    new_node->users.status = check_users_is_log(details[0], all);
    new_node->next = NULL;
    base->next = new_node;
}

static char *handle_line(char *line)
{
    char *tmp = NULL;
    char *id = malloc(sizeof(char) * SIZE_ID);
    char *name = malloc(sizeof(char) * (strlen(line) - SIZE_ID + 2));
    size_t index = 0;

    memset(name, 0, strlen(line) - SIZE_ID + 2);
    memset(id, 0, SIZE_ID);
    for (int i = 0; index < SIZE_ID - 1; ++index, ++i)
        id[i] = line[index];
    for (int i = 0; line[index] != '\0'; ++index, ++i) {
        if (line[index] == '\n')
            break;
        name[i] = line[index];
    }
    my_const_strcat(&tmp, id);
    my_const_strcat(&tmp, " ");
    my_const_strcat(&tmp, name);
    free(id);
    free(name);
    return tmp;
}

static void handle_users_list(users_list_t **user_list, char *line, \
client_t **all)
{
    char **user_details = NULL;
    char **user_array = str_to_word_array(line, "\n");
    char *tmp = NULL;

    for (int i = 0; user_array[i] != NULL; ++i) {
        tmp = handle_line(user_array[i]);
        user_details = str_to_word_array(tmp, " ");
        add_node_users_list(user_list, user_details, all);
        free_array(user_details);
        free(tmp);
    }
    free_array(user_array);
}

bool create_users_list(client_t **client, client_t **all, \
users_list_t **users_list)
{
    FILE *file = fopen("./save/client.txt", "r");
    char *line = NULL;
    size_t useless = 0;

    if (file == NULL)
        return false;
    while (getline(&line, &useless, file) != -1)
        handle_users_list(users_list, line, all);
    free(line);
    fclose(file);
    return true;
}
