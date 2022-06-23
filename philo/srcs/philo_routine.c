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

void	ft_think(t_philo *philo)
{
		//he starts thinking
		pthread_mutex_lock(&philo->data->printing);
		test_printer(THINK, philo->data, philo->id);
		pthread_mutex_unlock(&philo->data->printing);
		//check if it's the end, if not continue
		pthread_mutex_lock(&philo->data->end_mutex);
		if(!philo->data->is_it_the_end)
		{
			pthread_mutex_unlock(&philo->data->end_mutex);
			ft_eat(philo);
		}
		else
			pthread_mutex_unlock(&philo->data->end_mutex);
}

void	ft_sleep(t_philo *philo)
{
		//he starts sleeping
		pthread_mutex_lock(&philo->data->printing);
		test_printer(SLEEP, philo->data, philo->id);
		pthread_mutex_unlock(&philo->data->printing);
		precise_usleep(philo->data->time_to_sleep);
		//check if it's the end, if not continue
		pthread_mutex_lock(&philo->data->end_mutex);
		if(!philo->data->is_it_the_end)
		{
			pthread_mutex_unlock(&philo->data->end_mutex);
			ft_think(philo);
		}
		else
			pthread_mutex_unlock(&philo->data->end_mutex);
}

void	ft_eat(t_philo *philo)
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
		philo->last_meal = get_elapsed_time(philo->data);
		philo->meals_eaten++;
		precise_usleep(philo->data->time_to_eat);
		if (philo->meals_eaten == philo->need_to_eat)
		{
			pthread_mutex_lock(&philo->data->meals_mutex);
			philo->data->are_full++;
			pthread_mutex_unlock(&philo->data->meals_mutex);
		}
		//he drops both forks
		pthread_mutex_unlock(&philo->right_fork);
		pthread_mutex_unlock(philo->left_fork);
		//check if it's the end, if not continue
		pthread_mutex_lock(&philo->data->end_mutex);
		if(!philo->data->is_it_the_end)
		{
			pthread_mutex_unlock(&philo->data->end_mutex);
			ft_sleep(philo);
		}
		else
			pthread_mutex_unlock(&philo->data->end_mutex);
}

void	*philo_routine(void  *arg)
{
	t_philo *philo;

	philo = (t_philo *)arg;
	ft_eat(philo);
	return(0);
}
