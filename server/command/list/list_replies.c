/*
** EPITECH PROJECT, 2020
** NWP_myteams_2019
** File description:
** list_replies
*/

#include "server.h"

static void list_replie_two(char **str, replies_t *r, thread_t *th)
{
    char buff[30];

    memset(buff, 0, 30);
    sprintf(buff, "%d", r->timestamp);
    my_const_strcat(str, th->name);
    my_const_strcat(str, "\t");
    my_const_strcat(str, th->uuid);
    my_const_strcat(str, "\t");
    my_const_strcat(str, buff);
    my_const_strcat(str, "\t");
    my_const_strcat(str, r->body);
    my_const_strcat(str, "\t");
    my_const_strcat(str, r->user_uuid);
    my_const_strcat(str, "\n");
}

void list_repli(server_data **s, client_t ** c)
{
    char *str = NULL;
    team_t *t = find_team_for_replies(s, (*c)->use_path);
    thread_t *th = find_thread_for_replies(&t, (*c)->use_path);

    if (th == NULL)
        return;
    replies_t *r = th->reply;
    for (; r; r = r->next)
        list_replie_two(&str, r, th);
    if (str)
        send_list_success(c, str);
    free(str);
}
