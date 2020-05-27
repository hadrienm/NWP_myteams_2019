/*
** EPITECH PROJECT, 2020
** NWP_myteams_2019
** File description:
** create_replies
*/

#include "server.h"

static void push_inside_file(FILE *pFile, char **uuid_thread, char temp[10], \
ctos_create_t create)
{
    fputs(uuid_thread[0], pFile);
    fputs("\t", pFile);
    fputs(temp, pFile);
    fputs("\t", pFile);
    fputs(create.message, pFile);
    fputs("\t", pFile);
}

static int write_replies(char *str, char *temp, ctos_create_t create, \
client_t **client)
{
    FILE *pFile;
    char **uuid_thread = NULL;
    char *description = get_description((*client)->use_path);

    if (description == NULL) return 0;
    pFile = fopen(str, "a");
    uuid_thread = str_to_word_array(description, "\t");
    if (uuid_thread == NULL || uuid_thread[0] == NULL) return 0;
    if (pFile != NULL) {
        push_inside_file(pFile, uuid_thread, temp, create);
        fputs((*client)->uuid, pFile);
        fputs("\n", pFile);
        fclose(pFile);
    } else {
        free(description);
        free_array(uuid_thread);
        return 0;
    }
    free(description);
    free_array(uuid_thread);
    return 1;
}

int add_message(client_t **client, ctos_create_t create, client_t **all)
{
    stoc_create_t c = memset_all(create, REPLIES, client);
    char temp[10];
    char *str = my_strcat((*client)->use_path, "/conversation.txt");

    sprintf(temp, "%d", (int)time(NULL));
    char *uuid_team = get_uuid_team((*client)->use_path);
    sprintf(c.team_uuid, "%s", str_to_word_array(get_description\
(get_uuid_team((*client)->use_path)), "\t")[0]);
    write_replies(str, temp, create, client);
    free(str);
    str = get_uuid_parent_folder((*client)->use_path);
    sprintf(c.thread_uuid, "%s", str);
    server_event_thread_new_message(str, (*client)->uuid, create.message);
    send_create(client, 0, c);
    create_subscribe_broadcast(create_set_broadcast_buffer(c), all, \
create_broadcast_subscribe_list(my_strcat(get_uuid_team((*client)->use_path), \
"/default.txt"), (*client)->uuid));
    free(str);
    free(uuid_team);
    return 1;
}