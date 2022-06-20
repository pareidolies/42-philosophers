/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_routine.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smostefa <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/11 16:51:25 by smostefa          #+#    #+#             */
/*   Updated: 2022/06/11 16:51:26 by smostefa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "../includes/philosophers.h"

void *philo_routine(void  *arg)
{
	t_philo *philo;

	philo = (t_philo *)arg;
	while (1) //philo->data->everybody_is_alive
	{
		//takes the lower-numbered fork first
		if (philo->id == (philo->data->nbr_philos))
			pthread_mutex_lock(philo->left_fork);
		else
			pthread_mutex_lock(&philo->right_fork);
		pthread_mutex_lock(&philo->data->printing);
		test_printer(FORK, philo->data, philo->id);
		pthread_mutex_unlock(&philo->data->printing);
		//takes the second fork next to him
		if (philo->id == (philo->data->nbr_philos))
			pthread_mutex_lock(&philo->right_fork);
		else
			pthread_mutex_lock(philo->left_fork);
		pthread_mutex_lock(&philo->data->printing);
		test_printer(FORK, philo->data, philo->id);
		pthread_mutex_unlock(&philo->data->printing);
		//since he has both forks in hands he starts eating
		pthread_mutex_lock(&philo->data->printing);
		test_printer(EAT, philo->data, philo->id);
		pthread_mutex_unlock(&philo->data->printing);
		philo->meals_eaten++;
		if (philo->meals_eaten == philo->need_to_eat)
		{
			pthread_mutex_lock(&philo->data->meals_mutex);
			philo->data->are_full++;
			pthread_mutex_unlock(&philo->data->meals_mutex);
		}
		precise_usleep(philo->data->time_to_eat);
		//he drops both forks
		pthread_mutex_unlock(&philo->right_fork);
		pthread_mutex_unlock(philo->left_fork);
		//he starts sleeping
		pthread_mutex_lock(&philo->data->printing);
		test_printer(SLEEP, philo->data, philo->id);
		pthread_mutex_unlock(&philo->data->printing);
		precise_usleep(philo->data->time_to_sleep);
		//he starts thinking
		pthread_mutex_lock(&philo->data->printing);
		test_printer(THINK, philo->data, philo->id);
		pthread_mutex_unlock(&philo->data->printing);
	}
	return(0);
}
