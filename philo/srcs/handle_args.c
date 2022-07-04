/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_args.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smostefa <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/11 16:50:48 by smostefa          #+#    #+#             */
/*   Updated: 2022/06/28 12:53:43 by smostefa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philosophers.h"

int	only_positive_digit(char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (str[i] > '9' || str[i] < '0')
			return (0);
		i++;
	}
	return (1);
}

int	check_args(int argc, char **argv)
{
	int	i;

	if (argc < 5 || argc > 6)
		return (ARGS_ERROR);
	i = 1;
	while (argv[i])
	{
		if (!only_positive_digit(argv[i]))
			return (ARGS_ERROR);
		if (ft_atoi_int(argv[i]) <= 0)
			return (ARGS_ERROR);
		i++;
	}
	return (0);
}

t_data	parse_args(int argc, char **argv)
{
	t_data	data;

	(void) argc;
	data.nbr_philos = ft_atoi(argv[1]);
	data.time_to_die = ft_atoi(argv[2]);
	data.time_to_eat = ft_atoi(argv[3]);
	data.time_to_sleep = ft_atoi(argv[4]);
	data.need_to_eat = INT_MAX;
	if (argc == 6)
		data.need_to_eat = ft_atoi(argv[5]);
	data.someone_died = 0;
	data.are_full = 0;
	data.is_it_the_end = 0;
	pthread_mutex_init(&data.printing, NULL);
	return (data);
}
