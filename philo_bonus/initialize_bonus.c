/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   initialize_bonus.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jomirand <jomirand@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/08 10:47:37 by jomirand          #+#    #+#             */
/*   Updated: 2023/05/08 10:47:37 by jomirand         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers_bonus.h"

void	initialize(t_rules *rules, int argc, char **argv)
{
	rules->num_philos = ft_atoi(argv[1]);
	rules->ttd = ft_atoi(argv[2]);
	rules->tte = ft_atoi(argv[3]);
	rules->tts = ft_atoi(argv[4]);
	rules->pme = -1;
	rules->all_ate = 0;
	rules->died = 0;
	rules->pid = (int *)malloc(sizeof(int) * (ft_atoi(argv[1])));
	if (!rules->pid)
	{
		error_message("failed creating pid array");
		exit (1);
	}
	rules->ph = (t_philo *)malloc(sizeof(t_philo) * rules->num_philos);
	rules->time_init = get_time();
	if (argc == 6)
		rules->pme = ft_atoi(argv[5]);
	create_philos(rules);
	create_sems(rules);
}

void	create_philos(t_rules *rules)
{
	int		i;
	char	*philo_sem;

	i = 0;
	while (i < rules->num_philos)
	{
		rules->ph[i].id = i + 1;
		rules->ph[i].last_meal = get_time();
		rules->ph[i].times_eaten = 0;
		philo_sem = ft_itoa(rules->ph[i].id);
		sem_unlink(philo_sem);
		rules->ph[i].reaper = sem_open(philo_sem, O_CREAT, 0644, 1);
		free(philo_sem);
		rules->ph[i].rules = rules;
		i++;
	}
}

void	create_sems(t_rules *rules)
{
	sem_unlink("forks");
	sem_unlink("print");
	sem_unlink("dead");
	sem_unlink("end");
	sem_unlink("meals");
	rules->forks = sem_open("forks", O_CREAT, 0644, rules->num_philos);
	rules->print = sem_open("print", O_CREAT, 0644, 1);
	rules->dead = sem_open("dead", O_CREAT, 0644, 1);
	rules->end = sem_open("end", O_CREAT, 0644, 0);
	rules->meals = sem_open("meals", O_CREAT, 0644, 0);
}
