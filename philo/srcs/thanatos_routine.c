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

void	thanatos_routine(t_data *data, t_philo *philo)
{
	//t_all	*all = (t_all *)arg;
	//t_philo	*philo = all->philo;
	//t_data	data = all->data;
	int	i;
	int	time_since_last_meal;
	int	timestamp;

	i = 0;
	while (1)
	{
		pthread_mutex_lock(&data->life_mutex);
		time_since_last_meal = get_elapsed_time(data) - philo[i].last_meal;
		if (time_since_last_meal >= data->time_to_die)
		{
			data->is_it_the_end = 1;
			timestamp = get_elapsed_time(data);
			printf("%d %d %s\n", timestamp, i + 1, DIE_MSSG);
			pthread_mutex_unlock(&data->life_mutex);
			break;
		}
		else
		{
			i = (i + 1) % data->nbr_philos;
			pthread_mutex_unlock(&data->life_mutex);
			precise_usleep(9); //for the CPU load
		}
	}
	//return (0);
}

void    *dyonisos_routine(void  *arg)
{
	t_data  *data;

	data = (t_data *)arg;
	while (1)
	{    
		pthread_mutex_lock(&data->meals_mutex);
		if (data->are_full == data->nbr_philos)
		{
			pthread_mutex_lock(&data->end_mutex);
			data->is_it_the_end = 1;
			pthread_mutex_unlock(&data->end_mutex);
			printf("philosophers have eaten enough !\n");
			break;
		}
		else
		{
 			pthread_mutex_unlock(&data->meals_mutex);
			precise_usleep(data->time_to_eat);
		}
	}
	return(0);
}
