/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smostefa <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/08 10:32:07 by smostefa          #+#    #+#             */
/*   Updated: 2022/06/28 13:01:55 by smostefa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philosophers.h"

t_philo	*initialize_philo(t_data *data)
{
	t_philo	*philo;

	philo = malloc(sizeof(t_philo) * data->nbr_philos);
	if (!philo)
	{
		print_errors(MALLOC_ERROR);
		return (0);
	}
	data->start_time = gettimeofday_millisec() + (data->nbr_philos * 2);
	return (philo);
}

int	fill_philo(t_philo **philo, t_data *data)
{
	int	i;

	i = 0;
	while (i < data->nbr_philos)
	{
		(*philo)[i].id = i + 1;
		/*if (pthread_mutex_init(&((*philo)[i].right_fork), NULL))
		{
			free(*philo);
			return (MUTEX_ERROR);
		}*/
		(*philo)[i].data = data;
		(*philo)[i].need_to_eat = data->need_to_eat;
		(*philo)[i].time_to_die = data->time_to_die;
		(*philo)[i].time_to_eat = data->time_to_eat;
		(*philo)[i].time_to_sleep = data->time_to_sleep;
		(*philo)[i].meals_eaten = 0;
		(*philo)[i].last_meal = 0;
		/*if (i == data->nbr_philos - 1)
			(*philo)[i].left_fork = &((*philo)[0].right_fork);
		else
			(*philo)[i].left_fork = &((*philo)[i + 1].right_fork);*/
		i++;
	}
	return (0);
}

void	start_one_philo(t_data *data)
{
	data->start_time = gettimeofday_millisec();
	test_printer(FORK, data, 1);
	precise_usleep(data->time_to_die);
	test_printer(DIE, data, 1);
	ft_putstr_fd_color(SAD_END, 1, "\e[0;31m");
	return ;
}

int	initialize_semaphores(t_data *data)
{
	sem_unlink("forks");
	sem_unlink("printing");
	data->forks = sem_open("forks", O_CREAT, 0644, data->nbr_philos);
	data->printing = sem_open("printing", O_CREAT, 0644, 1);
	if (data->forks == SEM_FAILED || data->printing == SEM_FAILED)
		return (SEM_ERROR);
	return (0);
}

int	main(int argc, char **argv)
{
	t_all	all;
	int	error;

	error = 0;
	error = check_args(argc, argv);
	if (error)
		return (print_errors(error));
	all.data = parse_args(argc, argv);
	if (all.data.nbr_philos == 1)
	{
		start_one_philo(&all.data);
		return (0);
	}
	all.philo = initialize_philo(&all.data);
	if (!all.philo)
		return (PHILO_ERROR);
	error = fill_philo(&all.philo, &all.data);
	if (error)
		return (print_errors(error));
	error = initialize_semaphores(&all.data);
	if (error)
		return(print_errors(error));
	error = start_philo(&all);
	return (error);
}
