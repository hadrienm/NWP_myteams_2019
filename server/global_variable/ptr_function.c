/*
** EPITECH PROJECT, 2020
** NWP_myteams_2019
** File description:
** ptr_function
*/

#include "server.h"

void (*const command[])(client_t *, server_data **) = {
    help, login, logout, users, user, send_c, messages, \
    subscribe, subscribed, unsubscribe, use, create, list, info, NULL
};