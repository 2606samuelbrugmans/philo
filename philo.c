#include "philo.h"
int     process (t_philo    *philo)
{
    int index;

    index = 0;
    while (index < philo[0].shared->number_philos)
    {
        if (pthread_create(&philo[index].thread, NULL, routine, &philo[index]) != 0)
        {
            write(2, "failed to create a thread", 26);
            return (-1);
        }
        index++;
    }
}
void    even_eating(t_philo philo)
{
    pthread_mutex_lock(philo.shared->fork_mutexes[philo.id]);

}
void    odd_eating(t_philo philo)
{
    pthread_mutex_lock(philo.shared->fork_mutexes[philo.id + 1]);

}

int     routine(void *arg)
{
    int current_time;
    t_philo *philo;
     
    philo = (t_philo *)arg;

    current_time = gettimeofday();
    while (alive)
    {
        if (philo->id % 2 == 0)
            even_eating(philo);
        if (philo->id % 2 == 1)
            odd_eating(philo);
        if ((*philo).shared->forks[(*philo).id] == 0 
            && (*philo).shared->forks[(*philo).id + 1])
        {
           pthread_mutex_lock(((*philo).shared->fork_mutexes)

        }

    }

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
    *philos = malloc(sizeof(t_philo) * shared->number_philos);
    if (!*philos)
        return (1);
    index = 0;
    while (index < number_philos)
    {
        (*philos)[index].id = index;
        (*philos)[index].shared = shared;
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