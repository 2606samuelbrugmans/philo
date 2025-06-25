#include "philo.h"
int cleanup(t_shared *shared, t_philo *philos)
{
    int i;

    if (shared->number_philos > 0 && philos)
    {
        i = 0;
        while (i < shared->number_philos)
        {
            pthread_mutex_destroy(&philos[i].last_ate_protec);
            pthread_mutex_destroy(&philos[i].full_mutex);
            if (shared->fork_mutexes)
                pthread_mutex_destroy(&shared->fork_mutexes[i]);
            i++;
        }
    }
    if (shared->fork_mutexes)
        free(shared->fork_mutexes);
    if (shared->forks)
        free(shared->forks);
    if (philos)
        free(philos);
    pthread_mutex_destroy(&shared->stop_mutex);
    return (0);
}


