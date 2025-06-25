#include "philo.h"
void cleanup(t_philo *philos, t_shared *shared)
{
    int i = 0;
    while (i < shared->number_philos)
    {
        pthread_mutex_destroy(&shared->fork_mutexes[i]);
        i++;
    }
    free(shared->forks);
    free(shared->fork_mutexes);
    free(philos);
    pthread_mutex_destroy(&shared->full_mutex);
}

