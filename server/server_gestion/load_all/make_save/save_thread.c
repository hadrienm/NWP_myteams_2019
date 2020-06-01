/*
** EPITECH PROJECT, 2020
** Visual Studio Live Share (Workspace)
** File description:
** save_thread
*/

#include "server.h"

void create_replies(thread_t *thread)
{
    char *path = my_strcat(thread->path, "/conversation.txt");
    FILE *file = fopen(path, "w");
    char time[30] = {0};
    int i = 0;

    for (replies_t *r = thread->reply; file && r; r = r->next, ++i) {
        if (i == 0)
            continue;
        fputs(thread->uuid, file);
        fputs("\t", file);
        sprintf(time, "%d", r->timestamp);
        fputs(time, file);
        fputs("\t", file);
        fputs(r->body, file);
        fputs("\t", file);
        fputs(r->user_uuid, file);
        fputs("\n", file);
    }
    file != NULL ? fclose(file) : 0;
    free(path);
}

void create_thread(thread_t *thread)
{
    char *path = NULL;
    FILE *file = NULL;
    char time[30] = {0};

    mkdir(thread->path, 07777);
    path = my_strcat(thread->path, "/default.txt");
    file = fopen(path, "w");
    if (file == NULL)
        return free(path);
    fputs(thread->uuid, file);
    fputs("\t", file);
    sprintf(time, "%d", thread->timestamp);
    fputs(time, file);
    fputs("\t", file);
    fputs(thread->description, file);
    fputs("\t", file);
    fputs(thread->sender, file);
    fputs("\n", file);
    free(path);
    fclose(file);
}