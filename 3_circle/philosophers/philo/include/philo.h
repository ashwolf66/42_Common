/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jacha <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/29 17:49:35 by jacha             #+#    #+#             */
/*   Updated: 2024/09/02 10:45:56 by jacha            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <unistd.h>
# include <stdio.h>
# include <pthread.h>
# include <string.h>
# include <stdlib.h>
# include <sys/time.h>

struct			s_common;

typedef struct s_philo
{
	int					id;
	int					eat_count;
	long long			life;
	int					l_f;
	int					r_f;
	struct s_common		*common;
	pthread_t			thread;
}	t_philo;

typedef struct s_common
{
	int				num;
	int				die_time;
	int				eat_time;
	int				sleep_time;
	int				die;
	int				max_eat;
	int				done;
	long long		start_time;
	pthread_mutex_t	fork[200];
	pthread_mutex_t	eat_check;
	pthread_mutex_t	done_check;
	pthread_mutex_t	die_check;
	pthread_mutex_t	print;
	pthread_mutex_t	check;
	pthread_mutex_t	count;
	t_philo			philo[200];
}	t_common;

int			init_philo(t_common *common, char **argv);
int			init_mu(t_common *common);
int			init_thread(t_common *common);

void		moni(t_common *common, t_philo *philo);
int			die_check(t_common *common);
void		done_check(t_common *common, t_philo *philo);
int			escape_loop(t_common *common, t_philo *philo);

int			philo(t_common *common);
void		*philoing(void *philo);
int			eating(t_philo *philo);
void		eat_count(t_philo *philo, t_common *common);
void		life_up(t_philo *philo, t_common *common);

int			ft_atoi(const char *n);
long long	timestamp(void);
void		the_end(t_philo *philo, t_common *common);
void		check_time(long long time, t_common *common);
void		philo_print(t_common *common, int id, char *chr);

int			select_fork(t_common *common, t_philo *philo);
void		select_un_fork(t_common *common, t_philo *philo);

#endif
