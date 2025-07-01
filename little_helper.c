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
