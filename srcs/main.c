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

int	initialize_info(t_data	*data)
{
	int	i;

	data->philo = malloc(sizeof(t_philo) * data->nbr_philos);
	if (!data->philo)
		return (MALLOC_ERROR);
	gettimeofday(&data->start_time, NULL);
	pthread_mutex_init(&data->printing_mutex, NULL);
	i = 0;
	while (i < data->nbr_philos)
	{
		if (data->nbr_philos == 1)
			return (1); //ERROR MANAGEMENT TO DO BEFORE
		data->philo[i].id = i + 1;
		data->philo[i].nbr_philos = data->nbr_philos;
		data->philo[i].forks_in_hand = 0;
		data->philo[i].time_to_eat = data->time_to_eat;
		data->philo[i].time_to_sleep = data->time_to_sleep;
		pthread_mutex_init(&data->philo[i].right_fork, NULL);
		if (i == data->nbr_philos - 1)
			data->philo[i].left_fork = &data->philo[0].right_fork;
		else
			data->philo[i].left_fork = &data->philo[i + 1].right_fork;
		data->philo[i].printing = &data->printing_mutex;
		
		i++;
	}
	return (0);
}

int main(int argc, char **argv)
{
	t_data	data;
	int	error;

	error = 0;
	error = check_args(argc, argv);
	if (error)
		return (print_errors(error));
	error = parse_args(argc, argv, &data);
	if (error)
		return (print_errors(error));
	error = initialize_info(&data);
	if (error)
		return (print_errors(error));
	error = start_philo(&data);
		return (0);
}
