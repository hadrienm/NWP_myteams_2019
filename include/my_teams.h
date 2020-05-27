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
