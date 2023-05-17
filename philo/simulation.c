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
	mutex_lock_and_unlock(&philo->rules->verifs, 1);
	if (philo->rules->died == 1
		|| philo->rules->all_ate == philo->rules->num_philos)
	{
		mutex_lock_and_unlock(&philo->rules->verifs, 2);
		return (1);
	}
	mutex_lock_and_unlock(&philo->rules->verifs, 2);
	if (philo->id % 2)
	{
		mutex_lock_and_unlock(philo->l_fork, 1);
		print_message("has taken a fork\n", philo);
		mutex_lock_and_unlock(philo->r_fork, 1);
		print_message("has taken a fork\n", philo);
	}
	else
	{
		mutex_lock_and_unlock(philo->r_fork, 1);
		print_message("has taken a fork\n", philo);
		mutex_lock_and_unlock(philo->l_fork, 1);
		print_message("has taken a fork\n", philo);
	}
	return (0);
}

int	eating(t_philo *philo)
{
	mutex_lock_and_unlock(&philo->rules->verifs, 1);
	if (philo->rules->died == 1
		|| philo->rules->all_ate == philo->rules->num_philos)
	{
		mutex_lock_and_unlock(&philo->rules->verifs, 2);
		mutex_lock_and_unlock(philo->l_fork, 2);
		mutex_lock_and_unlock(philo->r_fork, 2);
		return (1);
	}
	mutex_lock_and_unlock(&philo->rules->verifs, 2);
	mutex_lock_and_unlock(&philo->reaper, 1);
	philo->last_meal = get_time();
	print_message("is eating\n", philo);
	mutex_lock_and_unlock(&philo->rules->verifs, 1);
	philo->times_eaten++;
	if (philo->rules->pme != -1 && philo->times_eaten == philo->rules->pme)
		philo->rules->all_ate++;
	mutex_lock_and_unlock(&philo->rules->verifs, 2);
	mutex_lock_and_unlock(&philo->reaper, 2);
	usleep(philo->rules->tte * 1000);
	mutex_lock_and_unlock(philo->l_fork, 2);
	mutex_lock_and_unlock(philo->r_fork, 2);
	return (0);
}

int	sleeping(t_philo *philo)
{
	mutex_lock_and_unlock(&philo->rules->verifs, 1);
	if (philo->rules->died == 1
		|| philo->rules->all_ate == philo->rules->num_philos)
	{
		mutex_lock_and_unlock(&philo->rules->verifs, 2);
		return (1);
	}
	mutex_lock_and_unlock(&philo->rules->verifs, 2);
	print_message("is sleeping\n", philo);
	usleep(philo->rules->tts * 1000);
	return (0);
}

int	thinking(t_philo *philo)
{
	mutex_lock_and_unlock(&philo->rules->verifs, 1);
	if (philo->rules->died == 1
		|| philo->rules->all_ate == philo->rules->num_philos)
	{
		mutex_lock_and_unlock(&philo->rules->verifs, 2);
		return (1);
	}
	mutex_lock_and_unlock(&philo->rules->verifs, 2);
	print_message("is thinking\n", philo);
	return (0);
}
