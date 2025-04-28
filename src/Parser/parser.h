/*
** EPITECH PROJECT, 2025
** Panoramix [WSL: Ubuntu]
** File description:
** parser
*/

#ifndef PARSER_H_
    #define PARSER_H_

typedef struct args_s {
    int nb_villagers;
    int pot_size;
    int nb_fights;
    int nb_refills;
} args_t;

int parse_args(int ac, char **av, args_t *args);

#endif /* !PARSER_H_ */
