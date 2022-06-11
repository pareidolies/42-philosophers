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

void	print_philo_state(int state)
{
	if (state == FORK)
		ft_putstr_fd_color(1, FORK_MSSG, ANSI_COLOR_LIGHT_PURPLE);
	if (state == EAT)
		ft_putstr_fd_color(1, EAT_MSSG, ANSI_COLOR_LIGHT_YELLOW);
	if (state == SLEEP)
		ft_putstr_fd_color(1, SLEEP_MSSG, ANSI_COLOR_LIGHT_BLUE);
	if (state == THINK)
		ft_putstr_fd_color(1, THINK_MSSG, ANSI_COLOR_LIGHT_GREEN);
	if (state == DIE)
		ft_putstr_fd_color(1, DIE_MSSG, ANSI_COLOR_LIGHT_RED);
}
