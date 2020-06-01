/*
** EPITECH PROJECT, 2020
** NWP_myteams_2019
** File description:
** rfc
*/

#include "client.h"

void rfc_decrypt_three(char rfc[RFC_MESSAGE_LENGTH], char id[SIZE_ID])
{
    if (strncmp("505", rfc, 3) == 0)
        client_error_unknown_thread(id);
    else if (strncmp("506", rfc, 3) == 0)
        client_error_already_exist();
}

void rfc_decrypt_two(char rfc[RFC_MESSAGE_LENGTH], char id[SIZE_ID])
{
    if (strncmp("503", rfc, 3) == 0)
        client_error_unknown_team(id);
    else if (strncmp("504", rfc, 3) == 0)
        client_error_unknown_channel(id);
    else
        rfc_decrypt_three(rfc, id);
}

void rfc_decrypt(client_data **client)
{
    char rfc[RFC_MESSAGE_LENGTH] = {0};
    char id[SIZE_ID] = {0};
    size_t index = HEADER_SIZE;

    memcpy(&rfc, (*client)->read_buffer + index, RFC_MESSAGE_LENGTH);
    index += RFC_MESSAGE_LENGTH;
    memcpy(&id, (*client)->read_buffer + index, SIZE_ID);
    if (strncmp("500", rfc, 3) == 0)
        client_error_unauthorized();
    else if (strncmp("502", rfc, 3) == 0)
        client_error_unknown_user(id);
    else
        rfc_decrypt_two(rfc, id);
    dprintf(1, "%s", rfc);
}
