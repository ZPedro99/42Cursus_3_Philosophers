/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jomirand <jomirand@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/05 10:54:45 by jomirand          #+#    #+#             */
/*   Updated: 2023/04/19 15:24:03 by jomirand         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

void	struct_initialize(t_rules *rules, int argc, char **argv)
{
	rules->num_philos = ft_atoi(argv[1]);
	rules->ttd = ft_atoi(argv[2]);
	rules->tte = ft_atoi(argv[3]);
	rules->tts = ft_atoi(argv[4]);
	rules->pme = -1;
	rules->all_ate = 0;
	rules->died = 0;
	rules->time_init = get_time();
	if(argc == 6)
		rules->pme = ft_atoi(argv[5]);
}

void	print_message(char *message, t_philo *philo)
{
	long long	time;

	/* printf("%d\n", philo->rules->died);
	printf("%d\n", philo->rules->all_ate);
	printf("%d\n", philo->rules->num_philos); */
	if(philo->rules->died || philo->rules->all_ate == philo->rules->num_philos)
		return ;
	time = get_time() - philo->rules->time_init;
	if (pthread_mutex_lock(&philo->rules->print) != 0)
		error_message("Failed locking print mutex\n");
	printf("%lld %d %s", time, philo->id, message);
	if (pthread_mutex_unlock(&philo->rules->print) != 0)
		return ;
}

long long	get_time(void)
{
	struct timeval time;
	gettimeofday(&time, NULL);
	return ((time.tv_sec * 1000) + (time.tv_usec / 1000));
}

void	error_message(char *str)
{
	ft_putstr_fd("Error!\n", 2);
	ft_putstr_fd(str, 2);
	return ;
}