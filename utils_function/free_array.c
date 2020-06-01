/*
** EPITECH PROJECT, 2020
** NWP_myteams_2019
** File description:
** free_array
*/

#include <stddef.h>
#include <stdlib.h>

void free_array(char **array)
{
    if (array == NULL)
        return;
    for (int i = 0; array[i]; ++i)
        free(array[i]);
    free(array);
}
