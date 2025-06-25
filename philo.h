#include <unistd.h>
#include <stdio.h>
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
    pthread_mutex_t full_mutex;
    pthread_mutex_t *fork_mutexes;
} t_shared;

typedef struct s_philo {
    int id;
    pthread_t thread;
    unsigned long long current_time;
    int                 full;
    unsigned long long last_ate_time;
    t_shared *shared;
} t_philo;
int all_ate(t_philo *philos);
int monitor(void *arg);
int process(t_philo *philo);
void even_eating(t_philo philo);
void odd_eating(t_philo philo);
int routine(void *arg);
int init(char **argv, t_philo *philos, t_shared *shared);
void grab_left_fork(t_philo philo);
void grab_right_fork(t_philo philo);
void ft_sleep(t_philo philo, char *type);
unsigned long long get_time_ms(void);

