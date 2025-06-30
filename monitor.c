#include "philo.h"
int anybody_die(t_philo *philos)
{
    unsigned long long time;
    int index;

    time = get_time_ms();
    index = 0;
    while(index < philos->shared->number_philos)
    {
        pthread_mutex_lock(&philos[index].last_ate_protec);
        if (time - philos[index].last_ate_time >= (unsigned long long)philos->shared->time_to_die)
        {
            pthread_mutex_unlock(&philos[index].last_ate_protec);
            time -= philos->shared->start_time;
            printf("%llu %d died\n", time, philos[index].id);
            pthread_mutex_lock(&philos->shared->stop_mutex);
            philos->shared->stop = 1;
            pthread_mutex_unlock(&philos->shared->stop_mutex);
            return (1);
        }
        index++;
    }
    return (0);
}
int all_ate(t_philo *philos)
{
    int i = 0;
    int full_count = 0;
    while (i < philos->shared->number_philos)
    {
        pthread_mutex_lock(&philos[i].full_mutex);
        if (philos[i].full)
            full_count++;
        i++;
        pthread_mutex_unlock(&philos[i].full_mutex);
    }

    return (full_count == philos->shared->number_philos);
}

void *monitor(void *arg)
{
    t_philo *philo;

    philo = (t_philo *)arg;
    while (1)
    {
        if (anybody_die(philo) == 1)
            return (0);
        if (all_ate(philo))
            return (0);
        usleep(1000);
    }
    return (NULL);
}
