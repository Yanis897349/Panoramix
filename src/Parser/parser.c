/*
** EPITECH PROJECT, 2025
** Panoramix [WSL: Ubuntu]
** File description:
** parser
*/

#include "parser.h"
#include "Panoramix/panoramix.h"
#include <stdio.h>
#include <stdlib.h>

int parse_args(int ac, char **av, args_t *args)
{
    if (ac != 5) {
        printf(USAGE_MSG_1);
        printf(USAGE_MSG_2);
        return 84;
    }
    args->nb_villagers = atoi(av[1]);
    args->pot_size = atoi(av[2]);
    args->nb_fights = atoi(av[3]);
    args->nb_refills = atoi(av[4]);
    if (args->nb_villagers <= 0 || args->pot_size <= 0 ||
        args->nb_fights <= 0 || args->nb_refills <= 0) {
        printf(USAGE_MSG_1);
        printf(USAGE_MSG_2);
        printf(VALUES_MSG);
        return 84;
    }
    return 0;
}
