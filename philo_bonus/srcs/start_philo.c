/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   start_philo.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smostefa <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/11 16:47:21 by smostefa          #+#    #+#             */
/*   Updated: 2022/06/28 12:58:26 by smostefa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philosophers.h"

int	create_children(t_data *data, t_philo *philo)
{
	int	i;

	i = 0;
	while (i < data->nbr_philos)
	{
		philo[i].pid = fork();
		if (philo[i].pid == -1)
			return (CHILDREN_ERROR);
		else if (philo[i].pid == 0)
		{
			philo_routine(&philo[i]);
			exit (0);
		}
		i++;
	}
	return (0);
}

void	end_philo(t_data *data, t_philo *philo)
{
	int	i;

	i = 0;
	while (i < data->nbr_philos)
	{
		kill(philo[i].pid, SIGTERM);
		i++;
	}
	sem_close(data->forks);
	sem_close(data->printing);
	sem_unlink("forks");
	sem_unlink("printing");
	if (philo)
		free(philo);
}

int	start_philo(t_data *data, t_philo *philo)
{
	int	error;

	error = create_children(data, philo);
	if (error)
		return (print_errors(error));
	return (0);
}
