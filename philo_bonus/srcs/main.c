/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smostefa <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/08 10:32:07 by smostefa          #+#    #+#             */
/*   Updated: 2022/07/26 17:03:44 by smostefa         ###   ########.fr       */
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
		(*philo)[i].data = data;
		(*philo)[i].need_to_eat = data->need_to_eat;
		(*philo)[i].time_to_die = data->time_to_die;
		(*philo)[i].time_to_eat = data->time_to_eat;
		(*philo)[i].time_to_sleep = data->time_to_sleep;
		(*philo)[i].nbr_philos = data->nbr_philos;
		(*philo)[i].meals_eaten = 0;
		(*philo)[i].last_meal = 0;
		(*philo)[i].start_time = data->start_time;
		i++;
	}
	return (0);
}

void	start_one_philo(t_data *data)
{
	data->start_time = gettimeofday_millisec();
	test_printer(FORK, data->start_time, 1);
	precise_usleep(data->time_to_die);
	test_printer(DIE, data->start_time, 1);
	ft_putstr_fd_color(SAD_END, 1, "\e[0;31m");
	exit(EXIT_SUCCESS);
}

int	initialize_semaphores(t_data *data)
{
	sem_unlink("forks");
	sem_unlink("printing");
	sem_unlink("end");
	sem_unlink("death");
	data->forks = sem_open("forks", O_CREAT, 0644, data->nbr_philos);
	data->printing = sem_open("printing", O_CREAT, 0644, 1);
	data->end = sem_open("end", O_CREAT, 0644, 1);
	data->death = sem_open("death", O_CREAT, 0644, 1);
	if (data->forks == SEM_FAILED || data->printing == SEM_FAILED
		|| data->end == SEM_FAILED || data->death == SEM_FAILED)
		return (SEM_ERROR);
	return (0);
}

int	main(int argc, char **argv)
{
	t_all	all;
	int		error;

	error = check_args(argc, argv);
	if (error)
		return (print_errors(error));
	all.data = parse_args(argc, argv);
	if (all.data.nbr_philos == 1)
		start_one_philo(&all.data);
	all.philo = initialize_philo(&all.data);
	if (!all.philo)
		return (PHILO_ERROR);
	error = fill_philo(&all.philo, &all.data);
	if (error)
		return (print_errors(error));
	error = initialize_semaphores(&all.data);
	if (error)
		return (print_errors(error));
	//sem_wait(all.data.end);
	error = start_philo(&all.data, all.philo);
	while(waitpid(-1, NULL, 0) > 0)
		;
	//sem_wait(all.data.end);
	printf("\ncoucou\n");
	end_philo(&all.data, all.philo);
	return (error);
}
