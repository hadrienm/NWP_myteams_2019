/*
** EPITECH PROJECT, 2020
** NWP_myteams_2019
** File description:
** ptr_function
*/

#include "client.h"

void (*const command[])(client_data **client) = {
    help, login, logout, users, user, send_c, messages, \
subscribe, subscribed, unsubscribe, use, create, list, info, NULL};

void (*const decrypt_command[])(stoc_header_t *, size_t, client_data **) = {
    help_decrypt, login_decrypt, logout_decrypt, users_decrypt, \
user_decrypt, send_decrypt, messages_decrypt, subscribe_decrypt, \
subscribed_decrypt, unsubscribe_decrypt, use_decrypt, create_decrypt, \
list_decrypt, info_decrypt, rfc_decrypt, NULL};
