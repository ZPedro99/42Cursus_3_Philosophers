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
	int	i;

	if (argc != 5 && argc != 6)
		return (0);
	i = 0;
	while (i < argc)
	{
		if (ft_atol(argv[i]) > INT_MAX || ft_atol(argv[i]) < INT_MIN)
			return (0);
		i++;
	}
	if (!only_num(argc, argv))
		return (0);
	if (!positive_args(argc, argv))
		return (0);
	return (1);
}

int	positive_args(int argc, char **argv)
{
	int	i;

	i = 1;
	while (i < argc)
	{
		if (ft_atoi(argv[i]) <= 0)
			return (0);
		i++;
	}
	return (1);
}

int	one_philo(t_philo *philo)
{
	if (philo->rules->num_philos == 1)
	{
		if (pthread_mutex_lock(philo->l_fork) != 0)
			error_message("Failed locking a fork\n");
		print_message("has taken a fork\n", philo);
		pthread_mutex_unlock(philo->l_fork);
		return (1);
	}
	return (0);
}

int	eating_verifs(t_philo *philo)
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
	return (0);
}
