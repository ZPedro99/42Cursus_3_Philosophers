/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_libft.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jomirand <jomirand@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/14 12:22:41 by jomirand          #+#    #+#             */
/*   Updated: 2023/04/14 12:25:27 by jomirand         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

int	ft_atoi(const char *str)

{
	int	i;
	int	result;
	int	negative;

	i = 0;
	result = 0;
	negative = 1;
	while ((str[i] >= 9 && str[i] <= 13) || str[i] == 32)
		i++;
	if (str[i] == '-' || str[i] == '+')
	{
		if (str[i] == '-')
			negative = -1;
		i++;
	}
	while (str[i] >= 48 && str[i] <= 57)
	{
		result = (result * 10) + (str[i] - '0');
		i++;
	}
	return (result * negative);
}

int	only_num(int argc, char **argv)
{
	int	i;
	int	j;

	i = 1;
	while(i < argc)
	{
		j = 0;
		if(argv[i][j] == '-')
			j++;
		while(argv[i][j])
		{
			if(argv[i][j] < '0' || argv[i][j] > '9')
				return (0);
			j++;
		}
		i++;
	}
	return (1);
}

void	ft_putchar_fd(char c, int fd)

{
	write(fd, &c, 1);
}

void	ft_putstr_fd(char *s, int fd)

{
	int	i;

	if (!s || !fd)
		return ;
	i = 0;
	while (s[i])
	{
		write (fd, &s[i], 1);
		i++;
	}
}