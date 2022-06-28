/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_routine.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smostefa <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/11 16:51:25 by smostefa          #+#    #+#             */
/*   Updated: 2022/06/28 12:08:14 by smostefa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philosophers.h"

void	ft_think(t_philo *philo)
{
	int	end;

	pthread_mutex_lock(&philo->data->printing);
	end = test_printer(THINK, philo->data, philo->id);
	if (end)
	{
		pthread_mutex_unlock(&philo->data->printing);
		return ;
	}
	pthread_mutex_unlock(&philo->data->printing);
	ft_take_forks(philo);
}

void	ft_sleep(t_philo *philo)
{
	int		end;
	long	duration;

	pthread_mutex_lock(&philo->data->printing);
	end = test_printer(SLEEP, philo->data, philo->id);
	if (end)
	{
		pthread_mutex_unlock(&philo->data->printing);
		return ;
	}
	pthread_mutex_unlock(&philo->data->printing);
	if (philo->time_to_die > philo->time_to_sleep)
		duration = philo->data->time_to_sleep;
	else
		duration = philo->data->time_to_die;
	precise_usleep(duration - (gettimeofday_millisec() - philo->offset));
	ft_think(philo);
}

void	ft_eat(t_philo *philo)
{
	int		end;
	long	duration;

	pthread_mutex_lock(&philo->data->printing);
	end = test_printer(EAT, philo->data, philo->id);
	if (end)
		return ((void)pthread_mutex_unlock(&philo->data->printing));
	philo->last_meal = get_elapsed_time(philo->data);
	pthread_mutex_unlock(&philo->data->printing);
	philo->meals_eaten++;
	if (philo->time_to_die > philo->time_to_eat)
		duration = philo->time_to_eat;
	else
		duration = philo->time_to_die;
	precise_usleep(duration - (gettimeofday_millisec() - philo->offset));
	philo->offset = gettimeofday_millisec();
	if (philo->meals_eaten == philo->need_to_eat)
	{
		pthread_mutex_lock(&philo->data->printing);
		philo->data->are_full++;
		pthread_mutex_unlock(&philo->data->printing);
	}
	pthread_mutex_unlock(&philo->right_fork);
	pthread_mutex_unlock(philo->left_fork);
	ft_sleep(philo);
}

void	ft_take_forks(t_philo *philo)
{
	int	end;

	pthread_mutex_lock(philo->left_fork);
	pthread_mutex_lock(&philo->data->printing);
	end = test_printer(FORK, philo->data, philo->id);
	if (end)
	{
		pthread_mutex_unlock(&philo->data->printing);
		pthread_mutex_unlock(philo->left_fork);
		return ;
	}
	pthread_mutex_unlock(&philo->data->printing);
	pthread_mutex_lock(&philo->right_fork);
	philo->offset = gettimeofday_millisec();
	pthread_mutex_lock(&philo->data->printing);
	end = test_printer(FORK, philo->data, philo->id);
	if (end)
	{
		pthread_mutex_unlock(&philo->data->printing);
		pthread_mutex_unlock(&philo->right_fork);
		return ;
	}
	pthread_mutex_unlock(&philo->data->printing);
	ft_eat(philo);
}

void	*philo_routine(void *arg)
{
	t_philo	*philo;

	philo = (t_philo *)arg;
	wait_all_philos(philo->data->start_time);
	if (philo->id % 2 != 0)
		precise_usleep(philo->time_to_eat);
	ft_take_forks(philo);
	return (0);
}
