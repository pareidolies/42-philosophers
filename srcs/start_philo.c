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

int philo_thread(t_philo **philo)
{
    int i;

    i = 0;
    while (i < data->nbr_philos)
    {
        pthread_create(&(philo[i].thread), NULL, &philo_routine, (void *)philo[i]);
        i++;
    }
    return (0);
}

int	thanatos_thread(t_thanatos  thanatos)
{
    pthread_create(&thanatos, NULL, &thanatos_routine, (void *)thanatos);
    return (0);
}

int	end_philo(t_philo **philo, t_thanatos thanatos)
{

    return (0);
}

int	start_philo(t_philo **philo, t_data *data)
{
	/*printf("%d\n", get_elapsed_time(data));
    usleep(200000);
    printf("%d\n", get_elapsed_time(data));
    usleep(200000);
    printf("%d\n", get_elapsed_time(data));
    usleep(200000);
    return (0);*/
    int error;
    t_thanatos  thanatos;

    error = 0;
    error = philo_thread(philo);
    if (error)
        return(print_errors(error));
    error = thanatos_thread(thanatos);
    if (error)
        return(print_errors(error));
    error = end_philo(philo, thanatos);
    if (error)
        return(print_errors(error));
    return (error);
}
