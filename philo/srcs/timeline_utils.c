/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   timeline_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smostefa <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/11 15:38:17 by smostefa          #+#    #+#             */
/*   Updated: 2022/06/11 15:38:43 by smostefa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philosophers.h"

long	get_elapsed_time(long start_time)
{
	return (gettimeofday_millisec() - start_time);
}

long	gettimeofday_millisec(void)
{
	struct timeval	now;
	int				seconds;
	int				useconds;

	gettimeofday(&now, NULL);
	seconds = (&now)->tv_sec;
	useconds = (&now)->tv_usec;
	return (seconds * 1000 + useconds / 1000);
}

void	precise_usleep(int duration, t_data *data, t_philo *philo)
{
	long	end;
	long	check;

	(void) data;
	end = gettimeofday_millisec() + duration;
	check = gettimeofday_millisec() + 1000;
	while (gettimeofday_millisec() < end)
	{
		usleep(PRECISE_SLEEP_TIME);
		if (gettimeofday_millisec() >= check)
		{
			pthread_mutex_lock(&data->printing);
			if (data->is_it_the_end == 1)
			{
				printf("coucou");
				if (philo->forks_in_hands == 2)
				{
					pthread_mutex_unlock(philo->left_fork);
					pthread_mutex_unlock(&philo->right_fork);
				}
				pthread_mutex_unlock(&data->printing);
				break ;
			}
			pthread_mutex_unlock(&data->printing);
			check = gettimeofday_millisec() + 1000;
		}
	}
}

void	wait_all_philos(int start_time)
{
	while (gettimeofday_millisec() < start_time)
		;
}
