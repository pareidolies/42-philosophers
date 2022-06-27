/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_messages.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smostefa <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/11 16:51:02 by smostefa          #+#    #+#             */
/*   Updated: 2022/06/11 16:51:04 by smostefa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philosophers.h"

void	print_manual(void)
{
	ft_putstr_fd_color(M1, 2, ANSI_COLOR_LIGHT_BLUE);
	ft_putstr_fd_color(M2, 2, ANSI_COLOR_LIGHT_BLUE);
	ft_putstr_fd_color(M3, 2, ANSI_COLOR_LIGHT_BLUE);
}

int	print_errors(int error)
{
	if (error == ARGS_ERROR)
		print_manual();
	if (error == MALLOC_ERROR)
		ft_putstr_fd_color(MALLOC_MSSG, 2, ANSI_COLOR_LIGHT_RED);
	if (error == THREAD_ERROR)
		ft_putstr_fd_color(THREAD_MSSG, 2, ANSI_COLOR_LIGHT_RED);
	if (error == MUTEX_ERROR)
		ft_putstr_fd_color(MUTEX_MSSG, 2, ANSI_COLOR_LIGHT_RED);
	return (error);
}

void	print_state(int id, char *mssg, char *color, t_data *data)
{
	long	timestamp;

	timestamp = get_elapsed_time(data);
	ft_putnbr_fd_color(timestamp, 1, color);
	ft_putstr_fd("    ", 1);
	ft_putnbr_fd_color(id, 1, color);
	ft_putstr_fd("    ", 1);
	ft_putstr_fd_color(mssg, 1, color);
	ft_putstr_fd("\n", 1);
}

int	print_philo_state(int state, t_data *data, int id)
{
	if(data->is_it_the_end)
	{
		return (1);
	}
	if (state == FORK)
		print_state(id, FORK_MSSG, ANSI_COLOR_LIGHT_PURPLE, data);
	if (state == EAT)
		print_state(id, EAT_MSSG, ANSI_COLOR_LIGHT_YELLOW, data);
	if (state == SLEEP)
		print_state(id, SLEEP_MSSG, ANSI_COLOR_LIGHT_BLUE, data);
	if (state == THINK)
		print_state(id, THINK_MSSG, ANSI_COLOR_LIGHT_GREEN, data);
	if (state == DIE)
		print_state(id, DIE_MSSG, ANSI_COLOR_LIGHT_RED, data);
	return (0);
}

int	test_printer(int state, t_data *data, int id)
{
	long	timestamp;

	timestamp = get_elapsed_time(data);
	if(data->is_it_the_end)
	{
		return (42);
	}
	if (state == FORK)
		printf("%ld %d %s", timestamp, id, FORK_MSSG);
	if (state == EAT)
		printf("%ld %d %s", timestamp, id, EAT_MSSG);
	if (state == SLEEP)
		printf("%ld %d %s", timestamp, id, SLEEP_MSSG);
	if (state == THINK)
		printf("%ld %d %s", timestamp, id, THINK_MSSG);
	if (state == DIE)
		printf("%ld %d %s", timestamp, id, DIE_MSSG);
	return (0);
}