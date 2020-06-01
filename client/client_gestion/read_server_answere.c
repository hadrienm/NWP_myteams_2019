/*
** EPITECH PROJECT, 2020
** NWP_myteams_2019
** File description:
** read_server_answere
*/

#include "client.h"

static int delete_useless_part_of_command(size_t size, int name, \
client_data **c, char *s)
{
    if ((*c)->read_size >= HEADER_SIZE + size) {
        decrypt_command[name](c);
        if ((*c)->read_size - HEADER_SIZE - size > 0) {
            s = malloc(sizeof(char) * ((*c)->read_size - HEADER_SIZE \
- size + 1));
            memset(s, 0, (*c)->read_size - HEADER_SIZE - size + 1);
            (*c)->read_size -= HEADER_SIZE + size;
            memcpy(s, (*c)->read_buffer + HEADER_SIZE + size, (*c)->read_size);
            free((*c)->read_buffer);
            (*c)->read_buffer = malloc(sizeof(char) * (*c)->read_size + 1);
            memset((*c)->read_buffer, 0, (*c)->read_size + 1);
            memcpy((*c)->read_buffer, s, (*c)->read_size);
            free(s);
        } else {
            (*c)->read_size = 0;
            free((*c)->read_buffer);
            (*c)->read_buffer = NULL;
        }
        return 0;
    }
    return 1;
}

void launch_command(client_data **client)
{
    int name = 0;
    size_t size = 0;
    size_t index = 0;
    char *save = NULL;

    while ((*client)->read_size >= HEADER_SIZE) {
        size = 0;
        index = 0;
        memcpy(&name, (*client)->read_buffer + index, sizeof(int));
        index += sizeof(int);
        memcpy(&size, (*client)->read_buffer + index, sizeof(size_t));
        if (delete_useless_part_of_command(size, name, client, save) == 1)
            break;
    }
}

static void realloc_read_buffer(client_data **client, char *line, size_t size)
{
    char *save = malloc(sizeof(char) * ((*client)->read_size + size + 1));

    memset(save, 0, (*client)->read_size + size + 1);
    memcpy(save, (*client)->read_buffer, (*client)->read_size);
    memcpy(save + (*client)->read_size, line, size);
    free((*client)->read_buffer);
    (*client)->read_buffer = malloc(sizeof(char) * ((*client)->read_size + \
size + 1));
    memset((*client)->read_buffer, 0, (*client)->read_size + size + 1);
    memcpy((*client)->read_buffer, save, (*client)->read_size + size + 1);
    (*client)->read_size += size;
    free(save);
}

void save_decrypt_command(client_data **client, size_t this_read, \
char *buffer)
{
    if ((*client)->read_size == 0) {
        (*client)->read_size = this_read;
        (*client)->read_buffer = malloc(sizeof(char) * (this_read + 1));
        memset((*client)->read_buffer, 0, this_read + 1);
        memcpy((*client)->read_buffer, buffer, this_read);
    } else {
        realloc_read_buffer(client, buffer, this_read);
    }
}
