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

void rfc_decrypt(stoc_header_t *header, size_t readed, client_data **client)
{
    char rfc[RFC_MESSAGE_LENGTH];
    char id[SIZE_ID];
    void *k = malloc(header->size);

    read((*client)->master_socket, k, header->size);
    memcpy(&rfc, k, RFC_MESSAGE_LENGTH);
    memcpy(&id, k + RFC_MESSAGE_LENGTH, SIZE_ID);
    if (strncmp("500", rfc, 3) == 0)
        client_error_unauthorized();
    else if (strncmp("502", rfc, 3) == 0)
        client_error_unknown_user(id);
    else
        rfc_decrypt_two(rfc, id);
    dprintf(1, "%s", rfc);
    free(k);
}
