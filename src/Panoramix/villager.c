/*
** EPITECH PROJECT, 2025
** Panoramix [WSL: Ubuntu]
** File description:
** villager
*/

#include "Panoramix/villager.h"
#include "Panoramix/panoramix.h"
#include <pthread.h>
#include <semaphore.h>
#include <stdio.h>
#include <stdlib.h>

static int wait_refill(void)
{
    panoramix_t *state = get_state(NULL);

    sem_wait(&state->sync->refilled_sem);
    pthread_mutex_lock(&state->sync->servings_mutex);
    if (state->sync->servings <= 0 && state->sync->druid_sleeping) {
        pthread_mutex_unlock(&state->sync->servings_mutex);
        return 0;
    }
    return 1;
}

static int take_serving(int villager_id)
{
    panoramix_t *state = get_state(NULL);

    pthread_mutex_lock(&state->sync->servings_mutex);
    printf("Villager %d: I need a drink... I see %d servings left.\n",
        villager_id, state->sync->servings);
    if (state->sync->servings <= 0) {
        printf("Villager %d: Hey Pano wake up! We need more potion.\n",
            villager_id);
        pthread_mutex_unlock(&state->sync->servings_mutex);
        sem_post(&state->sync->druid_sem);
        if (wait_refill() == 0)
            return 0;
    }
    if (state->sync->servings > 0) {
        state->sync->servings--;
        pthread_mutex_unlock(&state->sync->servings_mutex);
        return 1;
    }
    pthread_mutex_unlock(&state->sync->servings_mutex);
    return 0;
}

static void *villager_routine(void *arg)
{
    int villager_id = *(int *)arg;
    int nb_fights = get_state(NULL)->args->nb_fights;

    printf("Villager %d: Going into battle!\n", villager_id);
    while (nb_fights > 0) {
        if (take_serving(villager_id) == 0)
            break;
        nb_fights--;
        printf("Villager %d: Take that roman scum! Only %d left.\n",
            villager_id, nb_fights);
    }
    free(arg);
    printf("Villager %d: I'm going to sleep now.\n", villager_id);
    return NULL;
}

int create_villagers(pthread_t *villagers_threads, int nb_villagers)
{
    int *villager_id = NULL;

    for (int i = 0; i < nb_villagers; i++) {
        villager_id = malloc(sizeof(int));
        if (villager_id == NULL)
            return 84;
        *villager_id = i;
        if (pthread_create(&villagers_threads[i], NULL,
            villager_routine, villager_id) != 0) {
            free(villager_id);
            return 84;
        }
    }
    return 0;
}
