/*
** EPITECH PROJECT, 2020
** NWP_myteams_2019
** File description:
** server_to_client_command
*/

#ifndef SERVER_TO_CLIENT_COMMAND_H_
#define SERVER_TO_CLIENT_COMMAND_H_

#include "my_teams.h"
#include "enum_command.h"

typedef enum location_s {
    TEAM,
    CHANNEL,
    THREAD,
    REPLIES
}location_t;

typedef struct server_to_client_header_s {
    command_t name;
    size_t size;
}stoc_header_t;

typedef struct command_status_s {
    stoc_header_t header;
    char rfc_message[RFC_MESSAGE_LENGTH];
    char id[SIZE_ID];
}command_status_t;

typedef struct server_to_client_help_s {
    stoc_header_t header;
    char body_answer[DEFAULT_BODY_LENGTH];
}stoc_help_t;

typedef struct server_to_client_login_s {
    stoc_header_t header;
    char user_id[SIZE_ID];
    char name[DEFAULT_NAME_LENGTH];
}stoc_login_t;

typedef struct server_to_client_logout_s {
    stoc_header_t header;
    char user_id[SIZE_ID];
    char name[DEFAULT_NAME_LENGTH];
}stoc_logout_t;

typedef struct server_to_client_users_s {
    stoc_header_t header;
    char id[SIZE_ID];
    char name[DEFAULT_NAME_LENGTH];
    int status;
}stoc_users_t;

typedef struct users_list_s
{
    stoc_users_t users;
    struct users_list_s *next;
}users_list_t;

typedef struct server_to_client_user_s {
    stoc_header_t header;
    char id[SIZE_ID];
    char name[DEFAULT_NAME_LENGTH];
    int status;
}stoc_user_t;

typedef struct server_to_clientsend_s {
    stoc_header_t header;
    char user_id[SIZE_ID];
    char message_body[DEFAULT_BODY_LENGTH];
}stoc_send_t;

typedef struct server_to_client_messages_s {
    stoc_header_t header;
    char id[SIZE_ID];
    char message[DEFAULT_BODY_LENGTH];
    int timestamp;
}stoc_messages_t;

typedef struct messages_list_s
{
    stoc_messages_t message;
    struct messages_list_s *next;
}messages_list_t;

typedef struct server_to_client_subscribe_s {
    stoc_header_t header;
    char team_id[SIZE_ID];
    char user_id[SIZE_ID];
}stoc_subscribe_t;

typedef struct server_to_client_subscribed_s {
    stoc_header_t header;
    char team_id[SIZE_ID];
    char user_id[SIZE_ID];
    char desription[DEFAULT_DESCRIPTION_LENGTH];
    char name[DEFAULT_NAME_LENGTH];
    int timestamp;
    int status;
}stoc_subscribed_t;

typedef struct subscribed_list_s {
    struct subscribed_list_s *next;
    stoc_subscribed_t subscribed;
}subscribed_list_t;

typedef struct server_to_client_unsubscribe_s {
    stoc_header_t header;
    char team_id[SIZE_ID];
    char user_id[SIZE_ID];
}stoc_unsubscribe_t;

typedef struct server_to_client_use_s {
    stoc_header_t header;
}stoc_use_t;

typedef struct server_to_client_create_s {
    stoc_header_t header;
    char team_uuid[SIZE_ID];
    char user_uuid[SIZE_ID];
    char thread_uuid[SIZE_ID];
    char name[DEFAULT_NAME_LENGTH];
    char description[DEFAULT_BODY_LENGTH];
    location_t local;
    int timestamp;
    bool event;
}stoc_create_t;

typedef struct server_to_client_list_s {
    stoc_header_t header;
    char team_uuid[SIZE_ID];
    char user_uuid[SIZE_ID];
    char body[DEFAULT_BODY_LENGTH];
    char name[DEFAULT_NAME_LENGTH];
    int time;
    location_t function;
}stoc_list_t;

typedef struct list_list_s {
    struct list_list_s *next;
    stoc_list_t list;
}list_list_t;

typedef struct server_to_client_info_s {
    stoc_header_t header;
    char description[DEFAULT_BODY_LENGTH];
    char name[DEFAULT_NAME_LENGTH];
    char uuid[SIZE_ID];
    int timestamp;
}stoc_info_t;

#endif /* !SERVER_TO_CLIENT_COMMAND_H_ */
