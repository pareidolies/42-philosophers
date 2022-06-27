/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   thanatos_routine.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smostefa <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/11 16:51:10 by smostefa          #+#    #+#             */
/*   Updated: 2022/06/11 16:51:12 by smostefa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "../includes/philosophers.h"

int	thanatos(t_data *data, t_philo *philo)
{
	int	i;
	long	time_since_last_meal;
	long	timestamp;

	i = 0;
	while (i < data->nbr_philos)
	{
		time_since_last_meal = get_elapsed_time(data) - philo[i].last_meal;
		if (time_since_last_meal >= data->time_to_die)
		{
			data->is_it_the_end = 1;
			timestamp = get_elapsed_time(data);
			printf("\x1b[96m%-7ld %5d %23s\x1b[0m", timestamp, i + 1, DIE_MSSG);
			ft_putstr_fd_color(SAD_END, 1, ANSI_COLOR_LIGHT_RED);
			return (42);
		}
		i++;
	}
	return (0);
}

int    dyonisos(t_data	*data)
{
	if (data->are_full == data->nbr_philos)
	{
		data->is_it_the_end = 1;
		ft_putstr_fd_color(HAPPY_END, 1, ANSI_COLOR_LIGHT_CYAN);
		return (42);
	}
	return(0);
}

void	gods_overseeing(t_data *data, t_philo *philo)
{
	int		end;

	end = 0;
	while (1)
	{
		pthread_mutex_lock(&data->printing);
		end = dyonisos(data);
		if (end)
			return ((void)pthread_mutex_unlock(&data->printing));
		end = thanatos(data, philo);
		if (end)
			return ((void)pthread_mutex_unlock(&data->printing));
		pthread_mutex_unlock(&data->printing);
		usleep(1000); //for the CPU load
	}
}
