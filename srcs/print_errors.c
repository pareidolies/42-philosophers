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
