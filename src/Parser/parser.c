/*
** EPITECH PROJECT, 2025
** Panoramix [WSL: Ubuntu]
** File description:
** parser
*/

#include "parser.h"
#include <stdlib.h>

args_t *parse_args(char **av)
{
    args_t *args = calloc(1, sizeof(args_t));

    if (args == NULL)
        return (NULL);
    args->nb_villagers = atoi(av[1]);
    args->pot_size = atoi(av[2]);
    args->nb_fights = atoi(av[3]);
    args->nb_refills = atoi(av[4]);
    if (args->nb_villagers <= 0 || args->pot_size <= 0 ||
        args->nb_fights <= 0 || args->nb_refills <= 0) {
        free(args);
        return (NULL);
    }
    return (args);
}
