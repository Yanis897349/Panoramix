/*
** EPITECH PROJECT, 2025
** Panoramix [WSL: Ubuntu]
** File description:
** panoramix
*/

#include "Panoramix/panoramix.h"
#include "Panoramix/druid.h"
#include "Panoramix/villager.h"
#include "Parser/parser.h"
#include <pthread.h>
#include <stdlib.h>

static int setup_panoramix(panoramix_t *state, args_t *args)
{
    state->args = args;
    state->sync = calloc(1, sizeof(sync_t));
    if (state->sync == NULL)
        return 84;
    state->sync->servings = args->pot_size;
    state->sync->druid_sleeping = false;
    if (pthread_mutex_init(&state->sync->servings_mutex, NULL) != 0)
        return 84;
    if (sem_init(&state->sync->druid_sem, 0, 0) != 0)
        return 84;
    if (sem_init(&state->sync->refilled_sem, 0, 0) != 0)
        return 84;
    return 0;
}

static void free_panoramix(panoramix_t *state)
{
    if (state == NULL)
        return;
    pthread_mutex_destroy(&state->sync->servings_mutex);
    sem_destroy(&state->sync->druid_sem);
    sem_destroy(&state->sync->refilled_sem);
    free(state->sync);
}

panoramix_t *get_state(panoramix_t *state)
{
    static panoramix_t *panoramix = NULL;

    if (state != NULL)
        panoramix = state;
    return panoramix;
}

int run_panoramix(args_t *args)
{
    pthread_t *villagers_threads = calloc(sizeof(pthread_t),
        args->nb_villagers);
    pthread_t druid_thread;
    panoramix_t state;

    if (villagers_threads == NULL)
        return 84;
    if (setup_panoramix(&state, args) == 84) {
        free(villagers_threads);
        return 84;
    }
    get_state(&state);
    create_druid(&druid_thread);
    create_villagers(villagers_threads, args->nb_villagers);
    pthread_join(druid_thread, NULL);
    for (int i = 0; i < args->nb_villagers; ++i)
        pthread_join(villagers_threads[i], NULL);
    free_panoramix(get_state(NULL));
    free(villagers_threads);
    return 0;
}
