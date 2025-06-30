#include "philo.h"

void even_eating(t_philo *philo)
{
    grab_left_fork(philo);
    grab_right_fork(philo);
    ft_sleep(philo, 'e');
    philo->shared->forks[philo->id] = 0;
    pthread_mutex_unlock(&philo->shared->fork_mutexes[philo->id]);
    if (philo->id != philo->shared->number_philos - 1)
    {
        philo->shared->forks[philo->id + 1] = 0;
        pthread_mutex_unlock(&philo->shared->fork_mutexes[philo->id + 1]);
    }
    else
    {
        philo->shared->forks[0] = 0;
        pthread_mutex_unlock(&philo->shared->fork_mutexes[0]);
    }
}
void odd_eating(t_philo *philo)
{
    grab_right_fork(philo);
    grab_left_fork(philo);
    ft_sleep(philo, 'e');
    if (philo->id != philo->shared->number_philos - 1)
    {
        philo->shared->forks[philo->id + 1] = 0;
        pthread_mutex_unlock(&philo->shared->fork_mutexes[philo->id + 1]);
    }
    else
    {
        philo->shared->forks[0] = 0;
        pthread_mutex_unlock(&philo->shared->fork_mutexes[0]);
    }
    philo->shared->forks[philo->id] = 0;
    pthread_mutex_unlock(&philo->shared->fork_mutexes[philo->id]);
}


void     *routine(void *arg)
{
    t_philo *philo;
    int     num_eating;
    
    num_eating = 0;
    philo = (t_philo *)arg;
    while (philo->shared->eat_number == -1 || num_eating < philo->shared->eat_number)
    {
        if (should_stop(philo) == 1)
            return (NULL);
        if (philo->id % 2 == 1 || (philo->id == 0 && philo->shared->number_philos % 2 == 1))
            odd_eating(philo);
        else 
            even_eating(philo);
        num_eating++;
        if (should_stop(philo) == 1)
            return (NULL);
        ft_sleep(philo, 's');
        ft_sleep(philo, 't');

    }
    printf("about to lock full mutex\n");
    pthread_mutex_lock(&philo->full_mutex);
    philo->full = 1;
    pthread_mutex_unlock(&philo->full_mutex);
    printf("%llu %d is full\n", get_time_ms() - philo->shared->start_time, philo->id);
    return (NULL);
}