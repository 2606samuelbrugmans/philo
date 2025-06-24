#include "philo.h"

void grab_left_fork(t_philo philo)
{
    pthread_mutex_lock(philo.shared->fork_mutexes[philo.id]);
    philo.shared->forks[philo.id] = 1;
}
void grab_right_fork(t_philo philo)
{
    if (philo.id != philo.shared->number_philos - 1)
    {
        pthread_mutex_lock(philo.shared->fork_mutexes[philo.id + 1]);
        philo.shared->forks[philo.id + 1] = 1;
    }
    else 
    {
        pthread_mutex_lock(philo.shared->fork_mutexes[0]);
        philo.shared->forks[0] = 1;
    }
}
void ft_sleep(t_philo philo, char *type)
{
    philo.current_time = get_time_ms();
    philo.current_time -= philo.shared->start_time;
    if (type == "eat")
    {
        printf("%llu philo %d is eating", philo.current_time,  philo.id);
        usleep(1000 * philo.shared->time_to_eat);
        pthread_mutex_lock(philo.last_ate_time);
        philo.last_ate_time = get_time_ms();
        pthread_mutex_unlock(philo.last_ate_time);
    }
    if (type == "sleep")
    {
        printf("%llu philo %d is sleeping", philo.current_time,  philo.id);
        usleep(1000 * philo.shared->time_to_sleep);
    }
}
unsigned long long get_time_ms(void)
{
    struct timeval tv;
    gettimeofday(&tv, NULL);
    return (tv.tv_sec * 1000L) + (tv.tv_usec / 1000);
}
