/*
** EPITECH PROJECT, 2020
** NWP_myteams_2019
** File description:
** list_thread
*/

#include "server.h"

void list_thread(server_data **s, client_t ** c)
{
    char *str = NULL;
    char buff[30];
    thread_t *th = find_channel_path(&(*s)->team, (*c)->use_path)->thread;

    for (; th; th = th->next) {
        memset(buff, 0, 30);
        sprintf(buff, "%d", th->timestamp);
        my_const_strcat(&str, th->name);
        my_const_strcat(&str, "\t");
        my_const_strcat(&str, th->uuid);
        my_const_strcat(&str, "\t");
        my_const_strcat(&str, buff);
        my_const_strcat(&str, "\t");
        my_const_strcat(&str, th->description);
        my_const_strcat(&str, "\t");
        my_const_strcat(&str, th->sender);
        my_const_strcat(&str, "\n");
    }
    if (str)
        send_list_success(c, str);
    free(str);
}
