#include "philo.h"
int all_ate(t_philo *philos)
{
    int i = 0;
    int full_count = 0;
    pthread_mutex_lock(philo->shared->full_mutex);
    while (i < philos->shared->number_philos)
    {
        if (philos[i].full)
            full_count++;
        i++;
    }
    pthread_mutex_unlock(philo->shared->full_mutex);

    return (full_count == philos->shared->number_philos);
}


int monitor(void *arg)
{
    t_philo *philo;
    unsigned long long time;
    int index;

    index = 0;
    philo = (t_philo *)arg;
    while (1)
    {
        time = get_time_ms();
        index = 0;
        while(index < (philo)->shared->number_philos)
        {
            if (time - (philo)[index].last_ate_time >= philo->shared->time_to_die)
            {
                time -= philo->shared->start_time;
                printf("%llu %d died", time, (philo)[index].id);

                return (0);
            }
            index++;
        }
        if (all_ate(philo))
            return (0);
        usleep(1000);
    }
    return (0);
}
int     process (t_philo    *philo)
{
    int index;

    index = 0;
    (*philo).shared->start_time = get_time_ms();
    while (index < philo[0].shared->number_philos)
    {
        if (pthread_create(&philo[index].thread, NULL, routine, &philo[index]) != 0)
        {
            write(2, "failed to create a thread", 26);
            return (-1);
        }
        index++;
    }
    if (pthread_create(&(*philo).shared->monitor, NULL, monitor, &(philo[0])) != 0)
    {
        write(2, "failed to create a thread", 26);
        return (-1);
    }
    pthread_join(philo[0].shared->monitor, NULL);
    index = 0;
    while (index < philo[0].shared->number_philos)
    {
        pthread_join(philo[index].thread, NULL);
        index++;
    }
    return (0)
}

void    even_eating(t_philo philo)
{
    grab_left_fork(philo);
    grab_right_Fork(philo);
    ft_sleep(philo, "eat");
    philo.shared->forks[philo.id] = 0;
    if (philo.id != philo.shared->number_philos - 1)
        philo.shared->forks[philo.id + 1] = 0;
    else
        philo.shared->forks[0] = 0;
    pthread_mutex_unlock(philo.shared->fork_mutexes[philo.id + 1]);
    pthread_mutex_unlock(philo.shared->fork_mutexes[philo.id]);
}
void    odd_eating(t_philo philo)
{
    grab_right_Fork(philo);
    grab_left_fork(philo);
    ft_sleep(philo, "eat");
    philo.shared->forks[philo.id] = 0;
    if (philo.id != philo.shared->number_philos - 1)
        philo.shared->forks[philo.id + 1] = 0;
    else
        philo.shared->forks[0] = 0;
    pthread_mutex_unlock(philo.shared->fork_mutexes[philo.id + 1]);
    pthread_mutex_unlock(philo.shared->fork_mutexes[philo.id]);
}

int     routine(void *arg)
{
    t_philo *philo;
    int     num_eating;
    
    num_eating = 0;
    philo = (t_philo *)arg;
    philo->shared->start_time = get_time_ms();
    while (!num_eating != philo->shared->eat_number)
    {
        if (philo->id % 2 == 0)
            even_eating(*philo);
        if (philo->id % 2 == 1)
            odd_eating(*philo);
        num_eating++;
        ft_sleep(philo, "sleep");

    }
    pthread_mutex_lock(philo->shared->full_mutex);
    philo->full = 1;
    pthread_mutex_unlock(philo->shared->full_mutex);
    return (0);
}
int     init(char **argv, t_philo *philos, t_shared *shared)
{
    int number_philos;
    int index;

    index = 0;
    shared->number_philos = number_philos;
    shared->time_to_die = ft_atoi(argv[2]);
    shared->time_to_eat = ft_atoi(argv[3]);
    shared->time_to_sleep = ft_atoi(argv[4]);

    if (argv[5] != NULL)
        shared->eat_number = ft_atoi(argv[5]);
    else
        shared->eat_number = -1;
    shared->forks = malloc(sizeof(int) * number_philos);
    if (!shared->forks)
        return (1);
    shared->fork_mutexes = malloc(sizeof(pthread_mutex_t) * number_philos);
    if (!shared->fork_mutexes)
        return (2);
    while (index < number_philos)
    {
        pthread_mutex_init(&shared->fork_mutexes[index], NULL);
        index++;
    }
    philos = malloc(sizeof(t_philo) * shared->number_philos);
    if (!philos)
        return (1);
    index = 0;
    while (index < number_philos)
    {
        philos[index].id = index;
        philos[index].shared = shared;
    }

    return (0); // Success

}
int main(int argc, char **argv)
{
   t_philo *philosoph;
   t_shared shared;

    if (argc == 4 || argc == 5)
    {
        write(2, "number of arguments is inadequate", 14);
        return (-1)
    }
    init(argv, philosoph, &shared);
    process(philosoph);


    

}