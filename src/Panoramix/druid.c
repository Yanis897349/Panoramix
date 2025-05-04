/*
** EPITECH PROJECT, 2025
** Panoramix [WSL: Ubuntu]
** File description:
** druid
*/

#include "Panoramix/druid.h"
#include "Panoramix/panoramix.h"
#include <semaphore.h>
#include <stdio.h>
#include <pthread.h>

static void refill_pot(int nb_refills)
{
    panoramix_t *state = get_state(NULL);
    int remaining_refills = nb_refills - 1;

    pthread_mutex_lock(&state->sync->servings_mutex);
    printf("Druid: Ah! Yes, yes, I'm awake! Working on it! Beware I can ");
    printf("only make %d more refills after this one.\n", remaining_refills);
    state->sync->servings = state->args->pot_size;
    if (remaining_refills == 0) {
        printf("Druid: I'm out of viscum. I'm going back to... zZz\n");
        state->sync->druid_sleeping = true;
    }
    pthread_mutex_unlock(&state->sync->servings_mutex);
}

static void *druid_routine([[maybe_unused]] void *arg)
{
    panoramix_t *state = get_state(NULL);
    int nb_refills = state->args->nb_refills;

    printf("Druid: I'm ready... but sleepy...\n");
    while (nb_refills > 0) {
        sem_wait(&state->sync->druid_sem);
        refill_pot(nb_refills);
        for (int i = 0; i < state->args->nb_villagers; ++i) {
            sem_post(&state->sync->refilled_sem);
        }
        nb_refills--;
    }
    return NULL;
}

int create_druid(pthread_t *druid_thread)
{
    if (pthread_create(druid_thread, NULL,
        druid_routine, NULL) != 0) {
        return 84;
    }
    return 0;
}
