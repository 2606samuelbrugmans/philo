#include "philo.h"

void	odd_eating(t_philo *philo)
{
	int right;

	right = who_right(philo);
	grab_left_fork(philo);
	grab_right_fork(philo, right);
	ft_sleep(philo, 'e');
	philo->shared->forks[philo->id] = 0;
	pthread_mutex_unlock(&philo->shared->fork_mutexes[philo->id]);
	philo->shared->forks[right] = 0;
	pthread_mutex_unlock(&philo->shared->fork_mutexes[right]);
}

void	even_eating(t_philo *philo)
{
	int right;

	right = who_right(philo);
	grab_right_fork(philo, right);
	grab_left_fork(philo);
	ft_sleep(philo, 'e');
	philo->shared->forks[right] = 0;
	pthread_mutex_unlock(&philo->shared->fork_mutexes[right]);
	philo->shared->forks[philo->id] = 0;
	pthread_mutex_unlock(&philo->shared->fork_mutexes[philo->id]);
}

void	*routine(void *arg)
{
	t_philo *philo;
	int num_eating;

	num_eating = 0;
	philo = (t_philo *)arg;
	if (philo->id % 2 == 1)
		usleep(500);
	while ((philo->shared->eat_number == -1 || num_eating < philo->shared->eat_number))
	{
		if (philo->shared->number_philos != 1)
		{
			if (philo->id % 2 != 1)
				even_eating(philo);
			else
				odd_eating(philo);
		}
		num_eating++;
		ft_sleep(philo, 's');
		ft_sleep(philo, 't');
		if (should_stop(philo) == 1)
			break;
	}
	pthread_mutex_lock(&philo->full_mutex);
	philo->full = 1;
	pthread_mutex_unlock(&philo->full_mutex);
	return (NULL);
}