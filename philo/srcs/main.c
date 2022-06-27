/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smostefa <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/08 10:32:07 by smostefa          #+#    #+#             */
/*   Updated: 2022/06/08 12:18:42 by smostefa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philosophers.h"

t_philo	*initialize_info(t_data *data)
{
	int	i;
	t_philo	*philo;

	philo = malloc(sizeof(t_philo) * data->nbr_philos);
	if (!philo)
		return (0);
	i = 0;
	while (i < data->nbr_philos)
	{
		philo[i].id = i + 1;
		pthread_mutex_init(&(philo[i].right_fork), NULL);
		philo[i].data = data;
		philo[i].need_to_eat = data->need_to_eat;
		philo[i].time_to_die = data->time_to_die;
		philo[i].time_to_eat = data->time_to_eat;
		philo[i].time_to_sleep = data->time_to_sleep;
		philo[i].meals_eaten = 0;
		philo[i].last_meal = 0;
		if (i == data->nbr_philos - 1)
			philo[i].left_fork = &(philo[0].right_fork);
		else
			philo[i].left_fork = &(philo[i + 1].right_fork);
		i++;
	}
	data->start_time = gettimeofday_millisec() + (data->nbr_philos * 2);
	return (philo);
}

int	start_one_philo(t_data *data)
{
	data->start_time = gettimeofday_millisec();
	test_printer(FORK, data, 1);
	precise_usleep(data->time_to_die);
	test_printer(DIE, data, 1);
	ft_putstr_fd_color(SAD_END, 1, ANSI_COLOR_LIGHT_RED);
	return (0);
}

int main(int argc, char **argv)
{
	t_all	all;
	int	error;

	error = 0;
	error = check_args(argc, argv);
	if (error)
		return (print_errors(error));
	all.data = parse_args(argc, argv);
	//if (!all.data)
	//	return (print_errors(ARGS_ERROR));
	if (all.data.nbr_philos == 1)
	{
		error = start_one_philo(&all.data);
		return (print_errors(error));
	}
	all.philo = initialize_info(&all.data);
	if (!all.philo)
		return (print_errors(MALLOC_ERROR));
	error = start_philo(&all);
		return (0);
}
