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
	i = 0;
	while (i < data->nbr_philos)
	{
		data->philo[i].id = i;
		data->philo[i].right_fork = NULL;
		pthread_mutex_init(&data->philo[i].left_fork, NULL);
		if (data->nbr_philos == 1)
			return (1);
		if (i == data->nbr_philos - 1)
			data->philo[i].right_fork = &data->philo[0].left_fork;
		else
			data->philo[i].right_fork = &data->philo[i + 1].left_fork;
		i++;
	}
	return (1);
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
	/*error = initialize_info(&data);
	if (error)
		return (print_errors(error));
	error = start_philo(&data);*/
		return (0);
}
