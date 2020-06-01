/*
** EPITECH PROJECT, 2020
** Visual Studio Live Share (Workspace)
** File description:
** make_save
*/

#include "server.h"

void create_channel(channel_t *channel)
{
    char *path = NULL;
    FILE *file = NULL;
    char time[30] = {0};

    mkdir(channel->path, 07777);
    path = my_strcat(channel->path, "/default.txt");
    file = fopen(path, "w");
    if (file == NULL)
        return free(path);
    fputs(channel->uuid, file);
    fputs("\t", file);
    sprintf(time, "%d", channel->timestamp);
    fputs(time, file);
    fputs("\t", file);
    fputs(channel->description, file);
    fputs("\n", file);
    free(path);
    fclose(file);
}

void create_team(team_t *team)
{
    char *path = NULL;
    FILE *file = NULL;
    char time[30] = {0};

    mkdir(team->path, 07777);
    path = my_strcat(team->path, "/default.txt");
    file = fopen(path, "w");
    if (file == NULL)
        return free(path);
    fputs(team->uuid, file);
    fputs("\t", file);
    sprintf(time, "%d", team->timestamp);
    fputs(time, file);
    fputs("\t", file);
    fputs(team->description, file);
    fputs("\n", file);
    for (int i = 0; team->user_subscribe && team->user_subscribe[i]; ++i, \
fputs("\n", file))
        fputs(team->user_subscribe[i], file);
    free(path);
    fclose(file);
}

void make_save_thread(channel_t *c)
{
    for (thread_t *th = c->thread; th; th = th->next) {
        create_thread(th);
        char *str = my_strcat(th->path, "/conversation.txt");
        int status = remove(str);
        free(str);
        create_replies(th);
    }
}

void make_save(server_data *server)
{
    bool check = false;

    for (team_t *t = server->team; t; t = t->next) {
        create_team(t);
        for (channel_t *c = t->channel; c; c = c->next) {
            create_channel(c);
            make_save_thread(c);
        }
    }
}