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
	int	time_since_last_meal;
	int	timestamp;

	i = 0;
	while (i < data->nbr_philos)
	{
		pthread_mutex_lock(&data->life_mutex);
		time_since_last_meal = get_elapsed_time(data) - philo[i].last_meal;
		if (time_since_last_meal >= data->time_to_die)
		{
			data->is_it_the_end = 1;
			timestamp = get_elapsed_time(data);
			printf("%d %d %s\n", timestamp, i + 1, DIE_MSSG);
			pthread_mutex_unlock(&data->life_mutex);
			return (42);
		}
		i++;
		pthread_mutex_unlock(&data->life_mutex);
	}
	return (0);
}

int    dyonisos(t_data	*data)
{
	pthread_mutex_lock(&data->meals_mutex);
	if (data->are_full == data->nbr_philos)
	{
		pthread_mutex_lock(&data->end_mutex);
		data->is_it_the_end = 1;
		pthread_mutex_unlock(&data->end_mutex);
		printf("philosophers have eaten enough !\n");
		return (42);
	}
 	pthread_mutex_unlock(&data->meals_mutex);
	return(0);
}

void	gods_overseeing(t_data *data, t_philo *philo)
{
	int		end;

	end = 0;
	while (1)
	{
		end = dyonisos(data);
		if (end)
			return;
		end = thanatos(data, philo);
		if (end)
			return;
		usleep(1000); //for the CPU load
	}
}