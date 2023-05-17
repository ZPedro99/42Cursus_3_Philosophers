/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_libft_bonus.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jomirand <jomirand@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/02 15:39:37 by jomirand          #+#    #+#             */
/*   Updated: 2023/05/02 15:39:37 by jomirand         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers_bonus.h"

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
	while (i < argc)
	{
		j = 0;
		if (argv[i][j] == '-')
			j++;
		while (argv[i][j])
		{
			if (argv[i][j] < '0' || argv[i][j] > '9')
				return (0);
			j++;
		}
		i++;
	}
	return (1);
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

static int	ft_cal_number_digits(int n)
{
	int	count;

	count = 0;
	if (n < 0)
	{
		count++;
		n *= -1;
	}
	else if (n == 0)
		return (1);
	while ((unsigned int)n > 0)
	{
		count++;
		n = (unsigned int)n / 10;
	}
	return (count);
}

char	*ft_itoa(int n)
{
	char	*memall;
	int		num_dig;

	num_dig = ft_cal_number_digits(n);
	memall = malloc((num_dig + 1) * sizeof(char));
	if (n == 0)
		memall[0] = 48;
	if (memall == NULL)
		return (NULL);
	if (n < 0)
	{
		memall[0] = '-';
		n *= -1;
	}
	memall[num_dig] = '\0';
	while ((num_dig) > 0 && (unsigned int)n > 0)
	{
		memall[num_dig - 1] = ((unsigned int)n % 10) + '0';
		n = (unsigned int)n / 10;
		num_dig--;
	}
	return (memall);
}
