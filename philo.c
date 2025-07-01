#include "philo.h"


int	thread_create(t_philo *philo)
{
	int index;

	index = 0;
	while (index < philo->shared->number_philos)
	{
		if (pthread_create(&philo[index].thread, NULL, routine, &philo[index]) != 0)
		{
			write(2, "failed to create a thread\n", 26);
			while (--index >= 0)
				pthread_join(philo[index].thread, NULL);
			return (1);
		}
		index++;
	}
	if (pthread_create(&philo->shared->monitor, NULL, monitor, philo) != 0)
		write(2, "failed to create a thread\n", 26);
	return (0);
}

int process(t_philo *philo)
{
    int index;

    index = 0;
    philo->shared->start_time = get_time_ms();
    while (index < philo->shared->number_philos)
    {
        philo[index].last_ate_time = philo->shared->start_time;
        index++;
    }
    if (thread_create(philo) != 0)
        return (1);
    usleep(100); 
    pthread_join(philo->shared->monitor, NULL);
    index = 0;
    while (index < philo->shared->number_philos)
    {
        pthread_join(philo[index].thread, NULL);
        index++;
    }
    return (0);
}
int	init_philos(t_philo **philos, t_shared *shared)
{
	int index;

	index = 0;
	*philos = malloc(sizeof(t_philo) * shared->number_philos);
	if (!*philos)
		return (1);
	while (index < shared->number_philos)
	{
		(*philos)[index].id = index;
		(*philos)[index].shared = shared;
		(*philos)[index].full = 0;
		(*philos)[index].last_ate_time = get_time_ms();
		pthread_mutex_init(&(*philos)[index].last_ate_protec, NULL);
		pthread_mutex_init(&(*philos)[index].full_mutex, NULL);
		index++;
	}
	return (0);
}

int init_shared(int argc, char **argv, t_shared *shared)
{
    int index;

    index = 0;
    args_create(shared, argc, argv);
    shared->forks = malloc(sizeof(int) * shared->number_philos);
    if (!shared->forks)
        return (1);
    shared->fork_mutexes = malloc(sizeof(pthread_mutex_t) * shared->number_philos);
    if (!shared->fork_mutexes)
        return (2);
    while (index < shared->number_philos)
    {
        pthread_mutex_init(&shared->fork_mutexes[index], NULL);
        shared->forks[index] = 0;
        index++;
    }
    pthread_mutex_init(&shared->stop_mutex, NULL);
    return (0);
}

int main(int argc, char **argv)
{
    t_philo *philosoph;
    t_shared shared;

    if (argc != 5 && argc != 6)
    {
        write(2, "number of arguments is inadequate\n", 35);
        return (-1);
    }
    if (init_shared(argc, argv, &shared) != 0)
        return (cleanup(&shared, philosoph));
    if (init_philos(&philosoph, &shared) != 0)
        return (cleanup(&shared, philosoph));
    if (is_valid(argc, &shared) == 0)
        process(philosoph);
    else 
        write(2, "args cant be negative numbers\n", 31);
    return (cleanup(&shared, philosoph));
}