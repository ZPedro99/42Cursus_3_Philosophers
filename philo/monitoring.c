/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   monitoring.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jomirand <jomirand@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/19 14:18:42 by jomirand          #+#    #+#             */
/*   Updated: 2023/04/20 12:05:21 by jomirand         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

void	*monitoring(void *arg)
{
	t_rules	*rules;

	rules = (t_rules *)arg;
	while (1)
	{
		if (philos_died(rules))
			return (NULL);
		if (philos_ate(rules))
			return (NULL);
	}
}

int	philos_died(t_rules *rules)
{
	int	i;

	i = 0;
	while (i < rules->num_philos)
	{
		pthread_mutex_lock(&rules->ph[i].reaper);
		if ((get_time() - rules->ph[i].last_meal) > rules->ttd)
		{
			print_message("died\n", &rules->ph[i]);
			pthread_mutex_lock(&rules->verifs);
			rules->died = 1;
			pthread_mutex_unlock(&rules->verifs);
			pthread_mutex_unlock(&rules->ph[i].reaper);
			return (1);
		}
		pthread_mutex_unlock(&rules->ph[i].reaper);
		i++;
	}
	return (0);
}

int	philos_ate(t_rules *rules)
{
	if (rules->pme == -1)
		return (0);
	pthread_mutex_lock(&rules->verifs);
	if (rules->all_ate == rules->num_philos)
	{
		pthread_mutex_unlock(&rules->verifs);
		return (1);
	}
	pthread_mutex_unlock(&rules->verifs);
	return (0);
}
