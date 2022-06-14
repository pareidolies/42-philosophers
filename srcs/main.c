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

int	initialize_info(t_philo **philo, t_data *data)
{
	int	i;

	philo = malloc(sizeof(t_philo) * data->nbr_philos);
	if (!philo)
		return (MALLOC_ERROR);
	i = 0;
	while (i < data->nbr_philos)
	{
		if (data->nbr_philos == 1)
			return (1); //ERROR MANAGEMENT TO DO BEFORE
		philo[i]->id = i + 1;
		pthread_mutex_init(&(philo[i]->right_fork), NULL);
		if (i == data->nbr_philos - 1)
			philo[i]->left_fork = &(philo[0]->right_fork);
		else
			philo[i]->left_fork = &(philo[i + 1]->right_fork);
		i++;
	}
	pthread_mutex_init(&data->printing, NULL);
	data->everybody_is_alive = 1;
	return (0);
}

int main(int argc, char **argv)
{
	t_data	data;
	t_philo	*philo;
	int	error;

	error = 0;
	error = check_args(argc, argv);
	if (error)
		return (print_errors(error));
	error = parse_args(argc, argv, &data);
	if (error)
		return (print_errors(error));
	error = initialize_info(&philo, &data);
	if (error)
		return (print_errors(error));
	//wait for everybody to be ready
	gettimeofday(&(data.start_time), NULL);
	error = start_philo(&philo, &data);
		return (0);
}
