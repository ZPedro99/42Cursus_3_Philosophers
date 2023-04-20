/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   monitoring.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jomirand <jomirand@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/19 14:18:42 by jomirand          #+#    #+#             */
/*   Updated: 2023/04/20 11:30:07 by jomirand         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

void	*monitoring(void *arg)
{
	t_rules	*rules;

	rules = (t_rules *)arg;
	while(1)
	{
		if(philos_died(rules))
		{
			printf("vou retornar\n");
			return (NULL);
		}
		if(philos_ate(rules))
			return (NULL);
	}
	return(NULL);
}

int	philos_died(t_rules *rules)
{
	int			i;
	//printf("entrei no philos died\n");
	i = 0;
	while (i < rules->num_philos)
	{
		if((get_time() - rules->ph[i].last_meal) > rules->ttd)
		{
			//printf("entrei no if\n");
			print_message("died\n", &rules->ph[i]);
			//printf("entrei no if2\n");
			rules->died = 1;
			return(1);
		}
		i++;
	}
	return(0);
}

int	philos_ate(t_rules *rules)
{
	//printf("entrei no philos ate\n");
	if(rules->pme == -1)
		return(0);
	if(rules->all_ate == rules->num_philos)
		return(1);
	return(0);
}