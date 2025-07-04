#ifndef PHILO_H
#define PHILO_H

#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <sys/time.h>

typedef struct s_shared {

    pthread_t       monitor;
    int             *forks;
    int             time_to_die;
    int             time_to_eat;
    int             time_to_sleep;
    int             eat_number;
    int             number_philos;
    unsigned long long start_time;
    pthread_mutex_t stop_mutex;
    pthread_mutex_t *fork_mutexes;
    int             stop;
} t_shared;

typedef struct s_philo {
    int id;
    int right;
    pthread_t thread;
    pthread_mutex_t     full_mutex;
    pthread_mutex_t last_ate_protec;
    unsigned long long current_time;
    int                 full;
    unsigned long long last_ate_time;
    t_shared *shared;
} t_philo;

int should_stop(t_philo *philo);
int anybody_die(t_philo *philos);
int is_valid(int argc, t_shared *shared);
int who_right(t_philo *philo);
void	sleep_fair(t_philo *philo);

int all_ate(t_philo *philos);
void *monitor(void *arg);
int process(t_philo *philo);
void even_eating(t_philo *philo);
void odd_eating(t_philo *philo);
void *routine(void *arg);
int init_shared(int argc, char **argv, t_shared *shared);
int init_philos(t_philo **philos, t_shared *shared);
int cleanup(t_shared *shared, t_philo *philos);

void grab_left_fork(t_philo *philo);
void grab_right_fork(t_philo *philo, int right);
void ft_sleep(t_philo *philo, char type);
unsigned long long get_time_ms(void);
int is_digit(char c);
int is_space(char c);
int ft_atoi(const char *str);
int thread_create(t_philo *philo);
void args_create(t_shared *shared, int argc, char **argv);
void death(t_philo *philo, unsigned long long time, int index);

#endif 

