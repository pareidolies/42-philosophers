/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_routine.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smostefa <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/11 16:51:25 by smostefa          #+#    #+#             */
/*   Updated: 2022/06/11 16:51:26 by smostefa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "../includes/philosophers.h"

void    philo_routine(void  *arg)
{
    t_philo *philo;

    philo = (t_philo *)arg;

    //mutex lock
    print_philo_state(FORK);
    //mutex lock
    print_philo_state(FORK);
    print_philo_state(EAT);
    usleep(data->time_to_eat);
    //mutex unlock
    print_philo_state(SLEEP);
    usleep(data->time_to_eat);
    print_philo_state(THINK);    
}