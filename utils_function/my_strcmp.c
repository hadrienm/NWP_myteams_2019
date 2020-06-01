/*
** EPITECH PROJECT, 2020
** NWP_myteams_2019
** File description:
** my_strcmp
*/

#include "my_teams.h"

int my_strcmp(char *str1, char *str2)
{
    if (str1 == NULL || str2 == NULL)
        return 1;
    else
        return strcmp(str1, str2);
}