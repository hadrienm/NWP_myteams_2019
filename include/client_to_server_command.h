/*
** EPITECH PROJECT, 2020
** NWP_myteams_2019
** File description:
** command
*/

#ifndef CLIENT_TO_SERVER_COMMAND_H_
#define CLIENT_TO_SERVER_COMMAND_H_

#include "my_teams.h"
#include "enum_command.h"

typedef struct client_to_server_header_s {
    command_t name;
    size_t size;
}ctos_header_t;

typedef struct client_to_server_help_s {
    ctos_header_t header;
    char arg[DEFAULT_BODY_LENGTH];
}ctos_help_t;

typedef struct client_to_server_login_s {
    ctos_header_t header;
    char name[DEFAULT_NAME_LENGTH];
}ctos_login_t;

typedef struct client_to_server_logout_s {
    ctos_header_t header;
}ctos_logout_t;

typedef struct client_to_server_users_s {
    ctos_header_t header;
}ctos_users_t;

typedef struct client_to_server_user_s {
    ctos_header_t header;
    char uuid[DEFAULT_BODY_LENGTH];
}ctos_user_t;

typedef struct client_to_serversend_s {
    ctos_header_t header;
    char uuid[SIZE_ID];
    char body[DEFAULT_BODY_LENGTH];
}ctos_send_t;

typedef struct client_to_server_messages_s {
    ctos_header_t header;
    char id[SIZE_ID];
}ctos_messages_t;

typedef struct client_to_server_subscribe_s {
    ctos_header_t header;
    char team_uuid[SIZE_ID];
}ctos_subscribe_t;

typedef struct client_to_server_subscribed_s {
    ctos_header_t header;
    char team_uuid[SIZE_ID];
}ctos_subscribed_t;

typedef struct client_to_server_unsubscribe_s {
    ctos_header_t header;
    char team_uuid[SIZE_ID];
}ctos_unsubscribe_t;

typedef struct client_to_server_use_s {
    ctos_header_t header;
    char team_uuid[SIZE_ID];
    char channel_uuid[SIZE_ID];
    char thread_uuid[SIZE_ID];
}ctos_use_t;

typedef struct client_to_server_create_s {
    ctos_header_t header;
    char name[DEFAULT_NAME_LENGTH];
    char message[DEFAULT_BODY_LENGTH];
    char uuid[SIZE_ID];
}ctos_create_t;

typedef struct client_to_server_list_s {
    ctos_header_t header;
}ctos_list_t;

typedef struct client_to_server_info_s {
    ctos_header_t header;
}ctos_info_t;

#endif /* !CLIENT_TO_SERVER_COMMAND_H_ */
