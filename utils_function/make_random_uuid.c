/*
** EPITECH PROJECT, 2020
** NWP_myteams_2019
** File description:
** make_random_uuid
*/

#include "my_teams.h"

char *make_random_uuid(void)
{
    uuid_t binuuid;

    uuid_generate_random(binuuid);
    char *uuid = malloc(SIZE_ID);
    if (uuid)
        uuid_unparse_upper(binuuid, uuid);
    return uuid;
}
