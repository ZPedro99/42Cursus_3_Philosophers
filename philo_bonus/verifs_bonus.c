/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   verifs_bonus.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jomirand <jomirand@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/02 11:34:18 by jomirand          #+#    #+#             */
/*   Updated: 2023/05/02 11:34:18 by jomirand         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers_bonus.h"

int	args_check(int argc, char **argv)
{
	int	i;

	if(argc != 5 && argc != 6)
		return (0);
	i = 0;
	while(i < argc - 1)
	{
		if(ft_atol(argv[i]) > INT_MAX || ft_atol(argv[i]) < INT_MIN)
			return(0);
		i++;
	}
	if(!only_num(argc, argv))
		return (0);
	if(!positive_args(argc, argv))
		return (0);
	return (1);
}

int	positive_args(int argc, char **argv)
{
	int	i;

	i = 1;
	while(i < argc)
	{
		if(ft_atoi(argv[i]) <= 0)
			return (0);
		i++;
	}
	return (1);
}