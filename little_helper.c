#include 	"philo.h"

void death(t_philo *philo, unsigned long long time, int index)
{
	pthread_mutex_unlock(&philo[index].last_ate_protec);
	time -= philo->shared->start_time;
	printf("%llu %d died\n", time, philo->id);
	pthread_mutex_lock(&philo->shared->stop_mutex);
	philo->shared->stop = 1;
	pthread_mutex_unlock(&philo->shared->stop_mutex);
}
void	sleep_fair(t_philo *philo)
{
	if (philo->shared->number_philos % 2 == 1 && philo->shared->time_to_eat 
	== philo->shared->time_to_sleep)
		usleep((1000 * philo->shared->time_to_eat
			- philo->shared->time_to_sleep) + 500);
}