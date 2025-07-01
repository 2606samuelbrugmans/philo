#include "philo.h"

int	anybody_die(t_philo *philos)
{
	unsigned long long time;
	int index;

	time = get_time_ms();
	index = 0;
	while (index < philos->shared->number_philos)
	{
		pthread_mutex_lock(&philos[index].last_ate_protec);
		if (time - philos[index].last_ate_time > (unsigned long long)philos->shared->time_to_die)
			return (death(philos, time, index), 1);
		pthread_mutex_unlock(&philos[index].last_ate_protec);
		index++;
	}
	return (0);
}

int	all_ate(t_philo *philos)
{
	int i;
	int full_count;

	i = 0;
	full_count = 0;
	while (i < philos->shared->number_philos)
	{
		pthread_mutex_lock(&philos[i].full_mutex);
		if (philos[i].full)
			full_count++;
		pthread_mutex_unlock(&philos[i].full_mutex);
		i++;
	}
	return (full_count == philos->shared->number_philos);
}

void *monitor(void *arg)
{
    t_philo *philo = (t_philo *)arg;

    while (1)
    {
        usleep(300);
        if (anybody_die(philo) == 1)
            break;
        usleep(200);
        if (all_ate(philo) == 1)
        {
            pthread_mutex_lock(&philo->shared->stop_mutex);
            philo->shared->stop = 1;
            pthread_mutex_unlock(&philo->shared->stop_mutex);
            break;
        }
        usleep(500); 
    }
    return (NULL);
}
