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

void    my_usleep(int   sleep_time)
{


}
