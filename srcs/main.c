/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smostefa <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/08 10:32:07 by smostefa          #+#    #+#             */
/*   Updated: 2022/06/08 12:18:42 by smostefa         ###   ########.fr       */
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
			return (0);
 		i++;
	}
	return (1);
}

int check_args(int argc, char **argv)
{
	int	i;

	if (argc < 5 || argc > 6) //WRONG NBR OF ARGS
		return (0);
	i = 0;
	while (argv[i])
	{
		if (!is_positive_nbr(argv[i])) //POSITIVE VALUE
			return (0);
		i++;
	}
	return (1);
}

int	parse_args(int argc, char **argv, t_data *data)
{
	data->nbr_philos = ft_atoi(argv[1]);
	data->time_to_die = ft_atoi(argv[2]);
	data->time_to_eat = ft_atoi(argv[3]);
	data->time_to_sleep = ft_atoi(argv[4]);
	if (argc == 6)
		data->nbr_mandatory_lunches = ft_atoi(argv[5]);
	if (data->nbr_philos <= 0)
		return ();
	if (data->time_to_die <= 0)
		return ();
	if (data->time_to_eat <= 0)
		return ();
	if (data->nbr_time_to_sleep <= 0)
		return ();
	return (0);
}

int	initialize_info(t_data	*data)
{
	int	i;

	data->philo = malloc(sizeof(t_philo) * data->nbr_philos);
	if (!data->philo)
		return (MALLOC_ERROR);
	data->start_time = actual_time();
	i = 0;
	while (i < data->nbr_philos)
	{
		data->philo[i].id = i;
		data->philo[i].right_fork = NULL;
		pthread_mutex_init(&data->philo[i].left_fork, NULL);
		if (data->nbr_philos == 1)
			return (1);
		if (i == data->nbr_philos - 1)
			data->philo[i].right_fork = &data->philo[0].left_fork;
		else
			data->philo[i].right_fork = &data->philo[i + 1].left_fork;
		i++;
	}
	return (1);
}

int main(int argc, char **argv)
{
	t_data	data;
	int	error;

	error = check_args(argc, argv);
	if (error)
	{
		print(error);
		return (error);
	}
	parse_args(argc, argv, &data);
	error = initialize_info(&data);
	if (error)
	{
		print(error);
		return (error);
	}
	start_philo(&data);
	return (error);
}
