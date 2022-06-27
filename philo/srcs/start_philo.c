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

int philo_thread(t_data *data, t_philo *philo)
{
    int     i;

    if (pthread_mutex_init(&data->printing, NULL))
		return (MUTEX_ERROR);
    i = 0;
    while (i < data->nbr_philos)
    {
        if (pthread_create(&(philo[i].thread), NULL, philo_routine, (void *)&philo[i]))
            return (THREAD_ERROR);
        i++;
    }
    return (0);
}

int end_philo(t_all *all)
{
    int     i;
    t_philo *philo;
    t_data  data;

    philo = all->philo;
    data = all->data;
    i = 0;
    while (i < data.nbr_philos)
    {
        pthread_join(philo[i].thread, NULL);
        i++;
    }
    i = 0;
    while (i < data.nbr_philos)
    {
        pthread_mutex_destroy(&philo[i].right_fork);
        i++;
    }
    pthread_mutex_destroy(&data.printing);
    if (philo)
        free(philo);
    return (0);
}

int	start_philo(t_all *all)
{
    int error;

    error = philo_thread(&all->data, all->philo);
    if (error)
        return(print_errors(error));
    usleep(SLEEP_TIME); //MACRO
    gods_overseeing(&all->data, all->philo);
    error = end_philo(all);
    if (error)
        return(print_errors(error));
    return (error);
}
