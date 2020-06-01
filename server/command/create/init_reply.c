/*
** EPITECH PROJECT, 2020
** NWP_myteams_2019
** File description:
** init_reply
*/

#include "server.h"

void init_reply(thread_t **th)
{
    replies_t *r = malloc(sizeof(replies_t));

    memset(r->body, 0, DEFAULT_BODY_LENGTH);
    memset(r->user_uuid, 0, SIZE_ID);
    sprintf(r->user_uuid, "%s", (*th)->sender);
    sprintf(r->body, "%s", (*th)->description);
    r->next = NULL;
    r->timestamp = (*th)->timestamp;
    (*th)->reply = r;
}