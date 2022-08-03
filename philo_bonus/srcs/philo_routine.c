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
	sem_wait(philo->data->printing);
	test_printer(THINK, philo->start_time, philo->id);
	sem_post(philo->data->printing);
	if ((philo->nbr_philos % 2) != 0)
		wait_before_taking_forks(philo);
	else
		ft_take_forks(philo);
}

void	ft_sleep(t_philo *philo)
{
	long	duration;

	sem_wait(philo->data->printing);
	test_printer(SLEEP, philo->start_time, philo->id);
	sem_post(philo->data->printing);
	duration = philo->data->time_to_sleep;
	precise_usleep(duration - (gettimeofday_millisec() - philo->offset));
	ft_think(philo);
}

void	ft_eat(t_philo *philo)
{
	long	duration;

	sem_wait(philo->data->printing);
	test_printer(EAT, philo->start_time, philo->id);
	philo->last_meal = get_elapsed_time(philo->start_time);
	philo->meals_eaten++;
	duration = philo->time_to_eat;
	sem_post(philo->data->printing);
	precise_usleep(duration - (gettimeofday_millisec() - philo->offset));
	philo->offset = gettimeofday_millisec();
	sem_wait(philo->data->printing);
	sem_post(philo->data->forks);
	philo->forks_in_hands--;
	sem_post(philo->data->forks);
	philo->forks_in_hands--;
	sem_post(philo->data->printing);
	ft_sleep(philo);
}

void	ft_take_forks(t_philo *philo)
{
	sem_wait(philo->data->forks);
	sem_wait(philo->data->printing);
	philo->forks_in_hands++;
	test_printer(FORK, philo->start_time, philo->id);
	sem_post(philo->data->printing);
	sem_wait(philo->data->forks);
	philo->offset = gettimeofday_millisec();
	sem_wait(philo->data->printing);
	philo->forks_in_hands++;
	test_printer(FORK, philo->start_time, philo->id);
	sem_post(philo->data->printing);
	ft_eat(philo);
}

void	philo_routine(t_philo *philo)
{
	wait_all_philos(philo->data->start_time);
	if (philo->id % 2 != 0)
		precise_usleep(philo->time_to_eat / 2);
	if (pthread_create(&philo->thread, NULL, gods_overseeing, philo))
		exit(EXIT_FAILURE);
	pthread_detach(philo->thread);
	ft_take_forks(philo);
}
