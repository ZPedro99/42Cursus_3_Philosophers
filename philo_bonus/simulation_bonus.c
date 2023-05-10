/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   simulation_bonus.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jomirand <jomirand@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/10 10:03:47 by jomirand          #+#    #+#             */
/*   Updated: 2023/05/10 10:03:47 by jomirand         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers_bonus.h"

void	simulation(t_philo *philo)
{
	pthread_t	reaper;

	if(philo->id % 2)
		usleep(2000);
	pthread_create(&reaper, NULL, &monitoring, philo);
	while(1)
	{
		take_forks(philo);
		eating(philo);
		sleeping(philo);
		thinking(philo);
	}
}

void	take_forks(t_philo *philo)
{
	usleep(100);
	sem_wait(philo->rules->forks);
	print_message("has taken a fork\n", philo);
	usleep(100);
	sem_wait(philo->rules->forks);
	print_message("has taken a fork\n", philo);
}

void	eating(t_philo *philo)
{
	sem_wait(philo->reaper);
	philo->last_meal = get_time();
	print_message("is eating\n", philo);
	if(philo->rules->pme != -1) {
		philo->times_eaten++;
	}
	if(philo->times_eaten == philo->rules->pme) {
		sem_post(philo->rules->meals);
	}
	sem_post(philo->reaper);
	usleep(philo->rules->tte * 1000);
	sem_post(philo->rules->forks);
	sem_post(philo->rules->forks);
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