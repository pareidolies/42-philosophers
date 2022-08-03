/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   monitoring_loop.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smostefa <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/03 11:55:56 by smostefa          #+#    #+#             */
/*   Updated: 2022/08/03 11:56:00 by smostefa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philosophers.h"

int	monitoring_loop(t_data *data, t_philo *philo, int count)
{
	int	status;

	while (1)
	{
		waitpid(-1, &status, 0);
		if (WIFEXITED(status))
		{
			if (WEXITSTATUS(status) == SAD_EXIT)
			{
				end_philo(data, philo);
				return (SAD_EXIT);
			}
			else if (WEXITSTATUS(status) == HAPPY_EXIT)
			{
				if (count++ == data->nbr_philos)
				{
					ft_putstr_fd_color(HAPPY_END, 1, "\e[0;32m");
					end_philo(data, philo);
					return (SAD_EXIT);
				}
			}
		}
	}
	return (0);
}
