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

int get_elapsed_time(t_data *data)
{
    struct timeval  now;
    int             seconds;
    int             useconds;

    gettimeofday(&now, NULL);
    seconds = (&now)->tv_sec - data->start_time.tv_sec;
    useconds = (&now)->tv_usec - data->start_time.tv_usec;
    return (seconds * 1000 + useconds / 1000);
}

time_t	gettimeofday_millisec(void)
{
	struct timeval	now;
    int             seconds;
    int             useconds;

	gettimeofday(&now, NULL);
    seconds = (&now)->tv_sec;
    useconds = (&now)->tv_usec;
	return (seconds * 1000 + useconds / 1000);
}

/*void	precise_usleep(int  duration)
{
	time_t	end;

	end = gettimeofday_millisec() + duration;
	while (gettimeofday_millisec() < end)
		usleep(PRECISE_SLEEP_TIME); //100?
}*/

void	precise_usleep(int duration)
{
	time_t	start; 
	long		current;

    start = gettimeofday_millisec();
	current = 0;
	while (duration > current)
	{
		usleep(PRECISE_SLEEP_TIME);
		current = gettimeofday_millisec() - start;
	}
}
