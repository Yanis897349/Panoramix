/*
** EPITECH PROJECT, 2025
** Panoramix [WSL: Ubuntu]
** File description:
** panoramix
*/

#ifndef PANORAMIX_H_
    #define PANORAMIX_H_

    #include "Parser/parser.h"
    #include <pthread.h>
    #include <stdbool.h>
    #include <semaphore.h>

    #define USAGE_MSG_1 "USAGE: ./panoramix <nb_villagers> <pot_size> "
    #define USAGE_MSG_2 "<nb_fights> <nb_refills>\n"
    #define VALUES_MSG "Values must be >0.\n"

typedef struct sync_s {
    int servings;
    bool druid_sleeping;
    pthread_mutex_t servings_mutex;
    sem_t druid_sem;
    sem_t refilled_sem;
} sync_t;

typedef struct panoramix_s {
    args_t *args;
    sync_t *sync;
} panoramix_t;

panoramix_t *get_state(panoramix_t *state);
int run_panoramix(args_t *args);

#endif /* !PANORAMIX_H_ */
