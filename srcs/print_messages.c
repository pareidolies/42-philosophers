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

void	print_state(int id, char *mssg, char *color)
{
	int	timestamp;

	timestamp = get_elapsed_time(data);
	ft_putnbr_fd_color(1, timestamp, color);
	ft_putstr("    ");
	ft_putnbr_fd_color(1, id, color);
	ft_putstr("    ");
	ft_putstr_fd_color(1, mssg, color);
	ft_putstr("\n");
}

void	print_philo_state(int state, t_data *data, int id)
{
	if (state == FORK)
		print_state(id, FORK_MSSG, ANSI_COLOR_LIGHT_PURPLE);
	if (state == EAT)
		print_state(id, EAT_MSSG, ANSI_COLOR_LIGHT_YELLOW);
	if (state == SLEEP)
		print_state(id, SLEEP_MSSG, ANSI_COLOR_LIGHT_BLUE);
	if (state == THINK)
		print_state(id, THINK_MSSG, ANSI_COLOR_LIGHT_GREEN);
	if (state == DIE)
		print_state(id, DIE_MSSG, ANSI_COLOR_LIGHT_RED);
}
