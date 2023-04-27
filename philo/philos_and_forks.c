/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philos_and_forks.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jomirand <jomirand@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/05 11:46:09 by jomirand          #+#    #+#             */
/*   Updated: 2023/04/26 17:31:08 by jomirand         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

pthread_mutex_t	*create_forks(t_rules *rules)
{
	pthread_mutex_t *forks;
	int	i;

	forks = malloc(sizeof(pthread_mutex_t) * rules->num_philos);
	if(!forks)
		return(0);
	i = 0;
	while(i < rules->num_philos)
	{
		if(pthread_mutex_init(&forks[i], NULL) != 0)
			error_message("failed to init mutex!\n");
		i++;
	}
	if(pthread_mutex_init(&rules->print, NULL) != 0)
		error_message("failed to init mutex!\n");
	return(forks);
}

t_philo	*create_philos(t_rules *rules, pthread_mutex_t *forks)
{
	int	i;

	i = 0;
	rules->ph = malloc(sizeof(t_philo) * rules->num_philos);
	if(!rules->ph)
		return(NULL);
	while(i < rules->num_philos)
	{
		rules->ph[i].id = i + 1;
		rules->ph[i].last_meal = get_time();
		rules->ph[i].times_eaten = 0;
		rules->ph[i].r_fork = &forks[i];
		rules->ph[i].l_fork = &forks[(i + 1) % rules->num_philos];
		rules->ph[i].rules = rules;
		if(pthread_mutex_init(&rules->ph[i].reaper, NULL) != 0)
			error_message("failed to init mutex!\n");
		i++;
	}
	return (rules->ph);
}

void	create_threads(t_rules *rules)
{
	int	i;

	i = 0;
	while(i < rules->num_philos)
	{
		if(pthread_create(&rules->ph[i].philo, NULL, &simulation, &rules->ph[i]) != 0)
			error_message("Couldn't create thread!\n");
		usleep(100);
		i++;
	}
	if(pthread_create(&rules->monitor, NULL, &monitoring, rules) != 0)
		error_message("Couldn't create thread!\n");
}

void	join_threads(t_rules *rules, pthread_mutex_t *forks)
{
	int	i;

	i = 0;
	//pthread_mutex_unlock(&rules->print);
	while(i < rules->num_philos)
	{
		//pthread_mutex_unlock(&rules->ph[i].reaper);
		//pthread_mutex_unlock(rules->ph[i].l_fork);
		//pthread_mutex_unlock(rules->ph[i].r_fork);
		//pthread_mutex_unlock(&forks[i]);
		i++;
	}
	i = 0;
	if(pthread_join(rules->monitor, NULL) != 0)
		error_message("Couldn't join thread1!\n");
	while(i < rules->num_philos)
	{
		if(pthread_join(rules->ph[i].philo, NULL) != 0)
			error_message("Couldn't join thread2!\n");
		//usleep(100);
		i++;
	}
	i = 0;
	while(i < rules->num_philos)
	{
		pthread_mutex_destroy(&rules->ph[i].reaper);
		pthread_mutex_destroy(&forks[i]);
		i++;
	}
	pthread_mutex_destroy(&rules->print);
}