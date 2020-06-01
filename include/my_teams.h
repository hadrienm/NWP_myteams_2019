/*
** EPITECH PROJECT, 2020
** NWP_myteams_2019
** File description:
** my_teams
*/

#ifndef MY_TEAMS_H_
#define MY_TEAMS_H_

#define DEFAULT_DESCRIPTION_LENGTH 255
#define DEFAULT_BODY_LENGTH 512
#define DEFAULT_NAME_LENGTH 32
#define RFC_MESSAGE_LENGTH 40
#define SIZE_ID 37
#define MAX_SIZE 2048
#undef EXIT_FAILURE
#define EXIT_FAILURE 84

/* size server to client communication */
#define HEADER_SIZE (sizeof(int) + sizeof(size_t))
#define RFC_SIZE (HEADER_SIZE + RFC_MESSAGE_LENGTH + SIZE_ID)
#define RFC_CONTENT_SIZE (RFC_MESSAGE_LENGTH + SIZE_ID)
#define USER_SIZE (HEADER_SIZE + SIZE_ID + DEFAULT_NAME_LENGTH + sizeof(int))
#define USER_CONTENT_SIZE (SIZE_ID + DEFAULT_NAME_LENGTH + sizeof(int))
#define SUBSCRIBE_SIZE (HEADER_SIZE + SIZE_ID * 2)
#define SUBSCRIBE_CONTENT_SIZE (SIZE_ID * 2)
#define USERS_SIZE (HEADER_SIZE + SIZE_ID + DEFAULT_NAME_LENGTH + sizeof(int))
#define USERS_CONTENT_SIZE (SIZE_ID + DEFAULT_NAME_LENGTH + sizeof(int))
#define SUBSCRIBED_SIZE (HEADER_SIZE + SIZE_ID * 2 + DEFAULT_NAME_LENGTH + \
DEFAULT_DESCRIPTION_LENGTH + sizeof(int) * 2)
#define SUBSCRIBED_CONTENT_SIZE (SIZE_ID * 2 + DEFAULT_NAME_LENGTH + \
DEFAULT_DESCRIPTION_LENGTH + sizeof(int) * 2)
#define LIST_SIZE (HEADER_SIZE + SIZE_ID * 2 + DEFAULT_BODY_LENGTH + \
DEFAULT_NAME_LENGTH + sizeof(int) * 2)
#define LIST_CONTENT_SIZE (SIZE_ID * 2 + DEFAULT_BODY_LENGTH + \
DEFAULT_NAME_LENGTH + sizeof(int) * 2)
#define LOGOUT_SIZE (HEADER_SIZE + SIZE_ID + DEFAULT_NAME_LENGTH)
#define LOGOUT_CONTENT_SIZE (SIZE_ID + DEFAULT_NAME_LENGTH)
#define LOGIN_SIZE (HEADER_SIZE + SIZE_ID + DEFAULT_NAME_LENGTH)
#define LOGIN_CONTENT_SIZE (SIZE_ID + DEFAULT_NAME_LENGTH)
#define UNSUBSCRIBE_SIZE (HEADER_SIZE + SIZE_ID * 2)
#define UNSUBSCRIBE_CONTENT_SIZE (SIZE_ID * 2)
#define SEND_SIZE (HEADER_SIZE + SIZE_ID + DEFAULT_BODY_LENGTH)
#define SEND_CONTENT_SIZE (SIZE_ID + DEFAULT_BODY_LENGTH)
#define HELP_SIZE (HEADER_SIZE + DEFAULT_BODY_LENGTH)
#define HELP_CONTENT_SIZE (DEFAULT_BODY_LENGTH)
#define CREATE_SIZE (HEADER_SIZE + SIZE_ID * 3 + DEFAULT_NAME_LENGTH + \
DEFAULT_BODY_LENGTH + sizeof(int) * 2 + sizeof(bool))
#define CREATE_CONTENT_SIZE (SIZE_ID * 3 + DEFAULT_NAME_LENGTH + \
DEFAULT_BODY_LENGTH + sizeof(int) * 2 + sizeof(bool))
#define INFO_SIZE (HEADER_SIZE + SIZE_ID + DEFAULT_NAME_LENGTH + sizeof(int) \
+ DEFAULT_BODY_LENGTH)
#define INFO_CONTENT_SIZE (SIZE_ID + DEFAULT_NAME_LENGTH + sizeof(int) \
+ DEFAULT_BODY_LENGTH)

//Generique includes
#include <stddef.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <alloca.h>
#include <stdbool.h>
#include <regex.h>
#include <sys/stat.h>
#include <dirent.h>
#include <errno.h>

//To handle signal
#include <signal.h>

//To generate unique ID
#include <uuid/uuid.h>

//Inlcudes to create and handle sockets
#include <sys/socket.h>
#include <sys/types.h>
#include <netinet/in.h>
#include <sys/select.h>
#include <netdb.h>
#include <arpa/inet.h>

void my_const_strcat(char **str, const char *str2);

#endif /* !MY_TEAMS_H_ */
