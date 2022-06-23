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

void    *thanatos_routine(void  *arg)
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
		}
 		pthread_mutex_unlock(&data->meals_mutex);
		precise_usleep(data->time_to_eat);
	}
	return(0);
}
