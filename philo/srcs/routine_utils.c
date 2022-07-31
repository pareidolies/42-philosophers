/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smostefa <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/31 13:51:50 by smostefa          #+#    #+#             */
/*   Updated: 2022/07/31 13:51:53 by smostefa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philosophers.h"

void	wait_before_taking_first_fork(t_philo *philo)
{
	while ((get_elapsed_time(philo->start_time) - philo->last_meal)
		< (philo->time_to_die / 4) * 3)
		usleep(PRECISE_SLEEP_TIME);
	ft_take_first_fork(philo);
}
