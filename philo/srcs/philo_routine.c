/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_routine.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smostefa <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/11 16:51:25 by smostefa          #+#    #+#             */
/*   Updated: 2022/07/26 16:42:02 by smostefa         ###   ########.fr       */
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
	if ((philo->nbr_philos % 2) != 0)
		wait_before_taking_first_fork(philo);
	else
		ft_take_first_fork(philo);
}

void	ft_sleep(t_philo *philo)
{
	int		end;

	pthread_mutex_lock(&philo->data->printing);
	end = test_printer(SLEEP, philo->data, philo->id);
	if (end)
	{
		pthread_mutex_unlock(&philo->data->printing);
		return ;
	}
	pthread_mutex_unlock(&philo->data->printing);
	precise_usleep(philo->data->time_to_sleep - \
	(gettimeofday_millisec() - philo->offset), philo->data);
	ft_think(philo);
}

void	ft_eat(t_philo *philo)
{
	int		end;

	pthread_mutex_lock(&philo->data->printing);
	end = test_printer(EAT, philo->data, philo->id);
	if (end)
	{
		pthread_mutex_unlock(philo->left_fork);
		pthread_mutex_unlock(&philo->right_fork);
		return ((void)pthread_mutex_unlock(&philo->data->printing));
	}
	philo->last_meal = get_elapsed_time(philo->start_time);
	philo->meals_eaten++;
	pthread_mutex_unlock(&philo->data->printing);
	precise_usleep(philo->time_to_eat - \
	(gettimeofday_millisec() - philo->offset), philo->data);
	philo->offset = gettimeofday_millisec();
	if (philo->meals_eaten == philo->need_to_eat)
	{
		pthread_mutex_lock(&philo->data->printing);
		philo->data->are_full++;
		pthread_mutex_unlock(&philo->data->printing);
	}
	pthread_mutex_unlock(philo->left_fork);
	pthread_mutex_unlock(&philo->right_fork);
	ft_sleep(philo);
}

void	ft_take_second_fork(t_philo *philo)
{
	int	end;

	if ((philo->id % 2) == 0)
		pthread_mutex_lock(&philo->right_fork);
	else
		pthread_mutex_lock(philo->left_fork);
	philo->offset = gettimeofday_millisec();
	pthread_mutex_lock(&philo->data->printing);
	end = test_printer(FORK, philo->data, philo->id);
	if (end)
	{
		pthread_mutex_unlock(&philo->data->printing);
		pthread_mutex_unlock(&philo->right_fork);
		pthread_mutex_unlock(philo->left_fork);
		return ;
	}
	pthread_mutex_unlock(&philo->data->printing);
	ft_eat(philo);
}

void	ft_take_first_fork(t_philo *philo)
{
	int	end;

	if ((philo->id % 2) == 0)
		pthread_mutex_lock(philo->left_fork);
	else
		pthread_mutex_lock(&philo->right_fork);
	pthread_mutex_lock(&philo->data->printing);
	end = test_printer(FORK, philo->data, philo->id);
	if (end)
	{
		pthread_mutex_unlock(&philo->data->printing);
		if ((philo->id % 2) == 0)
			pthread_mutex_unlock(philo->left_fork);
		else
			pthread_mutex_unlock(&philo->right_fork);
		return ;
	}
	pthread_mutex_unlock(&philo->data->printing);
	ft_take_second_fork(philo);
}
