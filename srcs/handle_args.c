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

int	parse_args(int argc, char **argv, t_data *data)
{
	data->nbr_philos = ft_atoi(argv[1]);
	data->time_to_die = ft_atoi(argv[2]);
	data->time_to_eat = ft_atoi(argv[3]);
	data->time_to_sleep = ft_atoi(argv[4]);
	if (argc == 6)
		data->nbr_mandatory_lunches = ft_atoi(argv[5]);
	if (data->nbr_philos <= 0)
		return (ARGS_ERROR);
	if (data->time_to_die <= 0)
		return (ARGS_ERROR);
	if (data->time_to_eat <= 0)
		return (ARGS_ERROR);
	if (data->time_to_sleep <= 0)
		return (ARGS_ERROR);
	if (data->nbr_mandatory_lunches < 0)
		return (ARGS_ERROR);
	return (0);
}
