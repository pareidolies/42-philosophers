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

int	test_printer(int state, t_data *data, int id)
{
	long	timestamp;

	timestamp = get_elapsed_time(data->start_time);
	if (data->is_it_the_end)
		return (42);
	if (state == FORK)
		printf("\x1b[97m%-7ld %5d %23s\x1b[0m", timestamp, id, FORK_MSSG);
	if (state == EAT)
		printf("\e[0;33m%-7ld %5d %23s\x1b[0m", timestamp, id, EAT_MSSG);
	if (state == SLEEP)
		printf("\x1b[97m%-7ld %5d %23s\x1b[0m", timestamp, id, SLEEP_MSSG);
	if (state == THINK)
		printf("\x1b[97m%-7ld %5d %23s\x1b[0m", timestamp, id, THINK_MSSG);
	if (state == DIE)
		printf("\e[0;34m%-7ld %5d %23s\x1b[0m", timestamp, id, DIE_MSSG);
	return (0);
}
