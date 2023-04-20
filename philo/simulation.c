/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   simulation.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jomirand <jomirand@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/13 11:11:28 by jomirand          #+#    #+#             */
/*   Updated: 2023/04/20 09:51:07 by jomirand         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

void	*simulation(void *arg)
{
	int		i;
	t_philo	*philo;

	philo = (t_philo *)arg;
	i = 0;
	if(philo->id % 2)
		usleep(2000);
	while(1)
	{
		if(philo->rules->died || philo->rules->all_ate == philo->rules->num_philos)
			return(NULL);
		take_forks(philo);
		if(philo->rules->died || philo->rules->all_ate == philo->rules->num_philos)
			return(NULL);
		eating(philo);
		if(philo->rules->died || philo->rules->all_ate == philo->rules->num_philos)
			return(NULL);
		sleeping(philo);
		if(philo->rules->died || philo->rules->all_ate == philo->rules->num_philos)
			return(NULL);
		thinking(philo);
	}
	return NULL;
}

void	take_forks(t_philo *philo)
{
	if (pthread_mutex_lock(philo->l_fork) != 0)
		error_message("Failed locking a fork\n");
	print_message("has taken a fork\n", philo);
	if (pthread_mutex_lock(philo->r_fork) != 0)
		error_message("Failed locking a fork\n");
	print_message("has taken a fork\n", philo);
}

void	eating(t_philo *philo)
{
	philo->last_meal = get_time();
	print_message("is eating\n", philo);
	if(philo->rules->pme != -1)
	{
		philo->times_eaten++;
		if(philo->times_eaten == philo->rules->pme)
			philo->rules->all_ate++;
	}
	usleep(philo->rules->tte * 1000);
	if(pthread_mutex_unlock(philo->l_fork) != 0)
		error_message("Failed unlocking the mutex\n");
	if(pthread_mutex_unlock(philo->r_fork) != 0)
		error_message("Failed unlocking the mutex\n");
}

void	sleeping(t_philo *philo)
{
	print_message("is sleeping\n", philo);
	usleep(philo->rules->tts * 1000);
}

void	thinking(t_philo *philo)
{
	print_message("is thinking\n", philo);
}