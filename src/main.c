/*
** EPITECH PROJECT, 2025
** Panoramix [WSL: Ubuntu]
** File description:
** main
*/

#include "Parser/parser.h"
#include "Panoramix/panoramix.h"

int main([[maybe_unused]] int ac, [[maybe_unused]] char **av)
{
    args_t args;

    if (parse_args(ac, av, &args) == 84)
        return 84;
    return run_panoramix(&args);
}
