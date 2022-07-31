/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smostefa <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/31 14:00:48 by smostefa          #+#    #+#             */
/*   Updated: 2022/07/31 14:00:50 by smostefa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philosophers.h"

void	wait_before_taking_forks(t_philo *philo)
{
	while ((get_elapsed_time(philo->start_time) - philo->last_meal)
		< (philo->time_to_die / 4) * 3)
		usleep(PRECISE_SLEEP_TIME);
	ft_take_forks(philo);
}
