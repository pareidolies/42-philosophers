/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smostefa <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/08 12:18:03 by smostefa          #+#    #+#             */
/*   Updated: 2022/06/08 12:18:09 by smostefa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philosophers.h"

void	ft_putchar_fd(char c, int fd)
{
	write(fd, &c, 1);

}

void	ft_putstr_fd_color(char *str, int fd, char *color)
{
	ft_putstr_fd(color, fd);
	ft_putstr_fd(str, fd);
	ft_putstr_fd(ANSI_COLOR_RESET, fd);
}

void	ft_putstr_fd(char *s, int fd)
{
	int	i;

	i = 0;
	if (s)
	{
		while (s[i])
		{
			write(fd, &s[i], 1);
			i++;
		}
	}
}

void	ft_putnbr_fd_color(int n, int fd, char *color)
{
	ft_putstr_fd(color, fd);
	ft_putnbr_fd(n, fd);
	ft_putstr_fd(ANSI_COLOR_RESET, fd);
}

void	ft_putnbr_fd(int n, int fd)
{
	if (n == -2147483648)
		ft_putstr_fd("-2147483648", fd);
	else
	{
		if (n < 0)
		{
			ft_putchar_fd('-', fd);
			n = n * -1;
		}
		if (n > 9)
		{
			ft_putnbr_fd(n / 10, fd);
		}
		ft_putchar_fd((n % 10) + '0', fd);
	}
}

int	ft_atoi(const char *str)
{
	int	i;
	int	minus;
	int	nb;

	i = 0;
	minus = 0;
	nb = 0;
	while ((str[i] == ' ' | str[i] == '\t' | str[i] == '\n' | str[i] == '\v'
			| str[i] == '\f' | str[i] == '\r') && str[i] != '\0')
		i++;
	if (str[i] == '+' || str[i] == '-')
	{
		if (str[i] == '-')
			minus++;
		i++;
	}
	while (str[i] >= '0' && str[i] <= '9' && str[i] != '\0')
	{
		nb = nb * 10 + (str[i] - '0');
		i++;
	}
	if ((minus % 2) == 1)
		nb = nb * (-1);
	return (nb);
}
