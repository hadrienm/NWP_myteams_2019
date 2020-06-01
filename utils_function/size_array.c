/*
** EPITECH PROJECT, 2020
** Visual Studio Live Share (Workspace)
** File description:
** size_array
*/

#include <stddef.h>
#include <stdlib.h>

size_t size_array(char **array)
{
    size_t size = 0;

    if (array == NULL)
        return 0;
    for (; array[size] != NULL; ++size);
    return size;
}
