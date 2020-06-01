/*
** EPITECH PROJECT, 2020
** NWP_myteams_2019
** File description:
** push_messages
*/

#include "server.h"

static char *create_line(cpr_message_list_t *msg_list)
{
    char *line = NULL;
    char buff[30];

    for (cpr_message_list_t *tmp = msg_list; tmp != NULL; tmp = tmp->next) {
        my_const_strcat(&line, tmp->message.uuid);
        my_const_strcat(&line, "\t");
        sprintf(buff, "%d", tmp->message.timestamp);
        my_const_strcat(&line, buff);
        my_const_strcat(&line, "\t");
        my_const_strcat(&line, tmp->message.message);
        my_const_strcat(&line, "\n");
    }
    return line;
}

void push_corresponding_list(corresponding_t *cpr_list)
{
    char *line = NULL;
    char *str = NULL;
    size_t useless = 0;

    for (corresponding_t *tmp = cpr_list; tmp != NULL; tmp = tmp->next) {
        str = my_strcat("./save/", tmp->uuid1),
        str = my_strcat(str, tmp->uuid2);
        FILE *file = fopen(str, "w");
        if (file == NULL)
            return free(str);
        line = create_line(tmp->msg_list);
        fputs(line, file);
        fclose(file);
        free(line);
        free(str);
        line = NULL;
        str = NULL;
    }
}
