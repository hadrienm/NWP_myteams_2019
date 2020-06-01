/*
** EPITECH PROJECT, 2020
** NWP_myteams_2019
** File description:
** info
*/

#include "server.h"

static command_status_t info_set_rfc(int status)
{
    command_status_t rfc;

    memset(&rfc, 0, RFC_SIZE);
    memset(rfc.rfc_message, 0, RFC_MESSAGE_LENGTH);
    memset(rfc.id, 0, SIZE_ID);
    rfc.header.name = RFC;
    rfc.header.size = RFC_CONTENT_SIZE;
    if (status == 500)
        sprintf(rfc.rfc_message, "%s", rfc_message[CODE_500]);
    else
        sprintf(rfc.rfc_message, "%s", rfc_message[CODE_200]);
    return rfc;
}

static stoc_info_t init_info(void)
{
    stoc_info_t info;

    memset(&info, 0, sizeof(stoc_info_t));
    info.header.name = INFO;
    info.header.size = INFO_CONTENT_SIZE;
    memset(info.name, 0, DEFAULT_NAME_LENGTH);
    memset(info.uuid, 0, SIZE_ID);
    memset(info.description, 0, DEFAULT_DESCRIPTION_LENGTH);
    info.timestamp = 0;
    return info;
}

void send_info(client_t **client, stoc_info_t info)
{
    command_status_t rfc = info_set_rfc(200);
    size_t index = 0;

    (*client)->answer = malloc(INFO_SIZE + RFC_SIZE);
    memcpy((*client)->answer, &info.header.name, sizeof(int));
    index += sizeof(int);
    memcpy((*client)->answer + index, &info.header.size, sizeof(size_t));
    index += sizeof(size_t);
    memcpy((*client)->answer + index, &info.description, DEFAULT_BODY_LENGTH);
    index += DEFAULT_BODY_LENGTH;
    memcpy((*client)->answer + index, &info.name, DEFAULT_NAME_LENGTH);
    index += DEFAULT_NAME_LENGTH;
    memcpy((*client)->answer + index, &info.uuid, SIZE_ID);
    index += SIZE_ID;
    memcpy((*client)->answer + index, &info.timestamp, sizeof(int));
    (*client)->answer_size = INFO_SIZE + RFC_SIZE;
    send_rfc(client, rfc, INFO_SIZE);
}

void info(client_t *client, server_data **server)
{
    stoc_info_t info = init_info();
    short n = 0;

    if (client->name == NULL)
        return send_rfc(&client, info_set_rfc(500), 0);
    n = count_in_str(client->use_path, '/');
    switch (n) {
    case 0:
        return info_user(server, &client, info);
    case 2:
        return info_team(server, &client, info);
    case 3:
        return info_channel(server, &client, info);
    default:
        return info_thread(server, &client, info);
    }
}
