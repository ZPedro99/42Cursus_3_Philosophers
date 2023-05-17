/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers_bonus.h                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jomirand <jomirand@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/02 10:04:33 by jomirand          #+#    #+#             */
/*   Updated: 2023/05/02 10:04:33 by jomirand         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILOSOPHERS_BONUS_H
# define PHILOSOPHERS_BONUS_H

# include <pthread.h>
# include <stdio.h>
# include <unistd.h>
# include <stdlib.h>
# include <sys/time.h>
# include <fcntl.h>
# include <sys/stat.h>
# include <semaphore.h>
# include <sys/types.h>
# include <sys/wait.h>
# include <limits.h>

typedef struct s_philo
{
	int				id;
	long long		last_meal;
	int				times_eaten;
	sem_t			*reaper;
	struct s_rules	*rules;
}				t_philo;

typedef struct s_rules
{
	int			num_philos;
	long long	time_init;
	int			ttd;
	int			tts;
	int			tte;
	int			pme;
	int			died;
	int			all_ate;
	int			*pid;
	sem_t		*forks;
	sem_t		*meals;
	sem_t		*print;
	sem_t		*dead;
	sem_t		*end;
	t_philo		*ph;
}				t_rules;

//**********main**********//

void		create_processes(t_rules *rules);

//**********simulation_bonus**********//

void		simulation(t_philo *philo);
void		take_forks(t_philo *philo);
void		eating(t_philo *philo);
void		sleeping(t_philo *philo);
void		thinking(t_philo *philo);

//**********initialize_bonus**********//

void		*monitoring(void *arg);
int			philos_died(t_philo *philo);
void		check_end(t_rules *rules);
void		*check_meals(void *arg);
void		*check_finish(void *arg);

//**********verifs_bonus**********//

int			args_check(int argc, char **argv);
int			positive_args(int argc, char **argv);

//**********utils_libft_bonus**********//

int			ft_atoi(const char *str);
int			only_num(int argc, char **argv);
void		ft_putstr_fd(char *s, int fd);
char		*ft_itoa(int n);

//**********utils2_libft_bonus**********//

long		ft_atol(const char *str);
int			ft_isdigit(int c);

//**********utils_bonus**********//

void		print_message(char *message, t_philo *philo);
long long	get_time(void);
void		error_message(char *str);
void		closing(t_rules *rules);

//**********initialize_bonus**********//

void		initialize(t_rules *rules, int argc, char **argv);
void		create_philos(t_rules *rules);
void		create_sems(t_rules *rules);

#endif
