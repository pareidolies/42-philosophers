/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smostefa <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/08 12:13:44 by smostefa          #+#    #+#             */
/*   Updated: 2022/06/08 12:13:46 by smostefa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILOSOPHERS_H

# define PHILOSOPHERS_H

# include <unistd.h>
# include <stdlib.h>
# include <sys/time.h>
# include <pthread.h>
# include <stdio.h>

# define ARGS_ERROR 1
# define MALLOC_ERROR 2

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

# define FORK_MSSG "has taken a fork\n"
# define EAT_MSSG "is eating\n"
# define SLEEP_MSSG "is sleeping\n"
# define THINK_MSSG "is thinking\n"
# define DIE_MSSG "died\n"
# define SLEEP_TIME 200
# define PRECISE_SLEEP_TIME 100

typedef struct	s_data
{
	int				nbr_philos;
	int				time_to_die;
	int				time_to_eat;
	int				time_to_sleep;
	int				need_to_eat;
	struct timeval	start_time;
	pthread_t		thanatos;
	int				everybody_is_alive;		
	pthread_mutex_t	printing;
	pthread_mutex_t	death_thread;
	int				someone_died;
	pthread_mutex_t	meals_thread;
	int				are_full;
}		t_data;

typedef struct	s_philo
{
	int				id;
	int				need_to_eat;
	int				time_to_die;
	pthread_t		thread;
	pthread_mutex_t	right_fork;
	pthread_mutex_t	*left_fork;
	int				meals_eaten;
	struct timeval	last_eaten;				
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
void    ft_putnbr_fd_color(int n, int fd, char *color);
void    ft_putnbr_fd(int n, int fd);
int     ft_atoi(const char *str);

//start_philo.c
int	start_philo(t_all *all);

//philo_routine.c
void*    philo_routine(void  *arg);

//thanatos_routine.c
void*    thanatos_routine(void  *arg);

//timeline_utils.c
int get_elapsed_time(t_data *data);
void	precise_usleep(int  duration);

//print_messages.c
void	print_philo_state(int state, t_data *data, int id);
void	test_printer(int state, t_data *data, int id);

#endif