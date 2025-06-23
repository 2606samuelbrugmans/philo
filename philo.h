#include <unistd.h>
#include <stdio.h>
#include <pthread.h>





typedef struct s_shared {

    pthread_t       monitor;
    int             *forks;
    int             time_to_die;
    int             time_to_eat;
    int             time_to_sleep;
    int             eat_number;
    int             number_philos;
    pthread_mutex_t *fork_mutexes
} t_shared;

typedef struct s_philo {
    int id;
    pthread_t thread;
    t_shared *shared;
} t_philo;
