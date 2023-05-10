/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jomirand <jomirand@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/03 10:11:05 by jomirand          #+#    #+#             */
/*   Updated: 2023/05/03 10:11:05 by jomirand         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers_bonus.h"

void	print_message(char *message, t_philo *philo)
{
	long long	time;

	sem_wait(philo->rules->print);
	time = get_time() - philo->rules->time_init;
	printf("%lld %d %s", time, philo->id, message);
	sem_post(philo->rules->print);
}

long long	get_time(void)
{
	struct timeval	time;

	gettimeofday(&time, NULL);
	return ((time.tv_sec * 1000) + (time.tv_usec / 1000));
}

void	error_message(char *str)
{
	ft_putstr_fd("Error!\n", 2);
	ft_putstr_fd(str, 2);
	return ;
}

void	closing(t_rules *rules)
{
	int i;

	i = 0;
	while(i < rules->num_philos)
	{
		sem_close(rules->ph[i].reaper);
		sem_unlink("philo_sem");
		i++;
	}
	free(rules->ph);
	free(rules->pid);
	sem_close(rules->print);
	sem_close(rules->end);
	sem_close(rules->dead);
	sem_close(rules->forks);
	sem_close(rules->meals);
	free(rules);
	sem_unlink("print");
	sem_unlink("end");
	sem_unlink("dead");
	sem_unlink("forks");
	sem_unlink("meals");
}
