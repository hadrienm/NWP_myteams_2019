/*
** EPITECH PROJECT, 2020
** NWP_myteams_2019
** File description:
** get_messages
*/

#include "server.h"

bool found_conversation(char *uuid1, char *uuid2, corresponding_t *cpr_list)
{
    char *path1 = NULL;
    char *path2 = NULL;
    char *str = NULL;

    for (corresponding_t *tmp = cpr_list; tmp != NULL; tmp = tmp->next) {
        if ((strcmp(uuid1, tmp->uuid1) == 0 || \
strcmp(uuid1, tmp->uuid2) == 0) && (strcmp(uuid2, tmp->uuid1) == 0 || \
strcmp(uuid2, tmp->uuid2) == 0))
            return true;
    }
    return false;
}

static char * create_line(cpr_message_list_t *msg_list)
{
    char *answer = NULL;
    char buff[30] = {0};

    for (cpr_message_list_t *tmp = msg_list; tmp != NULL; tmp = tmp->next) {
        my_const_strcat(&answer, tmp->message.uuid);
        my_const_strcat(&answer, "\t");
        sprintf(buff, "%d", tmp->message.timestamp);
        my_const_strcat(&answer, buff);
        my_const_strcat(&answer, "\t");
        my_const_strcat(&answer, tmp->message.message);
        my_const_strcat(&answer, "\n");
    }
    return answer;
}

char *list_conversation(char *uuid1, char *uuid2, corresponding_t *cpr_list)
{
    for (corresponding_t *tmp = cpr_list; tmp != NULL; tmp = tmp->next) {
        if ((strcmp(uuid1, tmp->uuid1) == 0 || \
strcmp(uuid1, tmp->uuid2) == 0) && (strcmp(uuid2, tmp->uuid1) == 0 || \
strcmp(uuid2, tmp->uuid2) == 0))
            return create_line(tmp->msg_list);
    }
}

size_t size_of_list(messages_list_t *list)
{
    size_t size = 0;

    messages_list_t *tmp = list;
    while (tmp != NULL) {
        tmp = tmp->next;
        ++size;
    }
    return size;
}
