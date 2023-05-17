/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   monitoring_bonus.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jomirand <jomirand@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/10 12:29:09 by jomirand          #+#    #+#             */
/*   Updated: 2023/05/10 12:29:09 by jomirand         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers_bonus.h"

void	*monitoring(void *arg)
{
	t_philo	*philo;

	philo = (t_philo *)arg;
	while (1)
		if (philos_died(philo))
			return (NULL);
	return (0);
}

int	philos_died(t_philo *philo)
{
	sem_wait(philo->reaper);
	if ((get_time() - philo->last_meal) > philo->rules->ttd)
	{
		sem_wait(philo->rules->dead);
		print_message("died\n", philo);
		sem_post(philo->rules->end);
		return (1);
	}
	sem_post(philo->reaper);
	return (0);
}

void	check_end(t_rules *rules)
{
	pthread_t	meals;
	pthread_t	monitor;

	pthread_create(&monitor, NULL, check_finish, rules);
	pthread_create(&meals, NULL, check_meals, rules);
	pthread_join(monitor, NULL);
	pthread_join(meals, NULL);
}

void	*check_meals(void *arg)
{
	t_rules	*rules;
	int		i;

	i = 0;
	rules = (t_rules *)arg;
	while (1)
	{
		sem_wait(rules->meals);
		rules->all_ate++;
		if (rules->all_ate == rules->num_philos)
		{
			sem_post(rules->end);
			while (i < rules->num_philos)
			{
				kill(rules->pid[i], SIGKILL);
				i++;
			}
			return (NULL);
		}
	}
	return (NULL);
}

void	*check_finish(void *arg)
{
	t_rules	*rules;
	int		i;

	rules = (t_rules *)arg;
	sem_wait(rules->end);
	i = 0;
	while (i < rules->num_philos)
	{
		sem_post(rules->meals);
		i++;
	}
	return (NULL);
}
