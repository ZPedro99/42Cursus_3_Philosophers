/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jomirand <jomirand@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/05 09:56:33 by jomirand          #+#    #+#             */
/*   Updated: 2023/04/20 16:43:35 by jomirand         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILOSOPHERS_H
# define PHILOSOPHERS_H

# include <pthread.h>
# include <stdio.h>
# include <unistd.h>
# include <stdlib.h>
# include <sys/time.h>
# include <limits.h>

typedef struct s_philo
{
	int				id;
	long long		last_meal;
	pthread_t		philo;
	pthread_mutex_t	*l_fork;
	pthread_mutex_t	*r_fork;
	pthread_mutex_t	reaper;
	int				times_eaten;
	struct s_rules	*rules;
}				t_philo;

typedef struct s_rules
{
	int				num_philos;
	long long		time_init;
	int				ttd;
	int				tts;
	int				tte;
	int				pme;
	int				died;
	int				all_ate;
	pthread_mutex_t	print;
	pthread_mutex_t	verifs;
	pthread_t		monitor;
	t_philo			*ph;
}				t_rules;

//**********UTILS**********//

void			struct_initialize(t_rules *rules, int argc, char **argv);
long long		get_time(void);
void			print_message(char *message, t_philo *philo);
void			error_message(char *str);
void			mutex_lock_and_unlock(pthread_mutex_t *mutex, int flag);

//**********VERIFS**********//

int				args_check(int argc, char **argv);
int				only_num(int argc, char **argv);
int				positive_args(int argc, char **argv);
int				one_philo(t_philo *philo);
int				eating_verifs(t_philo *philo);

//**********PHILOS_AND_FORKS**********//

pthread_mutex_t	*create_forks(t_rules *rules);
t_philo			*create_philos(t_rules *rules, pthread_mutex_t *forks);
void			create_threads(t_rules *rules);
void			join_threads(t_rules *rules, pthread_mutex_t *forks);

//**********SIMULATION**********//

void			*simulation(void *arg);
int				take_forks(t_philo *philo);
int				eating(t_philo *philo);
int				sleeping(t_philo *philo);
int				thinking(t_philo *philo);

//**********MONITORING**********//

void			*monitoring(void *arg);
int				philos_died(t_rules *rules);
int				philos_ate(t_rules *rules);

//**********UTILS_LIBFT**********//

int				ft_atoi(const char *str);
int				only_num(int argc, char **argv);
void			ft_putstr_fd(char *s, int fd);
long			ft_atol(const char *str);
int				ft_isdigit(int c);

#endif