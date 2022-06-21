/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_args.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smostefa <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/11 16:50:48 by smostefa          #+#    #+#             */
/*   Updated: 2022/06/11 16:50:51 by smostefa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philosophers.h"

int is_positive_nbr(char *str) //INT MAX MIN
{
	int i;

	i = 0;
	while (str[i])
	{
		if (str[i] > '9' || str[i] < '0')
		{
			printf("err1");
			return (0);
		}
 		i++;
	}
	return (1);
}

int check_args(int argc, char **argv)
{
	int	i;

	if (argc < 5 || argc > 6) //WRONG NBR OF ARGS
	{
		printf("err2");
		return (ARGS_ERROR);
	}
	i = 1;
	while (argv[i])
	{
		if (!is_positive_nbr(argv[i])) //POSITIVE VALUE
		{
			printf("err3");
			return (ARGS_ERROR);
		}
		i++;
	}
	return (0);
}

t_data	parse_args(int argc, char **argv)
{
	t_data	data;
	(void)	argc;

	data.nbr_philos = ft_atoi(argv[1]);
	data.time_to_die = ft_atoi(argv[2]);
	data.time_to_eat = ft_atoi(argv[3]);
	data.time_to_sleep = ft_atoi(argv[4]);
	data.need_to_eat = INT_MAX;
	if (argc == 6)
		data.need_to_eat = ft_atoi(argv[5]);
	/*if (data.nbr_philos <= 0)
	{
		printf("err4");
		return (0);
	}
	if (data.time_to_die <= 0)
	{
		printf("err4");
		return (0);
	}
	if (data.time_to_eat <= 0)
	{
		printf("err4");
		return (0);
	}
	if (data.time_to_sleep <= 0)
	{
		printf("err4");
		return (0);
	}
	if (data.need_to_eat < 0)
	{
		printf("err4");
		return (0);
	}*/
	pthread_mutex_init(&data.printing, NULL);
	pthread_mutex_init(&data.death_mutex, NULL);
	pthread_mutex_init(&data.meals_mutex, NULL);
	pthread_mutex_init(&data.end_mutex, NULL);
	data.everybody_is_alive = 1;
	data.someone_died = 0;
	data.are_full = 0;
	data.is_it_the_end = 0;
	return (data);
}
