/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smostefa <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/08 12:13:44 by smostefa          #+#    #+#             */
/*   Updated: 2022/06/28 11:46:41 by smostefa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILOSOPHERS_H

# define PHILOSOPHERS_H

# include <unistd.h>
# include <semaphore.h>
# include <stdlib.h>
# include <pthread.h>
# include <sys/time.h>
# include <stdio.h>
# include <signal.h>
# include <fcntl.h>
# include <sys/stat.h>

# define ANSI_COLOR_LIGHT_BLUE		"\x1b[94m"
# define ANSI_COLOR_LIGHT_WHITE		"\x1b[97m"
# define ANSI_COLOR_LIGHT_RED		"\x1b[91m"
# define ANSI_COLOR_LIGHT_GREEN		"\x1b[92m"
# define ANSI_COLOR_LIGHT_YELLOW		"\x1b[93m"
# define ANSI_COLOR_LIGHT_PURPLE		"\x1b[95m"
# define ANSI_COLOR_LIGHT_CYAN		"\x1b[96m"
# define ANSI_COLOR_RESET		"\x1b[0m"

# define FORK 101
# define EAT 102
# define SLEEP 103
# define THINK 104
# define DIE 105

# define INT_MAX 2147483647

# define ARGS_ERROR 201
# define MALLOC_ERROR 202
# define THREAD_ERROR 203
# define SEM_ERROR 204
# define PHILO_ERROR 205
# define CHILDREN_ERROR 206

# define MALLOC_MSSG "Error : A malloc error occured.\n"
# define THREAD_MSSG "Error : A thread error occured.\n"
# define SEM_MSSG "Error : A semaphore error occured.\n"

# define FORK_MSSG "has taken a fork\n"
# define EAT_MSSG "is eating\n"
# define SLEEP_MSSG "is sleeping\n"
# define THINK_MSSG "is thinking\n"
# define DIE_MSSG "died\n"

# define M1 "\n----------------------     MANUAL     ----------------------\n\n"
# define M2 "./philo nbr_of_philos time_to_die time_to_eat time_to_sleep\n"
# define M3 "optional : number_of_time_each_philo_must_eat\n\n"


# define HAPPY_END "End of dinner : Philosophers have eaten enough !\n"
# define SAD_END "End of dinner : A philosopher died of starvation.\n"

# define SLEEP_TIME 2000
# define PRECISE_SLEEP_TIME 100

typedef struct	s_data
{
	long				nbr_philos;
	long				time_to_die;
	long				time_to_eat;
	long				time_to_sleep;
	long				need_to_eat;
	long				start_time;
	int				someone_died;
	long				are_full;
	int				is_it_the_end;
	sem_t				*forks;
	sem_t				*printing;
	sem_t				*end;
	sem_t				*death;
}		t_data;

typedef struct	s_philo
{
	int				id;
	pid_t				pid;
	long				time_to_die;
	long				time_to_eat;
	long				time_to_sleep;
	long				need_to_eat;
	long				start_time;
	long				offset;
	pthread_t		thread;
	long				meals_eaten;
	long				last_meal;
	t_data			*data;
}		t_philo;

typedef struct	s_all
{
	t_data	data;
	t_philo	*philo;
}		t_all;

//main.c


//handle_args.c
t_data     parse_args(int argc, char **argv);
int check_args(int argc, char **argv);
int is_positive_nbr(char *str);

//print_error.c
void    print_manual(void);
int     print_errors(int error);

//libft_utils.c
void    ft_putstr_fd_color(char *str, int fd, char *color);
void    ft_putstr_fd(char *s, int fd);
long     ft_atoi(const char *str);
int	ft_atoi_int(const char *str);

//start_philo.c
int	create_children(t_data *data, t_philo *philo);
int	start_philo(t_data *data, t_philo *philo);
void	end_philo(t_data *data, t_philo *philo);

//philo_routine.c
void	philo_routine(t_philo *philo);
void	ft_think(t_philo *philo);
void	ft_sleep(t_philo *philo);
void	ft_eat(t_philo *philo);
void	ft_take_forks(t_philo *philo);

//thanatos_routine.c
void	thanatos(t_philo *philo);
void	dyonisos(t_philo *philo);
void	*gods_overseeing(void *arg);

//timeline_utils.c
long get_elapsed_time(long start_time);
void	precise_usleep(int  duration);
long	gettimeofday_millisec(void);
void	wait_all_philos(int start_time);

//print_messages.c
int	test_printer(int state, long start_time, int id);

#endif
