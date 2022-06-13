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

    //takes the lower-numbered fork first
    if (philo->id == (philo->nbr_philos - 1))
        pthread_mutex_lock(&philo->left_fork);
    else
        pthread_mutex_lock(&philo->right_fork);
    philo->forks_in_hand++;
    pthread_mutex_lock(philo->printing);
    print_philo_state(FORK);
    pthread_mutex_unlock(philo->printing);
    //takes the second fork next to him
    if (philo->id == (philo->nbr_philos - 1))
        pthread_mutex_lock(&philo->right_fork);
    else
        pthread_mutex_lock(&philo->left_fork);
    pthread_mutex_lock(philo->printing);
    print_philo_state(FORK);
    pthread_mutex_unlock(philo->printing);
    //since he has both forks in hand he starts eating
    pthread_mutex_lock(philo->printing);
    print_philo_state(EAT);
    pthread_mutex_unlock(philo->printing);
    usleep(philo->time_to_eat);
    //he drops both forks
    pthread_mutex_unlock(&philo->right_fork);
    pthread_mutex_unlock(&philo->left_fork);
    //he starts sleeping
    pthread_mutex_lock(philo->printing);
    print_philo_state(SLEEP);
    pthread_mutex_unlock(philo->printing);
    usleep(philo->time_to_eat);
    //he starts thinking
    pthread_mutex_lock(philo->printing);
    print_philo_state(THINK);
    pthread_mutex_unlock(philo->printing);
}