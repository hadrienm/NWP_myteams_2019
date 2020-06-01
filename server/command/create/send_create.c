/*
** EPITECH PROJECT, 2020
** NWP_myteams_2019
** File description:
** send_create
*/

#include "server.h"

stoc_create_t memset_all(ctos_create_t create, int local, client_t **cli)
{
    stoc_create_t c;

    memset(&c, 0, sizeof(stoc_create_t));
    c.header.name = CREATE;
    c.header.size = CREATE_CONTENT_SIZE;
    c.timestamp = (int)time(NULL);
    c.local = local;
    memset(c.team_uuid, 0, SIZE_ID);
    memset(c.user_uuid, 0, SIZE_ID);
    memset(c.thread_uuid, 0, SIZE_ID);
    memset(c.name, 0, DEFAULT_NAME_LENGTH);
    memset(c.description, 0, DEFAULT_BODY_LENGTH);
    sprintf(c.name, "%s", create.name);
    sprintf(c.description, "%s", create.message);
    sprintf(c.user_uuid, "%s", (*cli)->uuid);
    c.event = true;
    return c;
}

command_status_t set_create_rfc(int status)
{
    command_status_t rfc;

    memset(&rfc, 0, RFC_SIZE);
    memset(rfc.rfc_message, 0, RFC_MESSAGE_LENGTH);
    memset(rfc.id, 0, SIZE_ID);
    rfc.header.name = RFC;
    rfc.header.size = RFC_CONTENT_SIZE;
    if (status == 200)
        sprintf(rfc.rfc_message, "%s", rfc_message[CODE_200]);
    else if (status == 500)
        sprintf(rfc.rfc_message, "%s", rfc_message[CODE_500]);
    else {
        if (status == 401)
            sprintf(rfc.rfc_message, "%s", rfc_message[CODE_401]);
        else
            sprintf(rfc.rfc_message, "%s", rfc_message[CODE_506]);
    }
    return rfc;
}

static void send_create_two(client_t **client, size_t index, stoc_create_t c)
{
    memcpy((*client)->answer + index, &c.thread_uuid, SIZE_ID);
    index += SIZE_ID;
    memcpy((*client)->answer + index, &c.name, DEFAULT_NAME_LENGTH);
    index += DEFAULT_NAME_LENGTH;
    memcpy((*client)->answer + index, &c.description, DEFAULT_BODY_LENGTH);
    index += DEFAULT_BODY_LENGTH;
    memcpy((*client)->answer + index, &c.local, sizeof(int));
    index += sizeof(int);
    memcpy((*client)->answer + index, &c.timestamp, sizeof(int));
}

void send_create(client_t **client, size_t index, stoc_create_t c)
{
    (*client)->answer = malloc(CREATE_SIZE + RFC_SIZE);

    memset((*client)->answer, 0, CREATE_SIZE + RFC_SIZE);
    memcpy((*client)->answer, &c.header.name, sizeof(int));
    index += sizeof(int);
    memcpy((*client)->answer + index, &c.header.size, sizeof(size_t));
    index += sizeof(size_t);
    memcpy((*client)->answer + index, &c.event, sizeof(bool));
    index += sizeof(bool);
    memcpy((*client)->answer + index, &c.team_uuid, SIZE_ID);
    index += SIZE_ID;
    memcpy((*client)->answer + index, &c.user_uuid, SIZE_ID);
    index += SIZE_ID;
    send_create_two(client, index, c);
    send_rfc(client, set_create_rfc(200), CREATE_SIZE);
    (*client)->answer_size = CREATE_SIZE + RFC_SIZE;
}
