/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smostefa <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/08 12:13:44 by smostefa          #+#    #+#             */
/*   Updated: 2022/06/08 12:13:46 by smostefa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILOSOPHERS_H

# define PHILOSOPHERS_H

# include <unistd.h>
# include <stdlib.h>
# include <sys/time.h>
# include <phtread.h>

typedef struct	s_philo
{
	int		id;
	pthread_t	thread;
	pthread_mutex_t	left_fork;
	pthread_mutex_t	*right_fork;
}		t_philo;

typedef struct	s_data
{
	int		nbr_philos;
	t_philo		*philo;
	pthread_t	thanatos;
	int		time_to_die;
	int		time_to_eat;
	int		time_to_sleep;
	int		nbr_mandatory_lunches;
	time_t		start_time;
	
}		t_data;

#endif
