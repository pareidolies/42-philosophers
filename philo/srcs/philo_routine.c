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
		int	end;

		//he starts thinking
		pthread_mutex_lock(&philo->data->printing);
		end = test_printer(THINK, philo->data, philo->id);
		if (end)
		{
			pthread_mutex_unlock(&philo->data->printing);
			return;
		}
		pthread_mutex_unlock(&philo->data->printing);
		//continue
		ft_eat(philo);
}

void	ft_sleep(t_philo *philo)
{
		int	end;
		int duration;

		//he starts sleeping
		pthread_mutex_lock(&philo->data->printing);
		end = test_printer(SLEEP, philo->data, philo->id);
		if (end)
		{
			pthread_mutex_unlock(&philo->data->printing);
			return;
		}
		pthread_mutex_unlock(&philo->data->printing);
		duration = philo->data->time_to_sleep - (gettimeofday_millisec() - philo->offset);
		precise_usleep(philo->data->time_to_sleep);
		//continue
		ft_think(philo);
}

void	ft_eat(t_philo *philo)
{
		int	end;
		int duration;
		
		//since he has both forks in hands he starts eating
		pthread_mutex_lock(&philo->data->printing);
		end = test_printer(EAT, philo->data, philo->id);
		if (end)
		{
			pthread_mutex_unlock(&philo->data->printing);
			return;
		}
		pthread_mutex_unlock(&philo->data->printing);
		philo->last_meal = get_elapsed_time(philo->data);
		philo->meals_eaten++;
		duration = philo->data->time_to_eat - (gettimeofday_millisec() - philo->offset);
		precise_usleep(duration);
		philo->offset = gettimeofday_millisec();
		if (philo->meals_eaten == philo->need_to_eat)
		{
			pthread_mutex_lock(&philo->data->printing);
			philo->data->are_full++;
			pthread_mutex_unlock(&philo->data->printing);
		}
		//he drops both forks
		pthread_mutex_unlock(&philo->right_fork);
		pthread_mutex_unlock(philo->left_fork);
		//continue
		ft_sleep(philo);
}

void	ft_take_forks(t_philo *philo)
{
	int end;

	//takes the fork on the left
	pthread_mutex_lock(philo->left_fork);
	pthread_mutex_lock(&philo->data->printing);
	end = test_printer(FORK, philo->data, philo->id);
	if (end)
	{
		pthread_mutex_unlock(&philo->data->printing);
		pthread_mutex_unlock(philo->left_fork);
		return;
	}
	pthread_mutex_unlock(&philo->data->printing);
	//takes the fork second on the right
	pthread_mutex_lock(&philo->right_fork);
	philo->offset = gettimeofday_millisec();
	pthread_mutex_lock(&philo->data->printing);
	end = test_printer(FORK, philo->data, philo->id);
	if (end)
	{
		pthread_mutex_unlock(&philo->data->printing);
		pthread_mutex_unlock(&philo->right_fork);
		return;
	}
	pthread_mutex_unlock(&philo->data->printing);
	//continue
	ft_eat(philo);
}

void	*philo_routine(void  *arg)
{
	t_philo *philo;

	philo = (t_philo *)arg;
	wait_all_philos(philo->data->start_time);
	if (philo->id % 2 != 0)
		precise_usleep(philo->time_to_eat);
	ft_take_forks(philo);
	return(0);
}
