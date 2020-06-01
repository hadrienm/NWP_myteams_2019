/*
** EPITECH PROJECT, 2020
** Visual Studio Live Share (Workspace)
** File description:
** delete
*/

#include "server.h"

void delete_load_thread(channel_t **ch)
{
    for (thread_t *t = (*ch)->thread; t;) {
        for (replies_t *r = t->reply; r;) {
            replies_t *save = r->next;
            free(r);
            r = save;
        }
        t->path != NULL ? free(t->path) : 0;
        thread_t *save2 = t->next;
        free(t);
        t = save2;
    }
}

void delete_load(server_data **server)
{
    team_t *tmp = (*server)->team;

    for (; tmp;) {
        for (channel_t *ch = tmp->channel; ch;) {
            delete_load_thread(&ch);
            channel_t *save3 = ch->next;
            ch->path != NULL ? free(ch->path) : 0;
            free(ch);
            ch = save3;
        }
        team_t *save4 = tmp->next;
        tmp->path != NULL ? free(tmp->path) : 0;
        free_array(tmp->user_subscribe);
        free(tmp);
        tmp = save4;
    }
}