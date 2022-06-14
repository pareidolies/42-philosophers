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
	ft_putstr_fd("error\n", 2);
}

int	print_errors(int error)
{
	if (error == ARGS_ERROR)
		print_manual();
	return (error);
}

void	print_state(int id, char *mssg, char *color, t_data *data)
{
	int	timestamp;

	timestamp = get_elapsed_time(data);
	ft_putnbr_fd_color(timestamp, 1, color);
	ft_putstr_fd("    ", 1);
	ft_putnbr_fd_color(id, 1, color);
	ft_putstr_fd("    ", 1);
	ft_putstr_fd_color(mssg, 1, color);
	ft_putstr_fd("\n", 1);
}

void	print_philo_state(int state, t_data *data, int id)
{
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
}
