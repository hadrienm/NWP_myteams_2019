/*
** EPITECH PROJECT, 2020
** NWP_myteams_2019
** File description:
** list_channel
*/

#include "server.h"

void list_channel(server_data **s, client_t ** c)
{
    char *str = NULL;
    char buff[30];
    channel_t *ch = find_team(&(*s)->team, (*c)->use_path)->channel;
    for (; ch; ch = ch->next) {
        memset(buff, 0, 30);
        sprintf(buff, "%d", ch->timestamp);
        my_const_strcat(&str, ch->name);
        my_const_strcat(&str, "\t");
        my_const_strcat(&str, ch->uuid);
        my_const_strcat(&str, "\t");
        my_const_strcat(&str, buff);
        my_const_strcat(&str, "\t");
        my_const_strcat(&str, ch->description);
        my_const_strcat(&str, "\n");
    }
    if (str)
        send_list_success(c, str);
    free(str);
}
