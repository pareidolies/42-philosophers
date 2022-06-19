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
		print_philo_state(FORK, philo->data, philo->id);
		pthread_mutex_unlock(&philo->data->printing);
		usleep(100000);
		//takes the second fork next to him
		if (philo->id == (philo->data->nbr_philos))
			pthread_mutex_lock(&philo->right_fork);
		else
			pthread_mutex_lock(philo->left_fork);
		pthread_mutex_lock(&philo->data->printing);
		print_philo_state(FORK, philo->data, philo->id);
		pthread_mutex_unlock(&philo->data->printing);
		usleep(100000);
		//since he has both forks in hand he starts eating
		pthread_mutex_lock(&philo->data->printing);
		print_philo_state(EAT, philo->data, philo->id);
		pthread_mutex_unlock(&philo->data->printing);
		precise_usleep(philo->data->time_to_eat);
		usleep(100000);
		//he drops both forks
		pthread_mutex_unlock(&philo->right_fork);
		pthread_mutex_unlock(philo->left_fork);
		usleep(100000);
		//he starts sleeping
		pthread_mutex_lock(&philo->data->printing);
		print_philo_state(SLEEP, philo->data, philo->id);
		pthread_mutex_unlock(&philo->data->printing);
		precise_usleep(philo->data->time_to_eat);
		usleep(100000);
		//he starts thinking
		pthread_mutex_lock(&philo->data->printing);
		print_philo_state(THINK, philo->data, philo->id);
		pthread_mutex_unlock(&philo->data->printing);
		usleep(100000);
	}
	return(0);
}
