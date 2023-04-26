/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   verifs.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jomirand <jomirand@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/10 09:08:23 by jomirand          #+#    #+#             */
/*   Updated: 2023/04/14 12:23:18 by jomirand         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

int	args_check(int argc, char **argv)
{
	if(argc != 5 && argc != 6)
		return (0);
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