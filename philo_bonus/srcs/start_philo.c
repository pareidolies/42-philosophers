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
		{
			return (CHILDREN_ERROR);
		}
		else if (philo[i].pid == 0)
			philo_routine(philo[i]);
		i++;
	}
	return (0);
}

/*int	end_philo(t_all *all)
{
	int		i;
	t_philo	*philo;
	t_data	data;

	philo = all->philo;
	data = all->data;
	i = 0;
	if (philo)
		free(philo);
	return (0);
}*/

int	start_philo(t_all *all)
{
	int	error;
	int	pid;

	error = create_childrend(&all->data, all->philo);
	if (error)
		return (print_errors(error));
	usleep(SLEEP_TIME);
	gods_overseeing(&all->data, all->philo);
	pid = waitpid(-1, NULL, 0);
	while (pid > 0)
		pid = waitpid(-1, NULL, 0);
	return (0);
}
