/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jomirand <jomirand@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/05 09:56:30 by jomirand          #+#    #+#             */
/*   Updated: 2023/04/20 10:49:51 by jomirand         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

int	main(int argc, char **argv)
{
	t_rules			*rules;
	pthread_mutex_t	*forks;

	rules = malloc(sizeof(t_rules));
	if (!args_check(argc, argv))
	{
		printf("check the args!\n");
		free(rules);
		return (0);
	}
	struct_initialize(rules, argc, argv);
	forks = create_forks(rules);
	if (!forks)
		error_message("No forks were initialized!\n");
	rules->ph = create_philos(rules, forks);
	if (rules->ph == 0)
		error_message("No philos were initialized!\n");
	create_threads(rules);
	join_threads(rules, forks);
	free(rules->ph);
	free(rules);
	free(forks);
	return (0);
}
