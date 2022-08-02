/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   gods_overseeing.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smostefa <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/11 16:51:10 by smostefa          #+#    #+#             */
/*   Updated: 2022/07/26 17:04:05 by smostefa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philosophers.h"

void	thanatos(t_philo *philo)
{
	long	time_since_last_meal;
	long	timestamp;

	time_since_last_meal = get_elapsed_time(philo->start_time) \
	- philo->last_meal;
	if (time_since_last_meal >= philo->time_to_die)
	{
		sem_wait(philo->data->printing);
		timestamp = get_elapsed_time(philo->start_time);
		printf("\e[0;34m%-7ld %5d %23s\x1b[0m", timestamp, philo->id, DIE_MSSG);
		ft_putstr_fd_color(SAD_END, 1, "\e[0;31m");
		exit(EXIT_SUCCESS);
		//sem_post(philo->data->end);
	}
}

void	dionysos(t_philo *philo)
{
	if (philo->meals_eaten == philo->need_to_eat + 1)
	{
		sem_wait(philo->data->printing);
		ft_putstr_fd_color(HAPPY_END, 1, "\e[0;32m");
		exit(EXIT_SUCCESS);
		//sem_post(philo->data->end);
	}
}

void	*gods_overseeing(void *arg)
{
	int		end;
	t_philo	*philo;

	philo = (t_philo *) arg;
	end = 0;
	while (1)
	{
		sem_wait(philo->data->death);
		dionysos(philo);
		thanatos(philo);
		sem_post(philo->data->death);
		usleep(SLEEP_TIME);
	}
}
