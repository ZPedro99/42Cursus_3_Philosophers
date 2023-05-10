/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jomirand <jomirand@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/02 09:46:08 by jomirand          #+#    #+#             */
/*   Updated: 2023/05/02 10:47:19 by jomirand         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers_bonus.h"

int	main(int argc, char **argv)
{
	t_rules	*rules;
	int 	j;
	int		i;

	rules = malloc(sizeof(t_rules));
	if (!rules)
		return (1);
	if (!args_check(argc, argv))
	{
		printf("check the args!\n");
		free(rules);
		return (1);
	}
	initialize(rules, argc, argv);
	i = 0;
	while (i < rules->num_philos)
	{
		rules->pid[i] = fork();
		if(rules->pid[i] == 0)
		{
			simulation(&rules->ph[i]);
			break ;
		}
		i++;
	}
	check_end(rules);
	j = 1;
	while(j > 0)
		j = waitpid(0, 0, 0);
	closing(rules);
	return (0);
}


