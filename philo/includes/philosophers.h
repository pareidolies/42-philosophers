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
# include <stdlib.h>
# include <sys/time.h>
# include <pthread.h>
# include <stdio.h>

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
# define MUTEX_ERROR 204
# define PHILO_ERROR 205

# define MALLOC_MSSG "Error : A malloc error occured.\n"
# define THREAD_MSSG "Error : A thread error occured.\n"
# define MUTEX_MSSG "Error : A mutex error occured.\n"

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

typedef struct s_data
{
	long			nbr_philos;
	long			time_to_die;
	long			time_to_eat;
	long			time_to_sleep;
	long			need_to_eat;
	long			start_time;
	pthread_mutex_t	printing;
	int				someone_died;
	long			are_full;
	int				is_it_the_end;
}		t_data;

typedef struct s_philo
{
	int				id;
	long			need_to_eat;
	long			time_to_die;
	long			time_to_eat;
	long			time_to_sleep;
	long			offset;
	pthread_t		thread;
	pthread_mutex_t	right_fork;
	pthread_mutex_t	*left_fork;
	long			meals_eaten;
	long			last_meal;
	t_data			*data;
}		t_philo;

typedef struct s_all
{
	t_data	data;
	t_philo	*philo;
}		t_all;

//main.c
void	start_one_philo(t_data *data);
int		fill_philo(t_philo **philo, t_data *data);
t_philo	*initialize_philo(t_data *data);

//handle_args.c
int		only_positive_digit(char *str);
int		check_args(int argc, char **argv);
t_data	parse_args(int argc, char **argv);

//print_messages.c
void	print_manual(void);
int		print_errors(int error);
int		test_printer(int state, t_data *data, int id);

//libft_utils.c
void	ft_putchar_fd(char c, int fd);
void	ft_putstr_fd_color(char *str, int fd, char *color);

//start_philo.c
int		start_philo(t_all *all);
void	destroy_and_free(t_data *data, t_philo *philo);
void	ft_putstr_fd(char *s, int fd);
int		ft_atoi_int(const char *str);
long	ft_atoi(const char *str);

//philo_routine.c
void	ft_think(t_philo *philo);
void	ft_sleep(t_philo *philo);
void	ft_eat(t_philo *philo);
void	ft_take_second_fork(t_philo *philo);
void	ft_take_first_fork(t_philo *philo);
void	*philo_routine(void *arg);

//gods_overseing.c
int		thanatos(t_data *data, t_philo *philo);
int		dyonisos(t_data	*data);
void	gods_overseeing(t_data *data, t_philo *philo);

//timeline_utils.c
long	get_elapsed_time(t_data *data);
long	gettimeofday_millisec(void);
void	precise_usleep(int duration);
void	wait_all_philos(int start_time);

#endif
