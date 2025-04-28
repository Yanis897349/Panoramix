/*
** EPITECH PROJECT, 2025
** Panoramix [WSL: Ubuntu]
** File description:
** main
*/

#include <stdio.h>
#include "Parser/parser.h"

static void print_usage(void)
{
    printf("USAGE: ./panoramix <nb_villagers> <pot_size> <nb_fights> ");
    printf("<nb_refills>\n");
}

int main([[maybe_unused]] int ac, [[maybe_unused]] char **av)
{
    args_t *args = NULL;

    if (ac != 5) {
        print_usage();
        return 84;
    }
    args = parse_args(av);
    if (args == NULL) {
        print_usage();
        return 84;
    }
    return 0;
}
