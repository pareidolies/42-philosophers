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

# include "../includes/philosophers.h"

//en millisecondes

long get_elapsed_time(t_data *data)
{
    return(gettimeofday_millisec() - data->start_time);
}

long	gettimeofday_millisec(void)
{
	struct timeval	now;
    int             seconds;
    int             useconds;

	gettimeofday(&now, NULL);
    seconds = (&now)->tv_sec;
    useconds = (&now)->tv_usec;
	return (seconds * 1000 + useconds / 1000);
}

void	precise_usleep(int  duration)
{
	long	end;

	end = gettimeofday_millisec() + duration;
	while (gettimeofday_millisec() < end)
		usleep(PRECISE_SLEEP_TIME); //100?
}

void	wait_all_philos(int start_time)
{
	while (gettimeofday_millisec() < start_time)
		;
}