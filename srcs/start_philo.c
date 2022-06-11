/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   start_philo.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smostefa <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/11 16:47:21 by smostefa          #+#    #+#             */
/*   Updated: 2022/06/11 16:47:23 by smostefa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "../includes/philosophers.h"

int philo_thread(t_data *data)
{
    int i;

    i = 0;
    while (i < data->nbr_philos)
    {
        pthread_create(&(data->philo[i].thread), NULL, &philo_routine, (void *)data->philo[i]);
        i++;
    }
    return (0);
}

int	thanatos_thread(t_data *data)
{

    return (0);
}

int	end_philo(t_data *data)
{

    return (0);
}

int	start_philo(t_data *data)
{
	/*printf("%d\n", get_elapsed_time(data));
    usleep(200000);
    printf("%d\n", get_elapsed_time(data));
    usleep(200000);
    printf("%d\n", get_elapsed_time(data));
    usleep(200000);
    return (0);*/
    int error;

    error = 0;
    error = philo_thread(data);
    if (error)
        return(print_errors(error));
    error = thanatos_thread(data);
    if (error)
        return(print_errors(error));
    error = philo_thread(data);
    if (error)
        return(print_errors(error));
    return (error);
}
