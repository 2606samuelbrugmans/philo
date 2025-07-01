/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   big_meower.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbrugman <sbrugman@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/01 14:37:29 by sbrugman          #+#    #+#             */
/*   Updated: 2025/07/01 14:53:46 by sbrugman         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int cleanup(t_shared *shared, t_philo *philos)
{
    int i;

    if (shared->number_philos > 0 && philos)
    {
        i = 0;
        while (i < shared->number_philos)
        {
            pthread_mutex_destroy(&philos[i].last_ate_protec);
            pthread_mutex_destroy(&philos[i].full_mutex);
            if (shared->fork_mutexes)
                pthread_mutex_destroy(&shared->fork_mutexes[i]);
            i++;
        }
    }
    if (shared->fork_mutexes)
        free(shared->fork_mutexes);
    if (shared->forks)
        free(shared->forks);
    if (philos)
        free(philos);
    pthread_mutex_destroy(&shared->stop_mutex);
    return (0);
}
int is_valid(int argc,t_shared *shared)
{
    if (shared->eat_number < 0 && argc == 6)
        return (-1);
    if (shared->time_to_die < 0)
        return (-1);
    if (shared->time_to_sleep < 0)
        return (-1);
    if (shared->time_to_eat < 0 )
        return (-1);
    return (0);
}
int who_right(t_philo *philo)
{
    int right;

    right = philo->id + 1;
    if (philo->id == philo->shared->number_philos - 1)
        right = 0;
    return (right);
}