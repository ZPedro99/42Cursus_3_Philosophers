/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   simulation.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jomirand <jomirand@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/13 11:11:28 by jomirand          #+#    #+#             */
/*   Updated: 2023/04/20 16:57:20 by jomirand         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

void	*simulation(void *arg)
{
	t_philo	*philo;

	philo = (t_philo *)arg;
	if (one_philo(philo))
		return (NULL);
	if (philo->id % 2 == 0)
		usleep(1000);
	while (1)
	{
		if (take_forks(philo))
			return (NULL);
		if (eating(philo))
			return (NULL);
		if (sleeping(philo))
			return (NULL);
		if (thinking(philo))
			return (NULL);
	}
	return (NULL);
}

int	take_forks(t_philo *philo)
{
	pthread_mutex_lock(&philo->rules->verifs);
	if (philo->rules->died == 1
		|| philo->rules->all_ate == philo->rules->num_philos)
	{
		pthread_mutex_unlock(&philo->rules->verifs);
		return (1);
	}
	pthread_mutex_unlock(&philo->rules->verifs);
	if (pthread_mutex_lock(philo->l_fork) != 0)
		error_message("Failed locking a fork\n");
	print_message("has taken a fork\n", philo);
	if (pthread_mutex_lock(philo->r_fork) != 0)
		error_message("Failed locking a fork\n");
	print_message("has taken a fork\n", philo);
	return (0);
}

int	eating(t_philo *philo)
{
	pthread_mutex_lock(&philo->rules->verifs);
	if (philo->rules->died == 1
		|| philo->rules->all_ate == philo->rules->num_philos)
	{
		pthread_mutex_unlock(&philo->rules->verifs);
		pthread_mutex_unlock(philo->l_fork);
		pthread_mutex_unlock(philo->r_fork);
		return (1);
	}
	pthread_mutex_unlock(&philo->rules->verifs);
	pthread_mutex_lock(&philo->reaper);
	philo->last_meal = get_time();
	print_message("is eating\n", philo);
	pthread_mutex_lock(&philo->rules->verifs);
	philo->times_eaten++;
	if (philo->rules->pme != -1)
	{
		if (philo->times_eaten == philo->rules->pme)
			philo->rules->all_ate++;
	}
	pthread_mutex_unlock(&philo->rules->verifs);
	pthread_mutex_unlock(&philo->reaper);
	usleep(philo->rules->tte * 1000);
	if (pthread_mutex_unlock(philo->l_fork) != 0)
		error_message("Failed unlocking the mutex\n");
	if (pthread_mutex_unlock(philo->r_fork))
		error_message("Failed unlocking the mutex\n");
	return (0);
}

int	sleeping(t_philo *philo)
{
	pthread_mutex_lock(&philo->rules->verifs);
	if (philo->rules->died == 1
		|| philo->rules->all_ate == philo->rules->num_philos)
	{
		pthread_mutex_unlock(&philo->rules->verifs);
		return (1);
	}
	pthread_mutex_unlock(&philo->rules->verifs);
	print_message("is sleeping\n", philo);
	usleep(philo->rules->tts * 1000);
	return (0);
}

int	thinking(t_philo *philo)
{
	pthread_mutex_lock(&philo->rules->verifs);
	if (philo->rules->died == 1
		|| philo->rules->all_ate == philo->rules->num_philos)
	{
		pthread_mutex_unlock(&philo->rules->verifs);
		return (1);
	}
	pthread_mutex_unlock(&philo->rules->verifs);
	print_message("is thinking\n", philo);
	return (0);
}
