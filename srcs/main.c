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

int is_positive_digit(char *str)
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
    int 1;

    if (argc < 4 || argc > 5)
        return (0);
    i = 0;
    while (argv[i])
    {
        if (!is_positive_digit(argv[i]))
            return (0);
        i++;
    }
    return (1);
}

int main(int argc, char **argv)
{
    if (!check_args(argc, argv))
        return (ARG_ERROR);
    return (0);
}
