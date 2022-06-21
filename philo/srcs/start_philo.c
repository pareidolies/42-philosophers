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

int philo_thread(t_all *all)
{
    int     i;
    t_philo *philo;
    t_data  data;

    philo = all->philo;
    data = all->data;
    i = 0;
    while (i < data.nbr_philos)
    {
        pthread_create(&(philo[i].thread), NULL, philo_routine, (void *)&philo[i]);
        i++;
    }
    return (0);
}

int	thanatos_thread(t_data *data)
{
    pthread_create(&(data->thanatos), NULL, thanatos_routine, (void *)(data->thanatos));
    return (0);
}

int	end_philo(t_all *all)
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
    return (0);
}

int	start_philo(t_all *all)
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
    error = philo_thread(all);
    if (error)
        return(print_errors(error));
    error = thanatos_thread(&all->data);
    if (error)
        return(print_errors(error));
    error = end_philo(all);
    if (error)
        return(print_errors(error));
    return (error);
}
